/*
   @file    STEVAL_MKBOXPRO_MEMS_FIFO_Interrupt.ino
   @author  STMicroelectronics
   @brief   Example to use the LSM6DSV16X library with FIFO status interrupts.
 *******************************************************************************
   Copyright (c) 2022, STMicroelectronics
   All rights reserved.

   This software component is licensed by ST under BSD 3-Clause license,
   the "License"; You may not use this file except in compliance with the
   License. You may obtain a copy of the License at:
                          opensource.org/licenses/BSD-3-Clause

 *******************************************************************************
*/
#include <LSM6DSV16XSensor.h>

#define SENSOR_ODR 104.0f // In Hertz
#define ACC_FS 2 // In g
#define GYR_FS 2000 // In dps
#define MEASUREMENT_TIME_INTERVAL (1000.0f/SENSOR_ODR) // In ms
#define FIFO_SAMPLE_THRESHOLD 199
#define FLASH_BUFF_LEN 8192
#define INT1_pin PA4
LSM6DSV16XSensor AccGyr(&Wire);

volatile uint8_t fullFlag = 0; // FIFO full flag

// ISR callback for INT1
void INT1_fullEvent_cb() {
  fullFlag = 1;
}

unsigned long timestamp_count = 0;
bool acc_available = false;
bool gyr_available = false;
int32_t acc_value[3];
int32_t gyr_value[3];
char buff[FLASH_BUFF_LEN];
uint32_t pos = 0;

void Read_FIFO_Data();

void setup() {
  
  Serial.begin(115200);
  Wire.begin();

  // Enable INT1 pin.
  attachInterrupt(INT1_pin, INT1_fullEvent_cb, RISING);
  
  // Initialize LSM6DSV16X.
  AccGyr.begin();
  AccGyr.Enable_X();
  AccGyr.Enable_G();
  
  // Configure ODR and FS of the acc and gyro
  AccGyr.Set_X_ODR(SENSOR_ODR);
  AccGyr.Set_X_FS(ACC_FS);
  AccGyr.Set_G_ODR(SENSOR_ODR);
  AccGyr.Set_G_FS(GYR_FS);
  
  // Configure FIFO BDR for acc and gyro
  AccGyr.FIFO_Set_X_BDR(SENSOR_ODR);
  AccGyr.FIFO_Set_G_BDR(SENSOR_ODR);

  // Set Set FIFO watermark level
  AccGyr.FIFO_Set_Watermark_Level(FIFO_SAMPLE_THRESHOLD);
  // Set FIFO stop on watermark level
  AccGyr.FIFO_Set_Stop_On_Fth(1);  
  // Enable FIFO full interrupt on sensor INT1 pin
  AccGyr.FIFO_Set_INT1_FIFO_Full(1); 
  // Set FIFO in Continuous mode
  AccGyr.FIFO_Set_Mode(LSM6DSV16X_STREAM_MODE);
  
  Serial.println("LSM6DSV16X FIFO Demo");
}

void loop() {
  uint8_t fullStatus = 0;
  
  // If we reach the threshold we can empty the FIFO
  if (fullFlag != 0) {
    fullFlag = 0;
    
    AccGyr.FIFO_Get_Full_Status(&fullStatus);

    if(fullStatus) {
      fullStatus = 0;
      
      // Empty the FIFO
      Read_FIFO_Data();
      
      // Print FIFO data
      Serial.print(buff);
    }
  }
}

void Read_FIFO_Data()
{
  uint16_t i;
  uint16_t samples_to_read;
  
  // Check the number of samples inside FIFO
  AccGyr.FIFO_Get_Num_Samples(&samples_to_read);
  
  for (i = 0; i < samples_to_read; i++) {
    uint8_t tag;
    
    // Check the FIFO tag
    AccGyr.FIFO_Get_Tag(&tag);
    switch (tag) {
      // If we have a gyro tag, read the gyro data
      case 1: {
          AccGyr.FIFO_Get_G_Axes(gyr_value);
          gyr_available = true;
          break;
        }
        
      // If we have an acc tag, read the acc data
      case 2: {
          AccGyr.FIFO_Get_X_Axes(acc_value);
          acc_available = true;
          break;
        }
        
      // We can discard other tags
      default: {
          break;
        }
    }
    // If we have the measurements of both acc and gyro, we can store them with timestamp
    if (acc_available && gyr_available) {
      int num_bytes;
      num_bytes = snprintf(&buff[pos], (FLASH_BUFF_LEN - pos), "%lu %d %d %d %d %d %d\r\n", (unsigned long)((float)timestamp_count * MEASUREMENT_TIME_INTERVAL), (int)acc_value[0], (int)acc_value[1], (int)acc_value[2], (int)gyr_value[0], (int)gyr_value[1], (int)gyr_value[2]);
      pos += num_bytes;
      timestamp_count++;
      acc_available = false;
      gyr_available = false;
    }
  }
  // We can add the termination character to the string, so we are ready to print it on hyper-terminal
  buff[pos] = '\0';
  pos = 0;
}
