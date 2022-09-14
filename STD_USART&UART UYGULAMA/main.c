#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include <stdio.h>
#include "delay.h"


uint16_t data=0;
char message[20];

void gpioConfig(void);
void adcConfig(void);
uint16_t readADC(void);
void delay(uint32_t time);
void uartConfig(void);
void uartTransmit(char *string);

void gpioConfig(){
   GPIO_InitTypeDef GPIOInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
   
	
	//ADC
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_AIN;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;
   GPIO_Init(GPIOA,&GPIOInitStructure);
   
   
   //TX->PA9 AND RX->PA10
   
   //TX
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_9;
   GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIOInitStructure);
   
   //RX
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_10;
   GPIO_Init(GPIOA,&GPIOInitStructure);
}


void adcConfig(){
   ADC_InitTypeDef ADCInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
   
   ADCInitStructure.ADC_ContinuousConvMode=ENABLE;
   ADCInitStructure.ADC_DataAlign= ADC_DataAlign_Right;
   ADCInitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
   ADCInitStructure.ADC_Mode=ADC_Mode_Independent;
   ADCInitStructure.ADC_NbrOfChannel=1;
   ADCInitStructure.ADC_ScanConvMode=DISABLE;
   
   ADC_Init(ADC1,&ADCInitStructure);
   ADC_Cmd(ADC1,ENABLE);
}

void uartConfig(){
   USART_InitTypeDef UARTInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
   
   UARTInitStructure.USART_BaudRate=9600;
   UARTInitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
   UARTInitStructure.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
   UARTInitStructure.USART_Parity=USART_Parity_No;
   UARTInitStructure.USART_StopBits=USART_StopBits_1;
   UARTInitStructure.USART_WordLength=USART_WordLength_8b;
   
   USART_Init(USART1,&UARTInitStructure);
   USART_Cmd(USART1,ENABLE);
}

uint16_t readADC(){
   
   ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
   
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);
   
   while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
   
   return ADC_GetConversionValue(ADC1);
}

void uartTransmit(char *string){
	
   while(*string){
      while(!(USART1->SR & 0x00000040));
      USART_SendData(USART1,*string);
      *string++;

   }
}



int main(){
   gpioConfig();
   adcConfig();
   uartConfig();
   DelayInit();
   
   while(1){
      data=readADC();
      sprintf(message,"%d\n",data);
      uartTransmit(message);
      delay_ms(500);
   }


}

