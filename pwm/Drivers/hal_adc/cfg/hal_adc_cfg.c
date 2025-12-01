#include "hal_adc.h"
#include "stm32f4xx_hal.h"

/* Table to connect user input to ADC_CHANNEL STM's macro */
static const uint32_t adc_channel_lookup[19] = {
    ADC_CHANNEL_0,  // 0
    ADC_CHANNEL_1,  // 1
    ADC_CHANNEL_2,  // 2
    ADC_CHANNEL_3,  // 3
    ADC_CHANNEL_4,  // 4
    ADC_CHANNEL_5,  // 5
    ADC_CHANNEL_6,  // 6
    ADC_CHANNEL_7,  // 7
    ADC_CHANNEL_8,  // 8
    ADC_CHANNEL_9,  // 9
    ADC_CHANNEL_10, // 10
    ADC_CHANNEL_11, // 11
    ADC_CHANNEL_12, // 12
    ADC_CHANNEL_13, // 13
    ADC_CHANNEL_14, // 14
    ADC_CHANNEL_15, // 15
    ADC_CHANNEL_16, // 16
    ADC_CHANNEL_17, // 17
    ADC_CHANNEL_18  // 18
};

static status_t adc_init_wrapper(void *ctx, uint8_t channel)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_HandleTypeDef *hadc1 = (ADC_HandleTypeDef *)ctx;
	ADC_ChannelConfTypeDef sConfig = {0};

    CHECK_NULL(ctx);
    CHECK_RANGE(channel, 0, 18);

    __HAL_RCC_GPIOA_CLK_ENABLE(); // PA0

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) */
	hadc1->Instance = ADC1;
	hadc1->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1->Init.Resolution = ADC_RESOLUTION_12B;
	hadc1->Init.ScanConvMode = DISABLE;
	hadc1->Init.ContinuousConvMode = ENABLE;
	hadc1->Init.DiscontinuousConvMode = DISABLE;
	hadc1->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1->Init.NbrOfConversion = 1;
	hadc1->Init.DMAContinuousRequests = ENABLE;
	hadc1->Init.EOCSelection = ADC_EOC_SEQ_CONV;
	if (HAL_ADC_Init(hadc1) != HAL_OK)
	{
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
	}

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. */
	sConfig.Channel = adc_channel_lookup[channel];
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(hadc1, &sConfig) != HAL_OK)
	{
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
	}

	return STATUS_OK;
}

static status_t adc_read_raw_wrapper(void *ctx, void *out)
{
	ADC_HandleTypeDef *hadc1 = (ADC_HandleTypeDef *)ctx;

    CHECK_NULL(ctx);

	if (HAL_ADC_Start(hadc1) != HAL_OK)
	{
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
	}

	if (HAL_ADC_PollForConversion(hadc1, HAL_MAX_DELAY) != HAL_OK)
	{
		__asm volatile ("cpsid i" : : : "memory");
		while (1);
	}

	(*(uint32_t *)out) = HAL_ADC_GetValue(hadc1);

    return STATUS_OK;
}

static const HAL_Adc_Driver_t adc_driver =
{
    .init     = adc_init_wrapper,
    .read = adc_read_raw_wrapper
};

const HAL_Adc_Driver_t* hal_adc_get_drv(void)
{
    return &adc_driver;
}
