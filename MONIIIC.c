
#include <rtthread.h>
#include <rtdevice.h>
#include "MONI_IIC.H"

void IIC_Init(void)
{
		rt_pin_mode(16,PIN_MODE_OUTPUT);
		rt_pin_mode(87,PIN_MODE_OUTPUT);
	  IIC_SDA(1);
    IIC_SCL(1);
	
}

/**
 * @brief	����IIC��ʼ�ź�
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Start(void)
{
    SDA_OUT();     //sda�����
    IIC_SDA(1);
    IIC_SCL(1);
    rt_thread_delay(1);
    IIC_SDA(0);//START:when CLK is high,DATA change form high to low
		rt_thread_delay(1);
    IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ��������
}

/**
 * @brief	����IICֹͣ�ź�
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Stop(void)
{
  SDA_OUT();//sda�����
	IIC_SDA(0);
  IIC_SCL(1);
	rt_thread_delay(1);
	IIC_SDA(1);//STOP:when CLK is high DATA change form low to high
	rt_thread_delay(1);
	IIC_SCL(0);//����I2C���߽����ź�
}

/**
 * @brief	�ȴ�Ӧ���źŵ���
 *
 * @param   void
 *
 * @return  u8		1������Ӧ��ʧ��
 *					0������Ӧ��ɹ�
 */
uint8_t IIC_Wait_Ack(void)
{
   
    SDA_IN();      //SDA����Ϊ����
    IIC_SDA(1);
    rt_thread_delay(1);
    IIC_SCL(1);
    rt_thread_delay(1);

		if(READ_SDA==1)
    {
        rt_thread_delay(251);
        if(READ_SDA==1)
				{
						IIC_Stop();
            return 1;
				}
        
    }

    IIC_SCL(0);//ʱ�����0
    return 0;
}
/**
 * @brief	����ACKӦ��
 *
 * @param   void
 *
 * @return  void
 */
void IIC_Ack(void)
{
    IIC_SCL(0);
    SDA_OUT();
    IIC_SDA(0);
    rt_thread_delay(1);
    IIC_SCL(1);
    rt_thread_delay(1);
    IIC_SCL(0);
}
/**
 * @brief	������ACKӦ��
 *
 * @param   void
 *
 * @return  void
 */
void IIC_NAck(void)
{
    IIC_SCL(0);
    SDA_OUT();
    IIC_SDA(1);
    rt_thread_delay(1);
    IIC_SCL(1);
     rt_thread_delay(1);
    IIC_SCL(0);
}
/**
 * @brief	IIC����һ���ֽ�
 *
 * @param   txd		��Ҫ���͵�����
 *
 * @return  void
 */
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���

    for(t = 0; t < 8; t++)
    {
        IIC_SDA((txd & 0x80) >> 7);
        txd <<= 1;
        IIC_SCL(1);
        rt_thread_delay(1);
        IIC_SCL(0);
         rt_thread_delay(1);;
    }
}
/**
 * @brief	��1���ֽ�����
 *
 * @param   ack		1������ACK		0������nACK
 *
 * @return  u8		���ض�ȡ����
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN();//SDA����Ϊ����

    for(i = 0; i < 8; i++)
    {
        IIC_SCL(0);
         rt_thread_delay(1);
        IIC_SCL(1);
        receive <<= 1;
        if(READ_SDA)receive++;
        rt_thread_delay(1);
    }

    if(!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK

    return receive;
	}
/**
 * @brief	��ATH10д������
 *
 * @param   cmd		����
 * @param   data	Ҫд�������
 * @param   len		д�����ݴ�С
 *
 * @return  u8		0,����,����,�������
 */
uint8_t AHT10_Write_Data(uint8_t cmd, uint8_t *data, uint8_t len)
{
    IIC_Start();
    IIC_Send_Byte((AHT10_IIC_ADDR << 1) | 0); //����������ַ+д����

    if(IIC_Wait_Ack())          //�ȴ�Ӧ��
    {
        IIC_Stop();
        return 1;
    }

    IIC_Send_Byte(cmd);         //д�Ĵ�����ַ
    IIC_Wait_Ack();             //�ȴ�Ӧ��

    for(uint8_t i = 0; i < len; i++)
    {
        IIC_Send_Byte(data[i]);     //��������
        IIC_Wait_Ack();				//�ȴ�Ӧ��
    }

    IIC_Stop();
    return 0;
}


/**
 * @brief	��һ���ֽ�
 *
 * @param   void
 *
 * @return  u8		����������
 */
uint8_t AHT10_ReadOneByte(void)
{
    uint8_t res = 0;
    IIC_Start();
    IIC_Send_Byte((AHT10_IIC_ADDR << 1) | 0X01); //����������ַ+������

    if(IIC_Wait_Ack())          //�ȴ�Ӧ��
    {
        IIC_Stop();
        return 1;
    }

    res = IIC_Read_Byte(0);		//������,����nACK
    IIC_Stop();                 //����һ��ֹͣ����
    return res;
}

/**
 * @brief	������
 *
 * @param   data	���ݻ���
 * @param   len		�����ݴ�С
 *
 * @return  u8		0,����,����,�������
 */
uint8_t AHT10_Read_Data(uint8_t *data, uint8_t len)
{
    IIC_Start();
    IIC_Send_Byte((AHT10_IIC_ADDR << 1) | 0x01); //����������ַ+������

    if(IIC_Wait_Ack())          //�ȴ�Ӧ��
    {
        IIC_Stop();
        return 1;
    }

    for(uint8_t i = 0; i < len; i++)
    {
        if(i == (len - 1))
            data[i] = IIC_Read_Byte(0);		//������,����nACK

        else
            data[i] = IIC_Read_Byte(1);		//������,����ACK
    }

    IIC_Stop();
    return 0;
}

/**
 * @brief	��ȡ�¶�����
 *
 * @param   void
 *
 * @return  float	�¶����ݣ���λ�����϶ȣ�
 */
float AHT10_Read_Temperature(void)
{
    uint8_t res = 0;
    uint8_t cmd[2] = {0, 0};
    uint8_t temp[6];
    float cur_temp;

    res = AHT10_Write_Data(AHT10_GET_DATA, cmd, 2); //���Ͷ�ȡ��������

    if(res)	return 1;

    res = AHT10_Read_Data(temp, 6);				//��ȡ����

    if(res)	return 1;

    cur_temp = ((temp[3] & 0xf) << 16 | temp[4] << 8 | temp[5]) * 200.0 / (1 << 20) - 50;

    return cur_temp;
}

/**
 * @brief	��ȡʪ������
 *
 * @param   void
 *
 * @return  float	ʪ�����ݣ���λ��%RH��
 */
float AHT10_Read_Humidity(void)
{
		uint8_t res = 0;
    uint8_t cmd[2] = {0, 0};
		uint8_t humi[6];
    float cur_humi;

    res = AHT10_Write_Data(AHT10_GET_DATA, cmd, 2); //���Ͷ�ȡ��������

    if(res)	return 1;

    res = AHT10_Read_Data(humi, 6);				//��ȡ����

    if(res)	return 1;

    cur_humi = ((humi[1]) << 12 | humi[2] << 4 | (humi[3] & 0xF0)) * 100.0 / (1 << 20);

    return cur_humi;
}

/**
 * @brief	ATH10��������ʼ��
 *
 * @param   void
 *
 * @return  u8		0,��ʼ���ɹ�������,ʧ��
 */
uint8_t AHT10_Init(void)
{
    uint8_t res;
    uint8_t temp[2] = {0, 0};

    IIC_Init();		//��ʼ��IIC�ӿڣ�ע�������IIC����Ϊ��SCL-PD6 SDA-PC1

    res = AHT10_Write_Data(AHT10_NORMAL_CMD, temp, 2);

    if(res != 0)	return 1;

    rt_thread_delay(300);

    temp[0] = 0x08;
    temp[1] = 0x00;
    res = AHT10_Write_Data(AHT10_CALIBRATION_CMD, temp, 2);

    if(res != 0)	return 1;

    rt_thread_delay(300);

    return 0;
}
