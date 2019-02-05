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



/*���Ź���ʼ��*/
IWDG_HandleTypeDef IWDG_Handler; //�������Ź����

/**
 * @brief	��ʼ���������Ź�����
 *			ʱ�����(���):Tout=((2^prer)*rlr)/32 (ms)
 *
 * @param   prer	��Ƶ��:IWDG_PRESCALER_4~IWDG_PRESCALER_256
 * @param   rlr		�Զ���װ��ֵ,0~0XFFF
 *
 * @return  void
 */
void IWDG_Init(uint8_t prer, uint16_t rlr)//�������Ź�����1
{
    IWDG_Handler.Instance = IWDG;
    IWDG_Handler.Init.Prescaler = prer;					//����IWDG��Ƶϵ��
    IWDG_Handler.Init.Reload = rlr;						//��װ��ֵ
    IWDG_Handler.Init.Window = IWDG_WINDOW_DISABLE;
    HAL_IWDG_Init(&IWDG_Handler);					//��ʼ��IWDG�������������Ź�
		 

}

///*���ڿ��Ź�*/
//WWDG_HandleTypeDef hwwdg;
// void MX_WWDG_Init(uint16_t tr,uint16_t wr,uint32_t pre)
//{

//  hwwdg.Instance = WWDG;
//  hwwdg.Init.Prescaler = pre;
//  hwwdg.Init.Window = wr;
//  hwwdg.Init.Counter = tr;
//  hwwdg.Init.EWIMode = WWDG_EWI_DISABLE;
//	HAL_WWDG_Init(&hwwdg);
//	__HAL_WWDG_ENABLE_IT(& hwwdg, WWDG_IT_EWI);//���жϲ���ι��
//	

//}
//void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
//{
//    __HAL_RCC_WWDG_CLK_ENABLE();    		//ʹ�ܴ��ڿ��Ź�ʱ��

//    HAL_NVIC_SetPriority(WWDG_IRQn, 2, 3);  //��ռ���ȼ�2�������ȼ�Ϊ3
//    HAL_NVIC_EnableIRQ(WWDG_IRQn);          //ʹ�ܴ��ڿ��Ź��ж�
//}
// void WWDG_IRQHandler(void)
//{
//    HAL_WWDG_IRQHandler(&hwwdg);//����WWDG�����жϴ�����
//		
//	
//}

///**
// * @brief	�жϷ������������
// *			�˺����ᱻHAL_WWDG_IRQHandler()����
// *
// * @param   hwwdg	���ڿ��Ź����
// *
// * @return  void
// */
//rt_uint8_t k=0;
//void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg1)
//{

//	HAL_WWDG_Refresh(&hwwdg);
//			rt_pin_write(29,k);
//		k=~k;//��һ��Ҫ���ȣ���Ȼb״̬ʼ�ղ��ܱ�
//  //���´��ڿ��Ź�ֵ
//}

/*************************************************
//PWMʹ��																					*
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
	rt_pin_attach_irq(KEY0,PIN_IRQ_MODE_FALLING,motor_control,(void*)PIN_KEY0);//���źţ�����ģʽ���ص�����������ص������Ĳ���

	rt_pin_attach_irq(KEY1,PIN_IRQ_MODE_FALLING,motor_control,(void*)PIN_KEY1);
	rt_pin_attach_irq(KEY2,PIN_IRQ_MODE_FALLING,motor_control,(void*)PIN_KEY2);
	rt_pin_irq_enable(KEY0,PIN_IRQ_ENABLE);
	
	rt_pin_irq_enable(KEY1,PIN_IRQ_ENABLE);
	rt_pin_irq_enable(KEY2,PIN_IRQ_ENABLE);//ʹ���ж�
	
	
}














