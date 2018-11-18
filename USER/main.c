#include "sys.h"
#include "delay.h"
#include "usart.h"


UART_HandleTypeDef uart1_handler;  //串口句柄，结构体指针类型，定义为全局变量，很多地方都会使用到


void uart1_init()
{
	//编写串口相关初始化
	uart1_handler.Instance=USART1;  //初始化成员变量  //访问成员变量使用.   // 
	uart1_handler.Init.BaudRate=115200;		//Init 成员变量初始化一些串口参数
	uart1_handler.Init.WordLength=UART_WORDLENGTH_8B; //去hal_uart.c中去找相应的函数对应的取值
	uart1_handler.Init.StopBits=UART_STOPBITS_1;
	uart1_handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	uart1_handler.Init.Mode=UART_MODE_TX_RX;
	uart1_handler.Init.Parity=UART_PARITY_NONE;  //奇偶校验位
	HAL_UART_Init(&uart1_handler);  //注意，指向地址,括号里填指针参数
	
}
	//串口相关IO口配置，复用配置：在HLA_UART_MspInit中调用HAL_GPIO_Init函数
	//先重写上面MspInit弱函数，里面调用GPIO_Init函数进行复用映射的配置
	//编写MspInit函数，目的：外设的复用映射和串口的初始化和一些中断优先级设置，这个函数最终会给HAL_UART_Init调用
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;		//GPIO端口设置
	
	if(huart->Instance==USART1) //因为stm32又很多串口，所以这里先进行判断  //如果是串口1，进行串口1 MSP初始化
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			//使能GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();			//使能USART1时钟
		//初始化IO口
		GPIO_Initure.Pin=GPIO_PIN_9; //PA9 //取值参考IO口实验
		GPIO_Initure.Mode=GPIO_MODE_AF_PP; //复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;	//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST; 	//高速
		GPIO_Initure.Alternate=GPIO_AF7_USART1;		//设置映射  初始化PA9
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);  //初始化PA9
		
		GPIO_Initure.Pin=GPIO_PIN_10; 	//PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); //初始化PA10
	}
}



int main(void)
{
	
	u8 buff[] = "test\r\n";
	HAL_Init();
	Stm32_Clock_Init(360,25,2,8); //时钟主频180Mhz
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

