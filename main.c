#include "main.h"


int count = 0;

void delay(uint32_t time)
{
	while(time--);
}

void GPIO_Config()
{
	RCC->CR |= 0x00030000; // HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000)); //HSEON Ready Flag wait
	RCC->CR |= 0x00080000; // CSS Enable
	RCC->PLLCFGR |= 0x00400000; // PLL e HSE seçtik
	RCC->PLLCFGR |= 0x0000004; // PLL M = 4
	RCC->PLLCFGR |= 0x00005A00; // PLL N = 168
	RCC->PLLCFGR |= 0x00000000; // PLL P = 2
	RCC->CFGR |= 0x00000000; // AHB Prescaler = 1
	RCC->CFGR |= 0x00080000; // APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400; // APB1 Prescaler = 4
	RCC->CIR |= 0x00080000; // HSERDY Flag clear
	RCC->CIR |= 0x00800000; // CSS Flag clear

	RCC->AHB1ENR = 0x00000009; // GPIOA ve GPIOD aktif

	GPIOD->MODER = 0x55000000; // 12,13,14,15. pin digital output
	GPIOD->OTYPER = 0x000000000; // 12,13,14,15. pins Push pull
	GPIOD->OSPEEDR = 0xFF000000; // 12,13,14,15. pins 100MHz
	GPIOD->PUPDR = 0x00000000; // 12,13,14,15. pins no pull
}
int main(void)
{

	GPIO_Config();
  while (1)
  {
	  if(GPIOA->IDR & 0x00000001)
	  {
		  while(GPIOA->IDR & 0x00000001);
		  delay(1680000);

		  count++;
	  }

	  if(count % 2 == 0)
		  GPIOD->ODR = 0x00000000;
	  else
		  GPIOD->ODR = 0x0000F000;

  }
}
