/*
 * 程序清单：这是一个 PWM 设备使用例程
 * 例程导出了 pwm_led_sample 命令到控制终端
 * 命令调用格式：pwm_led_sample
 * 程序功能：通过 PWM 设备控制 LED 灯的亮度，可以看到LED不停的由暗变到亮，然后又从亮变到暗。
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/rt_drv_pwm.h>
#define MotorA        23      /* LED PIN脚编号，查看驱动文件drv_gpio.c确定 */
#define PWM_DEV_NAME1       "pwm2"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL1     1       /* PWM通道 */
#define MotorB        24      /* LED PIN脚编号，查看驱动文件drv_gpio.c确定 */
#define PWM_DEV_NAME2        "pwm2"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL2     2       /* PWM通道 */

struct rt_device_pwm *pwm_dev1;      /* PWM设备句柄 */
struct rt_device_pwm *pwm_dev2;      /* PWM设备句柄 */

 int pwm_led_sample()
{
    rt_uint32_t period, pulse, dir;

    period = 500000;    /* 周期为0.5ms，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */

    /* 设置LED引脚脚模式为输出 */
    rt_pin_mode(MotorA , PIN_MODE_OUTPUT);
    /* 拉高LED引脚 */
    rt_pin_write(MotorA , PIN_HIGH);

    /* 查找设备 */
    pwm_dev1 = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME1);
    if (pwm_dev1 == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME1);
        return RT_ERROR;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev1, PWM_DEV_CHANNEL1, period, pulse);
    /* 使能设备 */
    rt_pwm_enable(pwm_dev1, PWM_DEV_CHANNEL1);

	}

	