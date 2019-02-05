#ifndef panduola_init_H__
#define panduola_init_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_iwdg.h"
#include <drv_lcd.h>
#include "app_uSart.h"
#include "math.h"
#define LED_PIN              PIN_LED_R
#define test_pin 38
#define G_Led	39
#define B_led	40
#define test2_pin 35
#define motorA 24
#define motorB 23
#define KEY0 57
#define KEY1 56
#define KEY2 55
#define  Event1_Sign (1<<0)
#define  Event2_Sign (1<<1)

typedef struct{
	float X_Angle;
	float  Y_Angle;
	float Z_Angle;	
	float COSX;
}MPU_Data;

void pin_mode_init(void );//输入输出初始化
void motor_left(void);//电机顺时针转
void motor_right(void);//电机顺时针转
void motor_stop(void);
void motor_control(void *arg);//引脚中断操作的回调函数
void MX_GPIO_Init(void);
void IWDG_Init(uint8_t prer, uint16_t rlr);//看门狗初始化时间ms=(4*2^prer)*rlr/32
void MX_WWDG_Init(uint16_t tr,uint16_t wr,uint32_t pre);
//int iwdg_sample(void);//rtthread中看门狗初始化
 int iwdg_sample(void);
 void pin_interrupt_control(void);
#endif
