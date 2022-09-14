#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adcValue=0;
float voltage=0;
float mapValue=0;
void gpioConfig(){
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0;
	
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

uint16_t readADC(){
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);
}

float map(float adcValue, float max, float min, float conMax, float conMin){
	
	return adcValue*((conMax-conMin)/(max-min));
}
int main(){
	gpioConfig();
	adcConfig();
	
	while(1){
		adcValue=readADC();
		voltage=adcValue*(2.98/4030);
		mapValue=map(adcValue,4030,0,180,0);
		
	}




}
	
