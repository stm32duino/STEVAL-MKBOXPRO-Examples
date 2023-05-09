/*
   @file    STEVAL_MKBOXPRO_Python_Wave_Serial_Encoder.ino
   @author  Giuseppe Roberti <giuseppe.roberti@ieee.org>
   @brief   PCM Audio recording using MP23DB01HP mems microphone on STEVAL-MKBOXPRO
 *******************************************************************************
   Copyright (c) 2022, STMicroelectronics
   All rights reserved.
   This software component is licensed by ST under BSD 3-Clause license,
   the "License"; You may not use this file except in compliance with the
   License. You may obtain a copy of the License at:
                          opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
*/

#include <Arduino.h>
#include <PCM.h>

uint16_t RecBuff[PCM_REC_BUFF_SIZE];

int sending;

void process()
{
  Serial.write((const uint8_t *)RecBuff, PCM_REC_BUFF_SIZE * 2U);
}

void setup()
{
  Serial.begin(921600);
  while (!Serial);

  int ret = PCM.Begin();

  if (ret) {
    Serial.println("Unable to initialize PCM.");

    while(1);
  }

  PCM.OnReceive(process);

  Serial.printf("Operative.");
}

void loop()
{
  if (Serial.available() < 1) {
    delay(100);

    return;
  }

  sending = Serial.read();

  if (sending == '\r' || sending == '\n') return;

  int ret;

  // Pause Recording
  if (sending == 0 || sending == '0') {
    ret = PCM.Pause();

    if (ret) {
      Serial.println("Unable to pause recording.");

      while(1);
    }
  }

  // Start Recording
  if (sending == 1 || sending == '1') {
    if (PCM.GetState() == PCM_AUDIO_IN_STATE_PAUSE) {
      ret = PCM.Resume();
    } else {
      ret = PCM.Record(RecBuff);
    }

    if (ret) {
      Serial.println("Unable to start recording.");

      while(1);
    }
  }

  // End Recording
  if (sending == 2 || sending == '2') {
    if (PCM.GetState() == PCM_AUDIO_IN_STATE_RECORDING) {
      ret = PCM.Stop();

      if (ret) {
        Serial.println("Unable to stop recording.");

        while(1);
      }
    }

    ret = PCM.End();

    if (ret) {
      Serial.println("Unable to deinitialize PCM.");
    } else {
      Serial.println("PCM deinitialized. Operations halted.");
    }

    while(1);
  }
}
