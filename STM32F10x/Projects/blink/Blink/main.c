#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void delay(uint32_t n_delay);

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //Initialize default GPIO struct
    GPIO_StructInit(&GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    if (SysTick_Config(SystemCoreClock / 1000)) {
        while(1);
    }

    
    //Superloop
    while (1) {
        static int led_val = 0;
        GPIO_WriteBit(GPIOC, GPIO_Pin_9, (led_val) ? Bit_SET : Bit_RESET);
        led_val = 1 - led_val;
        delay(1000);
    }

    return 0;
}

static __IO uint32_t timing_delay;

void delay(uint32_t n_time)
{
    timing_delay = n_time;
    while(timing_delay != 0);
}

void SysTick_Handler(void)
{
    if (timing_delay != 0x00) {
        timing_delay--;
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
while (1);
}
#endif