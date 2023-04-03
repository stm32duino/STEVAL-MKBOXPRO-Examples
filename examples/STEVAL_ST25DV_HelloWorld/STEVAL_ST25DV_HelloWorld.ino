/*
   @file    STEVAL_Python_Wave_Serial_Encoder.ino
   @author  STMicroelectronics
   @brief   Test application for ST25DV NFC device on STEVAL
 *******************************************************************************
   Copyright (c) 2022, STMicroelectronics
   All rights reserved.
   This software component is licensed by ST under BSD 3-Clause license,
   the "License"; You may not use this file except in compliance with the
   License. You may obtain a copy of the License at:
                          opensource.org/licenses/BSD-3-Clause
 *******************************************************************************
*/

/**
******************************************************************************
  How to use this sketch

  This sketch uses the I2C interface to communicate with the NFC device.
  It writes an NFC tag type URI (Uniform Resource Identifier) and reads this same tag.
  Choose the uri by changing the content of uri_write.

  When the NFC module is started and ready, the green LED switches ON else it blinks.
  Next, the tag is written, the blue LED switches ON else it blinks.
  Then read is performed, the yellow LED switches ON else it blinks.
  Finally, the written and read value are compared, if they does not match then
  all LED's blink.

  You can also use your smartphone to read/write a tag.
  On Android, download a NFC Tools. Then start the app, check if NFC is activated
  on your smartphone. Put your smartphone near the tag, you can read it. You can
  write a tag with this app.
******************************************************************************
*/

#include "ST25DVSensor.h"
#include "Wire.h"

TwoWire MyWire(PB14, PB13);
ST25DV st25dv(PE12, -1, &MyWire);

void setup() {
  const char uri_write_message[] = "st.com/st25";       // Uri message to write in the tag
  const char uri_write_protocol[] = URI_ID_0x01_STRING; // Uri protocol to write in the tag
  String uri_write = String(uri_write_protocol) + String(uri_write_message);
  String uri_read;

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }

  // The wire instance used can be omitted in case you use default Wire instance
  if(st25dv.begin() == 0) {
    Serial.println("System Init done!");
  } else {
    Serial.println("System Init failed!");
    while(1);
  }

  if(st25dv.writeURI(uri_write_protocol, uri_write_message, "")) {
    Serial.println("Write failed!");
    while(1);
  }

  delay(100);
  
  if(st25dv.readURI(&uri_read)) {
    Serial.println("Read failed!");
    while(1);
  }

  Serial.println(uri_read.c_str());

  if(strcmp(uri_read.c_str(), uri_write.c_str()) == 0) {
    Serial.println("Successfully written and read!");
  } else {
    Serial.println("Read bad string!");
  }
}

void loop() {
  //empty loop
}
