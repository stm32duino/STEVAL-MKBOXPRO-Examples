/*
   @file    STEVAL_MKBOXPRO_MEMS_HelloWorld.ino
   @author  Giuseppe Roberti <giuseppe.roberti@ieee.org>
   @brief   Example to use the LSM6DSV16X, LIS2DU12, LPS22DF, LIS2MDL and
            STTS22H sensors
 *******************************************************************************
   Copyright (c) 2022, STMicroelectronics
   All rights reserved.
   This software component is licensed by ST under BSD 3-Clause license,
   the "License"; You may not use this file except in compliance with the
   License. You may obtain a copy of the License at:
                          opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
*/

#include <LPS22DFSensor.h>
#include <LIS2DU12Sensor.h>
#include <LSM6DSV16XSensor.h>
#include <LIS2MDLSensor.h>
#include <STTS22HSensor.h>

// Uncomment if you want to use SPI for LSM6DSV16X
// #define SPI_ENABLE

#define MCU_SEL PI0

#ifdef SPI_ENABLE

#define LIS2DU12_CS PI7
#define LSM6DSV16X_CS PI5

LIS2DU12Sensor LIS2DU12(&SPI, LIS2DU12_CS);
uint8_t LIS2DU12_id;
int32_t LIS2DU12_accel[3];

LSM6DSV16XSensor LSM6DSV16X(&SPI, LSM6DSV16X_CS);
uint8_t LSM6DSV16X_id;
int32_t LSM6DSV16X_accel[3], LSM6DSV16X_angrate[3];
#else
LIS2DU12Sensor LIS2DU12(&Wire);
uint8_t LIS2DU12_id;
int32_t LIS2DU12_accel[3];

LSM6DSV16XSensor LSM6DSV16X(&Wire);
uint8_t LSM6DSV16X_id;
int32_t LSM6DSV16X_accel[3], LSM6DSV16X_angrate[3];
#endif

LPS22DFSensor LPS22DF(&Wire);
uint8_t LPS22DF_id;
float LPS22DF_press, LPS22DF_temp;

LIS2MDLSensor LIS2MDL(&Wire);
uint8_t LIS2MDL_id;
int32_t LIS2MDL_magfield[3];

STTS22HSensor STTS22H(&Wire, STTS22H_I2C_ADD_H);
uint8_t STTS22H_id;
float STTS22H_temp;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin();

#ifdef SPI_ENABLE
  pinMode(MCU_SEL, OUTPUT);
  digitalWrite(MCU_SEL, LOW);
  SPI.begin();

  pinMode(LSM6DSV16X_CS, OUTPUT);
  digitalWrite(LSM6DSV16X_CS, HIGH);
  
  pinMode(LIS2DU12_CS, OUTPUT);
  digitalWrite(LIS2DU12_CS, HIGH);
#endif

  LPS22DF.begin();
  LPS22DF.Enable();
  LPS22DF.ReadID(&LPS22DF_id);
  Serial.printf("Initialized LPS22DF [ID:%d]\r\n", LPS22DF_id);

  LIS2DU12.begin();
  LIS2DU12.Enable_X();
  LIS2DU12.ReadID(&LIS2DU12_id);
  Serial.printf("Initialized LIS2DU12 [ID:%d]\r\n", LIS2DU12_id);

  LSM6DSV16X.begin();
  LSM6DSV16X.Enable_X();
  LSM6DSV16X.Enable_G();
  LSM6DSV16X.ReadID(&LSM6DSV16X_id);
  Serial.printf("Initialized LSM6DSV16X [ID:%d]\r\n", LSM6DSV16X_id);

  LIS2MDL.begin();
  LIS2MDL.Enable();
  LIS2MDL.ReadID(&LIS2MDL_id);
  Serial.printf("Initialized LIS2MDL [ID:%d]\r\n", LIS2MDL_id);

  STTS22H.begin();
  STTS22H.Enable();
  STTS22H.ReadID(&STTS22H_id);
  Serial.printf("Initialized STTS22H [ID:%d]\r\n]", STTS22H_id);
}

void loop() {
  LPS22DF.GetPressure(&LPS22DF_press);
  LPS22DF.GetTemperature(&LPS22DF_temp);
  Serial.print("Pressure:");
  Serial.print(LPS22DF_press);
  Serial.printf(",LPS22DF-Temp=");
  Serial.print(LPS22DF_temp);

  LIS2DU12.Get_X_Axes(LIS2DU12_accel);
  Serial.print(",Acc-X:");
  Serial.print(LIS2DU12_accel[0]);
  Serial.print(",Acc-Y:");
  Serial.print(LIS2DU12_accel[1]);
  Serial.print(",Acc-Z:");
  Serial.print(LIS2DU12_accel[2]);

  LSM6DSV16X.Get_X_Axes(LSM6DSV16X_accel);
  Serial.print(",Acc-X:");
  Serial.print(LSM6DSV16X_accel[0]);
  Serial.print(",Acc-Y:");
  Serial.print(LSM6DSV16X_accel[1]);
  Serial.print(",Acc-Z:");
  Serial.print(LSM6DSV16X_accel[2]);

  LSM6DSV16X.Get_G_Axes(LSM6DSV16X_angrate);
  Serial.print(",Gyro-X:");
  Serial.print(LSM6DSV16X_angrate[0]);
  Serial.print(",Gyro-Y:");
  Serial.print(LSM6DSV16X_angrate[1]);
  Serial.print(",Gyro-Z:");
  Serial.print(LSM6DSV16X_angrate[2]);

  LIS2MDL.GetAxes(LIS2MDL_magfield);
  Serial.print(",Mag-X:");
  Serial.print(LIS2MDL_magfield[0]);
  Serial.print(",Mag-Y:");
  Serial.print(LIS2MDL_magfield[1]);
  Serial.print(",Mag-Z:");
  Serial.print(LIS2MDL_magfield[2]);

  STTS22H.GetTemperature(&STTS22H_temp);
  Serial.print(",Temp=");
  Serial.print(LPS22DF_temp);

  Serial.println();

  blink(LED_BUILTIN);
}

inline void blink (int pin) {
  digitalWrite(pin, HIGH);
  delay(25);
  digitalWrite(pin, LOW);
  delay(975);
}

