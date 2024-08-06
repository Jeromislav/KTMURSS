#include <stdlib.h>
#include <stdio.h>

#include <bmpUtils.h>

BMP280_HandleTypedef initBmpSensor(I2C_HandleTypeDef* hi2c1)
{
	BMP280_HandleTypedef bmp280;

	// configure settings
	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = hi2c1;

	// try to connect and initialize
	while (!bmp280_init(&bmp280, &bmp280.params)) {/*čita memoriju radi IDa i zapisuje postavke(mod rada, filtriranje, uzorkovanje, čekanje između mjerenja)*/
		printf("BMP280 initialization failed\r\n");
		HAL_Delay(2000);
	}

	// print exact detected sensor type
	bmp280.bme280p = bmp280.id == BME280_CHIP_ID;/*uspoređije ID da bi utvrtili koji je senzor u pitanju*/
	printf("BMP280: found %s\r\n", bmp280.bme280p ? "BME280" : "BMP280"); /*uspoređuje i ovisno o tome izvršit će "BME280" ili BMP280*/

	return bmp280;
}

sensorData readAndPrintData(BMP280_HandleTypedef bmp280)/*Definicija read and print funkcije, bmpUtils.h*/
{
	sensorData s = {0.0, 0.0, 0.0, false}; /*inicijalizacija varijable s-senzor data (3 floata i jedan bool)*/
	s.bme280p = bmp280.bme280p;/*s. i bmp280 su strukture koje sadrže boolian a u tom boolianu se nalazi info o tipu senzora*/

	// read the data from sensor
	while (!bmp280_read_float(&bmp280, &(s.temperature), &(s.pressure), &(s.humidity))) {/*funkcija readfloat čita navedene podatke*/
		printf("Temperature/pressure reading failed\r\n");
		TIM1->CCR1 = 0; //set PWM to 0 just in case /*stavljamo da PWM duty cycle u 0(gasimo napon) i svrha je da ako pročitamo krivu vrijednost da s njome ne upravljamo PWMom nego da radije uzgasimo ventilator*/
		HAL_Delay(2000);
	}

	// print temperature
	// Go to Project/Settings/C/C++ Build/Settings/MCU settings and enable "Use float with printf from newlib-nano (-u _printf_float)
	printf("Pressure: %.2f Pa, Temperature: %.2f C", s.pressure, s.temperature);

	// print humidity if it is available
	if (bmp280.bme280p) {
		printf(", Humidity: %.2f\r\n", s.humidity);/*linija 31*/
	}
	else {
		printf("\r\n");
	}

	return s; /**/
}
