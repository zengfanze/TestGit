//#include "os_event.h"
#include "uart.h"

BYTE xdata os_uart_buffer[UART_BUFFER_SIZE];
BYTE xdata os_uart_buffer_len = 0;
BYTE xdata os_uart_send_len = 0;
BYTE xdata rec_buf;
sbit LED_states = P3^3;
extern BOOL connnet_flag;
void os_uart_setup() //9600bps@22.1184MHz
{
	SCON = 0x50;		//8位数据,可变波特率

///定时器1作为波特率发生器
	AUXR |= 0x40;		//定时器时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;   //16位自动重装
	//定时器1作为波特率发生器
	//9600
	//TL1=0xC0;	
	//TH1=0xFD;
//	//19200
//	TL1 = 0xE0;
//	TH1 = 0xFE;
		//57600
//	TL1 = 0xA0;
//	TH1 = 0xFF;
//115200
	TL1 = 0xD0;
	TH1 = 0xFF;	
	//定时器1作为波特率发生器
	ET1=0;
	TR1=1;
//定时器2
//	AUXR |= 0x01;		//??1?????2???????
//	AUXR |= 0x04;		//???2???Fosc,?1T
//	T2L = 0xC0;		//??????
//	T2H = 0xFD;		//??????
//	AUXR |= 0x10;		//?????2
	ES      =   1;    //允许串口中断
  EA      =   1;    //开总中断
	LED_states =0;
}

void os_uart_push( BYTE c ) // 存储发送数据
{
	os_uart_buffer[os_uart_buffer_len] = c;
	os_uart_buffer_len += 1;
}

void os_uart_flush()   //发送数据入口函数
{
	if( os_uart_buffer_len )
	{
		os_uart_buffer_len--;
		os_uart_send_len = 0;
		SBUF = os_uart_buffer[os_uart_send_len];
	}
}

void uart() interrupt 4 using 2{
	if(RI) // receive  
	{
		rec_buf = SBUF;
		process_serial_data(rec_buf);
		RI = 0;
	}
	if(TI) //Send
	{
		if( os_uart_buffer_len ) //发送数据
		{
			os_uart_buffer_len--;
			os_uart_send_len++;
			SBUF = os_uart_buffer[os_uart_send_len];
		}
		TI = 0;
	}
}
BYTE reg_serial_states=0;
void process_serial_data(BYTE S_data)
{
	switch(reg_serial_states)
	{
		case 0:
			switch(S_data)
			{
				case 0x5A:
					reg_serial_states=1;
					break;
				default:
					reg_serial_states=0;
					break;
			}
			break;
		case 1:
			switch(S_data)
			{
				//重置连接。
				case 0x02:
					LED_states=0;
					connnet_flag=0;
					reg_serial_states=0;
					break;
				case 0x03:
					LED_states =1; //接收到下位机的信号，点亮LED
					connnet_flag =1; //连接成功
					reg_serial_states=0;
					break;
				case 0x04:
					LED_states =0; //接收到下位机的信号，关闭LED
					reg_serial_states=0;
					break;
				case 0x05:
					LED_states =1; //接收到下位机的信号，点亮LED
					reg_serial_states=0;
					break;
				default:
					reg_serial_states=0;
					break;
			}
			break;
		default:
			reg_serial_states=0;
			break;
		
	}
}

