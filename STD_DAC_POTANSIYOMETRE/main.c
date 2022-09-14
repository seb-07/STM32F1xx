#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC

uint16_t adcValue=0;
void gpioConfig(){
	
	GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//pot ve led clock aktif.
	
	GPIOInitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_4;
  
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

void dacConfig(){
	
	 
   DAC_InitTypeDef DACInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
   
   DACInitStructure.DAC_LFSRUnmask_TriangleAmplitude=DISABLE;
   DACInitStructure.DAC_OutputBuffer=ENABLE;
   DACInitStructure.DAC_Trigger=DAC_Trigger_None;
   DACInitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;
   
   DAC_Init(DAC_Channel_1,&DACInitStructure);
   DAC_Cmd(DAC_Channel_1,ENABLE);

}


int main(){
	gpioConfig();
	adcConfig();
	dacConfig();
	
	while(1){
		adcValue=readADC();
		
		DAC_SetChannel1Data(DAC_Channel_1,adcValue);
	}



}
