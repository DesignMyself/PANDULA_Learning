#include "panduola_init.h"


void motor_left()
{
	rt_pin_write(motorA,1);
	rt_pin_write(motorB,0);
	
}
void motor_right()
{
	rt_pin_write(motorA,0);
	rt_pin_write(motorB,1);
	
}
void motor_stop()
{
	rt_pin_write(motorA,0);
	rt_pin_write(motorB,0);
	
}
void pin_mode_init()
{
	rt_pin_mode(29,PIN_MODE_OUTPUT);
	rt_pin_mode(G_Led,PIN_MODE_OUTPUT);
	rt_pin_mode(B_led,PIN_MODE_OUTPUT);
	rt_pin_mode(motorA,PIN_MODE_OUTPUT);
	rt_pin_mode(motorB,PIN_MODE_OUTPUT);
	rt_pin_mode(test2_pin,PIN_MODE_OUTPUT);
	rt_pin_mode(KEY0,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(KEY1,PIN_MODE_INPUT_PULLUP);
	rt_pin_mode(KEY2,PIN_MODE_INPUT_PULLUP);
	rt_pin_write(test_pin,1);
	rt_pin_write(B_led,1);
	rt_pin_write(G_Led,1);
	
}


void motor_control(void *arg)
{
	
	rt_uint32_t sign=(rt_uint32_t)arg;
	rt_kprintf("the key is %d\n",sign);
	switch(sign)
	{
		case KEY0:
			motor_left();
			break;
		case KEY1:
			motor_right();
			break;
		case KEY2:
			motor_stop();
			break;
		default:
			break;
		
	
	}
}



/*看门狗初始化*/
IWDG_HandleTypeDef IWDG_Handler; //独立看门狗句柄

/**
 * @brief	初始化独立看门狗函数
 *			时间计算(大概):Tout=((2^prer)*rlr)/32 (ms)
 *
 * @param   prer	分频数:IWDG_PRESCALER_4~IWDG_PRESCALER_256
 * @param   rlr		自动重装载值,0~0XFFF
 *
 * @return  void
 */
void IWDG_Init(uint8_t prer, uint16_t rlr)//独立看门狗——1
{
    IWDG_Handler.Instance = IWDG;
    IWDG_Handler.Init.Prescaler = prer;					//设置IWDG分频系数
    IWDG_Handler.Init.Reload = rlr;						//重装载值
    IWDG_Handler.Init.Window = IWDG_WINDOW_DISABLE;
    HAL_IWDG_Init(&IWDG_Handler);					//初始化IWDG并开启独立看门狗
		 

}

///*窗口看门狗*/
//WWDG_HandleTypeDef hwwdg;
// void MX_WWDG_Init(uint16_t tr,uint16_t wr,uint32_t pre)
//{

//  hwwdg.Instance = WWDG;
//  hwwdg.Init.Prescaler = pre;
//  hwwdg.Init.Window = wr;
//  hwwdg.Init.Counter = tr;
//  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
//	HAL_WWDG_Init(&hwwdg);
//	__HAL_WWDG_ENABLE_IT(& hwwdg, WWDG_IT_EWI);//开中断才能喂狗
//	

//}
//void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
//{
//    __HAL_RCC_WWDG_CLK_ENABLE();    		//使能窗口看门狗时钟

//    HAL_NVIC_SetPriority(WWDG_IRQn, 2, 3);  //抢占优先级2，子优先级为3
//    HAL_NVIC_EnableIRQ(WWDG_IRQn);          //使能窗口看门狗中断
//}
// void WWDG_IRQHandler(void)
//{
//    HAL_WWDG_IRQHandler(&hwwdg);//调用WWDG共用中断处理函数
//		
//	
//}

///**
// * @brief	中断服务函数处理过程
// *			此函数会被HAL_WWDG_IRQHandler()调用
// *
// * @param   hwwdg	窗口看门狗句柄
// *
// * @return  void
// */
//rt_uint8_t k=0;
//void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg1)
//{

//	HAL_WWDG_Refresh(&hwwdg);
//			rt_pin_write(29,k);
//		k=~k;//这一步要优先，不然b状态始终不能变
//  //更新窗口看门狗值
//}

/*************************************************
//PWM使用																					*
																									*
**************************************************/
uint32_t speed1=0;
uint32_t speed2=0;
void key_callback(void* b)
{
	uint32_t k=(uint32_t)b;
	rt_kprintf("the input key is %d\n",k);
	switch(k)
	{
		case 1:
				speed1+=20;
				speed2=0;
				if(speed1>=1000)
				{
					speed1=999;
					
				}
				TIM_PWM2_1SET(speed1);
				TIM_PWM2_1SET(speed2);
				break;
		case 2:
				speed2+=20;
				speed1=0;
					if(speed2>=1000)
				{
					speed1=999;
					
				}
				TIM_PWM2_1SET(speed1);
				TIM_PWM2_1SET(speed2);
				break;
		default:
			break;
		
		
	}
	
}
void pin_interrupt_control()
{
	rt_kprintf("come into pin_control_interr\n");
	rt_pin_attach_irq(KEY0,PIN_IRQ_MODE_FALLING,motor_control,(void*)PIN_KEY0);//引脚号，触发模式，回调函数，传入回调函数的参数

	rt_pin_attach_irq(KEY1,PIN_IRQ_MODE_FALLING,motor_control,(void*)PIN_KEY1);
	rt_pin_attach_irq(KEY2,PIN_IRQ_MODE_FALLING,motor_control,(void*)PIN_KEY2);
	rt_pin_irq_enable(KEY0,PIN_IRQ_ENABLE);
	
	rt_pin_irq_enable(KEY1,PIN_IRQ_ENABLE);
	rt_pin_irq_enable(KEY2,PIN_IRQ_ENABLE);//使得中断
	
	
}














