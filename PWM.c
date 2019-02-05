/* TIM2 init function */
#include "stm32l4xx_hal.h"
TIM_HandleTypeDef htim2;//��ʱ��2��PWM���
 void MX_TIM2_Init(uint16_t per,uint16_t pre)////TIM2ʱ��Ƶ�� 80M/pre  ����Ƶ��80M/pre/per     Ĭ��ռ�ձ�Ϊ50%
{
	
  TIM_OC_InitTypeDef sConfigOC;//��ʱ��2���

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = pre-1;//��ʱ��2��Ƶ
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period =per-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    rt_kprintf("PWM2 Init fail");
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;//ģʽѡ��PWM1
  sConfigOC.Pulse = per/2;//���ñȽ�ֵ����ֵ����ȷ����ձȣ�/2��ʾΪ50%
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;//����Ƚϼ���
 
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
   rt_kprintf("PWM Channel 1 fail");
  }
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    rt_kprintf("PWM Channel 2 fail");
  }
	 
	 
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); 	//����PWMͨ��1
	rt_kprintf("TIM2 finish\n");
}
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_pwm->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }

}



void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }

}
/**
 * @brief	����TIM2ͨ��1��ռ�ձ�
 *
 * @param   compare		�Ƚ�ֵ
 *
 * @return  void
 */
void TIM_PWM2_1SET(uint32_t compare)
{
  // __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,compare);
	TIM2->CCR1=compare;
						
}

/**
 * @brief	����TIM2ͨ��2��ռ�ձ�
 *
 * @param   compare		�Ƚ�ֵ
 *
 * @return  void
 */
void TIM_PWM2_2SET(uint32_t  compare)
{
   TIM2->CCR2=compare;
						
}
