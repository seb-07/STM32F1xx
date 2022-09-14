#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adcValue=0;
uint16_t digital=0;
void gpioConfig(){
   GPIO_InitTypeDef GPIOInitStructure;
   //ir sensor
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
   
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_AIN;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;
   GPIO_Init(GPIOA,&GPIOInitStructure);
}
void adcConfig(){
   ADC_InitTypeDef ADCInitStructure;
   
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//adc clock enable
   
   ADCInitStructure.ADC_ContinuousConvMode=ENABLE;
   ADCInitStructure.ADC_DataAlign=ADC_DataAlign_Right;
   ADCInitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
   ADCInitStructure.ADC_Mode=ADC_Mode_Independent;
   ADCInitStructure.ADC_NbrOfChannel=1;
   ADCInitStructure.ADC_ScanConvMode=DISABLE;
   
   ADC_Init(ADC1,&ADCInitStructure);
   ADC_Cmd(ADC1,ENABLE);
}

uint16_t readADC(){
   
   ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
   ADC_SoftwareStartConvCmd(ADC1,ENABLE);
   
   while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
   
   return ADC_GetConversionValue(ADC1);

}

uint16_t toDigital(uint16_t adcValue){
	
	if(adcValue>3000){
		return 1;
		
	}else{
		
		return 0;
	}
	
}

int main(){
	gpioConfig();
	adcConfig();
	
	while(1){
		adcValue=readADC();
		digital=toDigital(adcValue);
	
	}




}

