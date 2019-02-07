#ifndef _MONI_IIC_H
#define _MONI_IIC_H
#include <rtthread.h>
#include <rtdevice.h>
//IO方向设置
#define SDA_IN()  rt_pin_mode(16,PIN_MODE_INPUT_PULLUP)//{GPIOC->MODER&=~(3<<(1*2));GPIOC->MODER|=0<<(1*2);}	//PC1输入模式
#define SDA_OUT() rt_pin_mode(16,PIN_MODE_OUTPUT)//{GPIOC->MODER&=~(3<<(1*2));GPIOC->MODER|=1<<(1*2);} 	//PC1输出模式
//IO操作
#define IIC_SCL(n)		(n?rt_pin_write(87,1):rt_pin_write(87,0))//SCL PD6
#define IIC_SDA(n)		(n?rt_pin_write(16,1):rt_pin_write(16,0))//SDA PC1
#define READ_SDA  		rt_pin_read(16)//输入SDA

#define AHT10_IIC_ADDR	0x38			//AHT10 IIC地址
#define AHT10_CALIBRATION_CMD 	0xE1 	//校准命令(上电后只需要发送一次)
#define AHT10_NORMAL_CMD 		0xA8 	//正常工作模式
#define AHT10_GET_DATA 			0xAC 	//读取数据命令

uint8_t AHT10_Init(void);
float AHT10_Read_Temperature(void);
float AHT10_Read_Humidity(void);

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);
#endif 