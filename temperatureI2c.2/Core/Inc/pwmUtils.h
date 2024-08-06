#pragma once // datoteka se ponavlja samo jednom da bi se izbjegle greške

#define TEMP_MIN 25.5
#define TEMP_MAX 28.0//određujemo raspon na kojo temperaturi se senzor upali i do koje vrijednosti PWM dosegne 100%

/* Sets initial PWM duty cycle and starts the TIM1 timer
 *
 * Params	startingPercentage		Initial duty cycle as a percentage, 0-100
 * 			htim1					handle to TIM1 used configure and start the clock
 * */
void initPwm(int startingPercentage, TIM_HandleTypeDef htim1);

/* Calculates integer PWM duty cycle percentage as a function of current temperature
 *
 * Params	temperature	current temperature
 * 			lowerBound	value under which the PWM duty cycle percentage will be 0
 * 			upperBound	value over which the PWM duty cycle percentage will be 100
 *
 * Returns	PWM duty cycle percentage
 *
 * Values between the lower and upper bound are linearly mapped to a percentage
 * E.g. For lb=20, ub=30, temp=25 will return 50, temp=22.5 25 and temp=27.5 75
 * */
int mapToPwm(float temperature, float lowerBound, float upperBound);

/* Updates the provided current PWM value in a circular pattern (0 20 40 60 80 100) and sends it to TIM1
 *
 * Params	currentPwmValue	current PWM duty cycle percentage
 *
 * Returns	new PWM duty cycle percentage
 * */
int circularIncrementPwm(int currentPwmValue);

/* Updates the provided current PWM value based on current temperature and sends it to TIM1
 *
 * Params	temperature	current temperature
 *
 * Returns	new PWM duty cycle percentage
 * */
int temperaturePwm(float temperature);
