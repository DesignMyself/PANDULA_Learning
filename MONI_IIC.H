#ifndef _MONI_IIC_H
#define _MONI_IIC_H
#include <rtthread.h>
#include <rtdevice.h>
//IO��������
#define SDA_IN()  rt_pin_mode(16,PIN_MODE_INPUT_PULLUP)//{GPIOC->MODER&=~(3<<(1*2));GPIOC->MODER|=0<<(1*2);}	//PC1����ģʽ
#define SDA_OUT() rt_pin_mode(16,PIN_MODE_OUTPUT)//{GPIOC->MODER&=~(3<<(1*2));GPIOC->MODER|=1<<(1*2);} 	//PC1���ģʽ
//IO����
#define IIC_SCL(n)		(n?rt_pin_write(87,1):rt_pin_write(87,0))//SCL PD6
#define IIC_SDA(n)		(n?rt_pin_write(16,1):rt_pin_write(16,0))//SDA PC1
#define READ_SDA  		rt_pin_read(16)//����SDA

#define AHT10_IIC_ADDR	0x38			//AHT10 IIC��ַ
#define AHT10_CALIBRATION_CMD 	0xE1 	//У׼����(�ϵ��ֻ��Ҫ����һ��)
#define AHT10_NORMAL_CMD 		0xA8 	//��������ģʽ
#define AHT10_GET_DATA 			0xAC 	//��ȡ��������

uint8_t AHT10_Init(void);
float AHT10_Read_Temperature(void);
float AHT10_Read_Humidity(void);

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);
#endif 