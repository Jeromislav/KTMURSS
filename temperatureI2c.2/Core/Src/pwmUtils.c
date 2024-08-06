#include <stdlib.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"

#include "pwmUtils.h"

void initPwm(int startingPercentage, TIM_HandleTypeDef htim1)
{
	if ((startingPercentage < 0) | (startingPercentage > 100))
	{
		printf("PWM duty=%d is invalid, using 0 instead\r\n", startingPercentage);
		startingPercentage = 0;
	}

	TIM1->CCR1 = startingPercentage; // set capture-compare register for channel (ARR is 100, so this is a direct percentage)
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // starting the TIM1 in PWM mode
}

int mapToPwm(float temperature, float lowerBound, float upperBound)
{
    if (temperature <= lowerBound)
    {
    	return 0;
    }
    else if (temperature >= upperBound)//račun pretvaranja u PWM vrijednost, tj. koliko će biti postotak PWM-a
    {
    	return 100;
    }
    else
    {
    	return (int)(((temperature - lowerBound) * 100) / (upperBound - lowerBound) ); // račun za dobivanje postotka
    }
}

int circularIncrementPwm(int currentPwmValue)
{
	int newPwmValue = currentPwmValue + 20;
	if (newPwmValue > 100)	// PWM % will go 0 20 40 60 80 100
	{
		newPwmValue = 0;
	}
	printf("Setting PWM duty to=%d\r\n", newPwmValue);
	TIM1->CCR1 = newPwmValue;

	return newPwmValue;
}

int temperaturePwm(float temperature)
{
	int newPwmValue = mapToPwm(temperature, TEMP_MIN, TEMP_MAX);
	printf("For measured T=%.2f C, setting PWM duty to=%d\r\n", temperature, newPwmValue);
	TIM1->CCR1 = newPwmValue; //TIM capture/compare register 1

	return newPwmValue;
}
