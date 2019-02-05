/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-16     armink       first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "panduola_init.h"
#include <drivers/rt_drv_pwm.h>
#include "stm32l4xx_hal.h"
#include "Display.h"
#define event4_flag 1<<4
static struct rt_event event4;//用来控制往LCD发送数据
/* using RED LED in RGB */
extern IWDG_HandleTypeDef IWDG_Handler;


static  rt_thread_t task_1;
static  rt_thread_t task_2;
extern rt_device_t wdg_dev;

char * b;
MPU_Data MPU_Data1;
uint8_t buffer[120];//数据存储区
void LCD_Display(void *parameter)
{
		uint32_t ch;
		uint16_t x=50;
			uint16_t y=20;

	while(1)
	{
	 
	
			rt_event_recv(&event4,event4_flag,RT_EVENT_FLAG_AND|RT_EVENT_FLAG_CLEAR,RT_WAITING_FOREVER,&ch);
			rt_kprintf("x angle is:");
			Value_Asii(1,MPU_Data1.X_Angle);
			uart1_putchar('\n');
			rt_kprintf("y angle is:");
			Value_Asii(1,MPU_Data1.Y_Angle);
			uart1_putchar('\n');
			rt_kprintf("Z angle is:");
			Value_Asii(1,MPU_Data1.Z_Angle);
			uart1_putchar('\n');
			
			rt_thread_delay(500);
    /* show some string on lcd */
   
	}
}

void task_2_entry(void *parameter)
{
	uint8_t count=0;
	while(1)
	{
		count=uart3_getchar();
		uart3_putchar(count);
	
	}
	
	
}
void  MPU_Get_Data(void *parameter)
{
	uart3_open("uart3");
	uart1_open("uart1");//用来接收MPU6050的数据
	uint8_t i=0;
	while(1)
	{
		
		
		for(i=0;i<11;i++)
		{
				buffer[i]=uart3_getchar();//在里面已经包含有调度函数，当没有数据输入时会停留在这一步，时间到后调度到其他任务
				
				if(buffer[0]!=0x55)
				{
						 
				break;
					
				}
				
					if(i==1&&buffer[1]!=0x53)
					{
						
						break;
						
					}
				
			
			if(i==10)
			{
				
				MPU_Data1.X_Angle=(((buffer[3]<<8)|buffer[2])*180/32768.00f);
				MPU_Data1.Y_Angle=(((buffer[5]<<8)|buffer[4])*180/32768.00f);
				MPU_Data1.Z_Angle=(((buffer[7]<<8)|buffer[6])*180/32768.00f);
				rt_event_send(&event4,event4_flag);
				break;
			
			}
		}
		
	
	}
	
}

 void idle_hook(void)
{
   rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE , NULL);
}

int main(void)
{
    uint32_t result=0;
		
    /* set LED pin mode to output */
	
		pin_mode_init();
		pin_interrupt_control();
			//	HAL_IWDG_Refresh(&IWDG_Handler);//独立看门狗开启——1
		lcd_clear(BLACK);

	 /* set the background color and foreground color */
    lcd_set_color(BLACK,YELLOW);
		//uart1_open("uart1");
		
		
		rt_event_init(&event4, "event4", RT_IPC_FLAG_FIFO);
		//MX_TIM2_Init(1000,80);
	
		//IWDG_Init(IWDG_PRESCALER_8,50);
		////独立看门狗开启——1    8*200/32ms,看门狗没有中断，利用HSI的32.165k的晶振
		rt_thread_idle_sethook(idle_hook);
		iwdg_sample();
	
	/*********启动任务1********/
		task_1=rt_thread_create("task_1",LCD_Display,RT_NULL,1024,4,10);
		if(task_1!=RT_NULL)
		{
			
			rt_thread_startup(task_1);
		}
			/*********启动任务2********/
			task_2=rt_thread_create("task_2",MPU_Get_Data,RT_NULL,1024,20,10);
		if(task_2!=RT_NULL)
		{
			rt_thread_startup(task_2);
		}
    
    return 0;

}
