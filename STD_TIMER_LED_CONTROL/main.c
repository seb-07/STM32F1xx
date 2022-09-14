#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM


void gpioConfig(){
   
   GPIO_InitTypeDef GPIOInitStructure;
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
   
   GPIOInitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
   GPIOInitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2;
   GPIOInitStructure.GPIO_Speed=GPIO_Speed_50MHz;
   
   GPIO_Init(GPIOA,&GPIOInitStructure);

}

void timerConfig(){
   
   TIM_TimeBaseInitTypeDef TIMERInitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
   TIMERInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
   TIMERInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIMERInitStructure.TIM_Prescaler=10;
   TIMERInitStructure.TIM_Period=2399;
   TIMERInitStructure.TIM_RepetitionCounter=0;
   
   TIM_TimeBaseInit(TIM2,&TIMERInitStructure);
   TIM_Cmd(TIM2,ENABLE);

}


void pwmConfig(uint32_t timPulse){
   
   TIM_OCInitTypeDef TIMER_OCInitStructure;
   TIMER_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIMER_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIMER_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
   TIMER_OCInitStructure.TIM_Pulse=timPulse;

   TIM_OC1Init(TIM2,&TIMER_OCInitStructure);
   TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);

}

void pwm1Config(uint32_t timPulse){
   
   TIM_OCInitTypeDef TIMER_OCInitStructure;
   TIMER_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIMER_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIMER_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
   TIMER_OCInitStructure.TIM_Pulse=timPulse;

   TIM_OC2Init(TIM2,&TIMER_OCInitStructure);
   TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);

}
void pwm2Config(uint32_t timPulse){
   
   TIM_OCInitTypeDef TIMER_OCInitStructure;
   TIMER_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
   TIMER_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
   TIMER_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
   TIMER_OCInitStructure.TIM_Pulse=timPulse;

   TIM_OC3Init(TIM2,&TIMER_OCInitStructure);
   TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);

}

void delay(uint32_t time ){

   while(time--);


}

int main(){
   gpioConfig();
   timerConfig();
   
   
   while(1){
//		 for(int i=1;i<2399;i++){
//		     pwmConfig(i);
//			 delay(3600);
//		 }
//		 for(int i=1;i<2399;i++){
//		     pwm1Config(i);
//			  delay(3600);
//		 }
//		 for(int i=1;i<2399;i++){
//		     pwm2Config(i);
//			  delay(3600);
//		 }
		  pwmConfig(2399);
		  pwm1Config(0);
		  pwm2Config(0);
		 delay(360000);
		 pwmConfig(0);
		  pwm1Config(2399);
		  pwm2Config(0);
		 delay(360000);
		 pwmConfig(0);
		  pwm1Config(0);
		  pwm2Config(2399);
			delay(360000);
		 
		 
		 
 
   }



}
