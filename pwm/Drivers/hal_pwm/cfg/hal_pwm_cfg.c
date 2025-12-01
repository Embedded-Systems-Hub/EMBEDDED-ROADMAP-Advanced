#include "hal_pwm.h"
#include "stm32f4xx_hal.h"

/* Table to connect user input to ADC_CHANNEL STM's macro */
static const uint32_t tim_channel_lookup[5] = {
    0,
    TIM_CHANNEL_1,   // 1
    TIM_CHANNEL_2,   // 2
    TIM_CHANNEL_3,   // 3
    TIM_CHANNEL_4    // 4
};

static status_t pwm_init_wrapper(void *ctx, uint8_t channel)
{
	TIM_HandleTypeDef *htim4 = (TIM_HandleTypeDef *)ctx;
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};

    CHECK_NULL(ctx);
    CHECK_RANGE(channel, 1, 4);

    htim4->Instance = TIM4;
    htim4->Init.Prescaler = 0;
    htim4->Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4->Init.Period = 4095;
    htim4->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(htim4) != HAL_OK)
    {
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(htim4, &sClockSourceConfig) != HAL_OK)
    {
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
    }
    if (HAL_TIM_PWM_Init(htim4) != HAL_OK)
    {
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(htim4, &sMasterConfig) != HAL_OK)
    {
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(htim4, &sConfigOC, tim_channel_lookup[channel]) != HAL_OK)
    {
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_TIM_PWM_Start(htim4, tim_channel_lookup[channel]);

    return STATUS_OK;
}

static status_t pwm_set_wrapper(void *ctx, const void *in)
{
	uint32_t value = (*(uint32_t *)in);

    CHECK_NULL(ctx);
    CHECK_RANGE(value, 0, 4095);

	TIM4->CCR1 = value;

    return STATUS_OK;
}

static const HAL_PWM_Driver_t pwm_driver =
{
    .init = pwm_init_wrapper,
    .set  = pwm_set_wrapper
};

const HAL_PWM_Driver_t* hal_pwm_get_drv(void)
{
    return &pwm_driver;
}
