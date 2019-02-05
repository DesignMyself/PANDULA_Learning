/*
 * �����嵥������һ�� PWM �豸ʹ������
 * ���̵����� pwm_led_sample ��������ն�
 * ������ø�ʽ��pwm_led_sample
 * �����ܣ�ͨ�� PWM �豸���� LED �Ƶ����ȣ����Կ���LED��ͣ���ɰ��䵽����Ȼ���ִ����䵽����
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/rt_drv_pwm.h>
#define MotorA        23      /* LED PIN�ű�ţ��鿴�����ļ�drv_gpio.cȷ�� */
#define PWM_DEV_NAME1       "pwm2"  /* PWM�豸���� */
#define PWM_DEV_CHANNEL1     1       /* PWMͨ�� */
#define MotorB        24      /* LED PIN�ű�ţ��鿴�����ļ�drv_gpio.cȷ�� */
#define PWM_DEV_NAME2        "pwm2"  /* PWM�豸���� */
#define PWM_DEV_CHANNEL2     2       /* PWMͨ�� */

struct rt_device_pwm *pwm_dev1;      /* PWM�豸��� */
struct rt_device_pwm *pwm_dev2;      /* PWM�豸��� */

 int pwm_led_sample()
{
    rt_uint32_t period, pulse, dir;

    period = 500000;    /* ����Ϊ0.5ms����λΪ����ns */
    dir = 1;            /* PWM������ֵ���������� */
    pulse = 0;          /* PWM������ֵ����λΪ����ns */

    /* ����LED���Ž�ģʽΪ��� */
    rt_pin_mode(MotorA , PIN_MODE_OUTPUT);
    /* ����LED���� */
    rt_pin_write(MotorA , PIN_HIGH);

    /* �����豸 */
    pwm_dev1 = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME1);
    if (pwm_dev1 == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME1);
        return RT_ERROR;
    }

    /* ����PWM���ں�������Ĭ��ֵ */
    rt_pwm_set(pwm_dev1, PWM_DEV_CHANNEL1, period, pulse);
    /* ʹ���豸 */
    rt_pwm_enable(pwm_dev1, PWM_DEV_CHANNEL1);

	}

	