#include <rtthread.h>
#include <rtdevice.h>
#include "math.h"
#include "app_uSart.h"
#include "Display.h"
/********把数字转为ASCII*********/
/*****************把数值转为ASII****/
void Value_Asii(uint8_t uart_value,float value)
{

	uint8_t ch1[12];
	uint8_t i=0;
	uint32_t num;
	uint16_t num1;
	num=(uint32_t)fabs(value);

			
			num1=(value-num)*100;
			ch1[0]=num/1000000+48;
			ch1[1]=num%1000000/100000+48;
			ch1[2]=num%1000000%100000/10000+48;
			ch1[3]=num%1000000%100000%10000/1000+48;
			ch1[4]=num%1000000%100000%10000%1000/100+48;
			ch1[5]=num%1000000%100000%10000%1000%100/10+48;
			ch1[6]=num%1000000%100000%10000%1000%100%10+48;
			ch1[7]=46;
			ch1[8]=num1/10+48;
			ch1[9]=num1%10+48;
			
			if(uart_value==3)
				{
						for(i=0;i<10;i++)
					{
							if(ch1[i]!=48||i>=6)
							{
								uart3_putchar(ch1[i]);
							}
					}
				}
			if(uart_value==1)
				{
						for(i=0;i<10;i++)
					{
							if(ch1[i]!=48||i>=6)
							{
								uart1_putchar(ch1[i]);
							}
					}
				}
			if(uart_value==2)
				{
						for(i=0;i<10;i++)
					{
							if(ch1[i]!=48||i>=6)
							{
								uart2_putchar(ch1[i]);
							}
					}
				}
}
	