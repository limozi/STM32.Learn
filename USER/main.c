#include "sys.h"
#include "delay.h"
#include "usart.h"


UART_HandleTypeDef uart1_handler;  //���ھ�����ṹ��ָ�����ͣ�����Ϊȫ�ֱ������ܶ�ط�����ʹ�õ�


void uart1_init()
{
	//��д������س�ʼ��
	uart1_handler.Instance=USART1;  //��ʼ����Ա����  //���ʳ�Ա����ʹ��.   // 
	uart1_handler.Init.BaudRate=115200;		//Init ��Ա������ʼ��һЩ���ڲ���
	uart1_handler.Init.WordLength=UART_WORDLENGTH_8B; //ȥhal_uart.c��ȥ����Ӧ�ĺ�����Ӧ��ȡֵ
	uart1_handler.Init.StopBits=UART_STOPBITS_1;
	uart1_handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	uart1_handler.Init.Mode=UART_MODE_TX_RX;
	uart1_handler.Init.Parity=UART_PARITY_NONE;  //��żУ��λ
	HAL_UART_Init(&uart1_handler);  //ע�⣬ָ���ַ,��������ָ�����
	
}
	//�������IO�����ã��������ã���HLA_UART_MspInit�е���HAL_GPIO_Init����
	//����д����MspInit���������������GPIO_Init�������и���ӳ�������
	//��дMspInit������Ŀ�ģ�����ĸ���ӳ��ʹ��ڵĳ�ʼ����һЩ�ж����ȼ����ã�����������ջ��HAL_UART_Init����
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;		//GPIO�˿�����
	
	if(huart->Instance==USART1) //��Ϊstm32�ֺܶമ�ڣ����������Ƚ����ж�  //����Ǵ���1�����д���1 MSP��ʼ��
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹ��GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();			//ʹ��USART1ʱ��
		//��ʼ��IO��
		GPIO_Initure.Pin=GPIO_PIN_9; //PA9 //ȡֵ�ο�IO��ʵ��
		GPIO_Initure.Mode=GPIO_MODE_AF_PP; //�����������
		GPIO_Initure.Pull=GPIO_PULLUP;	//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST; 	//����
		GPIO_Initure.Alternate=GPIO_AF7_USART1;		//����ӳ��  ��ʼ��PA9
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);  //��ʼ��PA9
		
		GPIO_Initure.Pin=GPIO_PIN_10; 	//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); //��ʼ��PA10
	}
}



int main(void)
{
	
	u8 buff[] = "test\r\n";
	HAL_Init();
	Stm32_Clock_Init(360,25,2,8); //ʱ����Ƶ180Mhz
	delay_init(180);
	uart1_init();
	while(1)
	{
		HAL_UART_Transmit(&uart1_handler, buff, sizeof(buff), 1000 );
		
		delay_ms(300);
		
		
		// just for test git 
//		HAL_UART_Transmit(&uart1_handler, buff, sizeof(buff1), 1000 );
//		
//		delay_ms(300);
	}
		
}

