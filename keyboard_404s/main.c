#include "config.h"
#include "uart.h"
//#include "os_event.h"

//sbit key1 = P2^0;
//sbit key2 = P2^1;
//sbit key3 = P2^2;
//sbit key4 = P2^3;
//sbit key5 = P2^4;
//sbit key6 = P2^5;
//sbit key7 = P2^6;
//sbit key8 = P2^7;
#define DEBUG 0

#define hander_keys P2
#define SendModel 0

BOOL connnet_flag;
BOOL speed_flag;
WORD states_keys;
void Delay10ms();
void scan_keys();
void scan_keyboard();
void send_D_data(WORD D_data);
void send_data(BYTE param);
void send_8byte_data(BYTE param1,BYTE param2,BYTE param3,BYTE param4);

void main(void)
{
	EA=1;
	P2M0 = 0x00;
  P2M1 = 0x00;
	connnet_flag =0;
	speed_flag =1;
	os_uart_setup();
	os_uart_push(0x11);
	os_uart_push(0x22);
	os_uart_flush();
	
	//sendData(0x01);
	
	while(1){
	//scan_keys();
//	if(!connnet_flag)
//	{
//	//������λ��Ӧ��
//	os_uart_push(0x5A);
//	os_uart_push(0x03);
//	os_uart_push(0xFF);		
//	os_uart_flush();
//	Delay10ms();
//	Delay10ms();	
//	}		
//	else{
	//states_keys = 0xFFFF;
  //scan_keyboard();
	//����״̬ɨ��
		if(states_keys != hander_keys)
		{
			Delay10ms();
			if(states_keys != hander_keys)
			{
			//������Ч���ͷ���ָ�
			//os_uart_push(hander_keys);
			//os_uart_flush();
			states_keys = hander_keys;
			switch(states_keys)
			{
				//ֹͣ״̬
				case 0xFF:
					#if SendModel
						send_D_data(0xFFFF);
					#else
						send_data(0x00);
					#endif
					speed_flag=1;
					break;
				//ǰ��
				case 0xFE:
					if(speed_flag){
						#if SendModel
							send_D_data(0xEFFF);
						#else
							send_data(0x01);
						#endif
					}
					speed_flag=1;
					break;
				//����
				case 0xFD:
					if(speed_flag){
						#if SendModel
							send_D_data(0xDFFF);
						#else
							send_data(0x02);
						#endif
					
					}
					speed_flag =1;
					break;
				//��ת
				case 0xFB:
					if(speed_flag){
						#if SendModel	
							send_D_data(0xBFFF);
						#else
							send_data(0x03);
						#endif
					
					}
					speed_flag=1;
					break;
				//��ת
				case 0xF7:
					if(speed_flag){
						#if SendModel	
							send_D_data(0x7FFF);
						#else
							send_data(0x04);
						#endif
					}
					speed_flag=1;
					break;
				//����,�����ٶ�
				case 0xEF:
				case 0xEE:
				case 0xED:
				case 0xEB:
				case 0xE7:
					#if SendModel
						send_D_data(0xFFEF);
					#else
						send_data(0x05);
					#endif
					speed_flag =0;
					break;
				//�����ٶ�
				case 0xDF:
				case 0xDE:
				case 0xDD:
				case 0xDB:
				case 0xD7:
					#if SendModel
						send_D_data(0xFFDF);
					#else
						send_data(0x06);
					#endif
					
					speed_flag=0;
					break;
				//���ⲿ��բ
				case 0xBF:
					#if SendModel
						send_D_data(0xFFBF);
					#else
						send_data(0x07);
					#endif
					speed_flag =0;
					break;
				//
				case 0x7F:
					#if SendModel
						send_D_data(0xFF7F);
						#else
					#endif
					speed_flag =0;
					break;
				//ʹ���ֱ�
				case 0x1F:
					#if SendModel
						send_D_data(0xFF1F);
					#else
					#endif
					break;
				//�ر��ֱ�
				case 0x2F:
					#if SendModel
						send_D_data(0xFF2F);
					#else
					#endif
					break;
				//����
				case 0x87:
					connnet_flag=0;
					break;
				default:
					speed_flag =1;
					break;
			}
			}
		else{};//do nothing;��������
		}
	//}//else
	};//while(1)
}
void send_D_data(WORD D_data)
{
	os_uart_push(0x5A);
	os_uart_push(D_data>>8);
	os_uart_push(D_data);
	os_uart_flush();
}
void send_data(BYTE param)
{
	switch(param)
	{
		//ֹͣ
		case 0x00:
			send_8byte_data(0x02,0x00,0x00,0x00);
			break;
		//ǰ��
		case 0x01:
			send_8byte_data(0x02,0x01,0x00,0x00);
			break;
		//����
		case 0x02:
			send_8byte_data(0x02,0x02,0x00,0x00);	
			break;
		//��ת
		case 0x03:
			send_8byte_data(0x02,0x03,0x00,0x00);	
			break;
		//��ת
		case 0x04:
			send_8byte_data(0x02,0x04,0x00,0x00);	
			break;
		//�����ٶ�
		case 0x05:
			send_8byte_data(0x01,0xCD,0x00,0x00);	
			break;
		//�����ٶ�
		case 0x06:
			send_8byte_data(0x01,0xCE,0x00,0x00);	
			break;
		//���ⲿ��բ
		case 0x07:
			send_8byte_data(0x02,0x05,0x00,0x00);	
			break;
		case 0x08:
			break;
		case 0x09:
			break;
		case 0x0A:
			break;
		case 0x0B:
			break;
		case 0x0C:
			break;
		case 0x0D:
			break;
		case 0x0E:
			break;
		case 0x0F:
			break;
	}
}
void send_8byte_data(BYTE param1,BYTE param2,BYTE param3,BYTE param4)
{
	os_uart_push(0x55);
	os_uart_push(0xAA);
	os_uart_push(param1);
	os_uart_push(param2);
	os_uart_push(param3);
	os_uart_push(param4);
	os_uart_push(0xAA);
	os_uart_push(0x55);
	os_uart_flush();
}

//��������
//void scan_keyboard()
//{
//	hander_keys = 0xFF;
//	if(hander_keys != 0xFF)
//	{
//		Delay10ms();
//		if(hander_keys != 0xFF)
//		{
//			if (DEBUG){
//			os_uart_push(hander_keys);
//			os_uart_flush();
//			}
//			//��4λ
//			hander_keys = 0x0F;
//			switch(hander_keys)
//			{
//				case 0x0E:
//					states_keys =  states_keys & (0xEFFF);
//					if (DEBUG){
//					os_uart_push(0x01);
//					os_uart_flush();
//					}
//					break;
//				case 0x0D:
//					states_keys =  states_keys & (0xBFFF);
//					if (DEBUG){
//					os_uart_push(0x02);
//					os_uart_flush();
//					}
//					break;
//				case 0x0B:
//					states_keys =  states_keys & (0x7FFF);
//				if (DEBUG){
//				os_uart_push(0x04);
//					os_uart_flush();
//				}
//					break;
//				case 0x07:
//					states_keys =  states_keys & (0xDFFF);
//				if (DEBUG){
//					os_uart_push(0x08);
//					os_uart_flush();
//				}
//					break;	
//			}
//			//��4λ
//			hander_keys = 0xF0;
//			switch(hander_keys)
//			{
//				case 0xE0:
//					states_keys =  states_keys & (0xFFEF);
//				if (DEBUG){
//					os_uart_push(0x10);
//					os_uart_flush();
//				}
//					break;
//				case 0xD0:
//					states_keys =  states_keys & (0xFFBF);
//				if (DEBUG){
//				os_uart_push(0x20);
//					os_uart_flush();
//				}
//					break;
//				case 0xB0:
//					states_keys =  states_keys & (0xFF7F);
//				if (DEBUG){
//					os_uart_push(0x40);
//					os_uart_flush();
//				}
//					break;
//				case 0x70:
//					states_keys =  states_keys & (0xFFDF);
//				if (DEBUG){
//					os_uart_push(0x80);
//					os_uart_flush();
//				}
//					break;	
//			}
//		}
//	}
//}


void Delay10ms()		//@22.1184MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 1;
	j = 216;
	k = 35;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
