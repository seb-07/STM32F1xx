#include "stm32f10x.h"                  // Device header
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART

char testMessage[25]="Arif Mandal\r\n";

char gelenVeri=0;

void gpioConfig(){
	
	GPIO_InitTypeDef GPIOInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//TX->PA9 AND RX->PA10
	
	
	//TX->PA9
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	
	//RX->PA10
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIOInitStructure);
	
	
	//PB0,PB1 LEDS
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOInitStructure);
	

}

void usartConfig(){
	USART_InitTypeDef USARTInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	
	USARTInitStructure.USART_BaudRate=9600;
	USARTInitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USARTInitStructure.USART_Mode=USART_Mode_Tx |USART_Mode_Rx;
	USARTInitStructure.USART_Parity=USART_Parity_No;
	USARTInitStructure.USART_StopBits=USART_StopBits_1;
	USARTInitStructure.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART1,&USARTInitStructure);
	USART_Cmd(USART1,ENABLE);
	
}

void usartTranmit(char *string){
	
	while(*string){
		while(!(USART1 ->SR & 0x00000040));
		USART_SendData(USART1,*string);
		*string++;
	}
}

void delay(uint32_t time){
	while(time--);


}
int main(){
	
	gpioConfig();
	usartConfig();
	
	while(1){
		
//		usartTranmit(testMessage);
//		delay(36000000);
		
		gelenVeri=USART_ReceiveData(USART1);
		
		if(gelenVeri=='0'){
			GPIO_SetBits(GPIOB,GPIO_Pin_0);

		}if(gelenVeri=='1'){
			GPIO_SetBits(GPIOB,GPIO_Pin_1);

		}if(gelenVeri=='2'){
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);

		}if(gelenVeri=='3'){
			GPIO_ResetBits(GPIOB,GPIO_Pin_1);

		}
		
	
	}



}

