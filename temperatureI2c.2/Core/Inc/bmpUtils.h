#pragma once

#include "stm32f4xx_hal.h"
#include "bmp280.h"

typedef struct SensorData { /*definicija i deklaracija senzordata u jedan*/
  float temperature;
  float pressure;/*članovi od senzor data*/
  float humidity;
  bool bme280p; /*boolian koji kpristimo kod određivanja je li u pitanju bmp ili bme senzor*/
} sensorData;

/* Connect to, configure and probe a BMP sensor
 *
 * Params	hi2c1	I2C handle used to talk with the sensor
 *
 * Returns	Handle to a configured and ready-to-use BMP sensor
 * */
BMP280_HandleTypedef initBmpSensor(I2C_HandleTypeDef* hi2c1);

/* Reads and prints temperature, pressure and, if available, humidity from a BMP sensor
 *
 * Params	bmp280	Handle to a configured and ready-to-use BMP sensor
 *
 * Returns	Struct containing the measured data and flag if humidity was measured
 * */
sensorData readAndPrintData(BMP280_HandleTypedef bmp280); /*Linija 132 u main.c, deklaracija, poziva se u main.c*/
