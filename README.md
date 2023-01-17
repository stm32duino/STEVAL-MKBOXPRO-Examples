# STEVAL-Examples

[This repository](https://github.com/stm32duino/STEVAL-Examples) contains some examples that demonstrate how to use the following sensors on the STEVAL board:

- LIS2DU12 (inertial)
- LSM6DSV16X (inertial)
- LPS22DF (pressure)
- LIS2MDL (megnetic field)
- STTS22H (temperature)
- MP23DB01HP (digital audio)
- ST25DV04K (NFC)

## Python Wave Serial Encoder

The `STEVAL_Python_Wave_Serial_Encoder` sketch can be used together with the [Python-Wave-Serial-Encoder GUI](https://github.com/stm32duino/Python-Wave-Serial-Encoder) application to record PCM audio to a WAV file on desktop, by using serial connection to the board.

1. Install [STEVAL-Audio](https://github.com/stm32duino/STEVAL-Audio) library (if you haven't done yet)

2. Compile and Flash the `STEVAL_Python_Wave_Serial_Encoder` sketch you find in `examples/` folder (using Arduino IDE, for instance)

3. Connect the STEVAL board to serial port

4. Launch [Python-Wave-Serial-Encoder GUI](https://github.com/stm32duino/Python-Wave-Serial-Encoder)

5. Select the serial port and click Connect

6. Click Save and select the WAV file where you're going to record the audio

7. Click Start to start capturing audio

8. Click Stop when you finished

9. Listen the WAV file with your preferred audio player

## MEMS HelloWorld

The `STEVAL_MEMS_HelloWorld` sketch shows how to get data from LIS2DU12, LSM6DSV16X, LPS22DF, LIS2MDL and STTS22H. Just open the sketch, compile and run. Remember to install the relative sensors libraries.

## ST25DV HelloWorld

The `STEVAL_ST25DV_HelloWorld` sketch shows how to setup the ST25DV04K NFC to serve the URL [http://www.st.com/st25](http://www.st.com/st25). In order to use it, just open the sketch, install the ST25DV04K library (if not present), then compile and flash it.

## STEVAL_MEMS_6D_Orientation

The `STEVAL_MEMS_6D_Orientation` This application shows how to use LSM6DSV16X accelerometer 
to find out the 6D orientation and display data on a hyperterminal.

## STEVAL_MEMS_Double_Tap_Detection

The `STEVAL_MEMS_Double_Tap_Detection` This application shows how to detect the double tap event using the LSM6DSV16X accelerometer.

## STEVAL_MEMS_Free_Fall_Detection

The `STEVAL_MEMS_Free_Fall_Detection`  This application shows how to detect the free fall event using the LSM6DSV16X accelerometer.

## STEVAL_MEMS_Pedometer

The `STEVAL_MEMS_Pedometer` This application shows how to use LSM6DSV16X accelerometer to count steps.

## STEVAL_MEMS_Single_Tap_Detection

The `STEVAL_MEMS_Single_Tap_Detection` This application shows how to detect the single tap event using the LSM6DSV16X accelerometer.

## STEVAL_MEMS_Tilt_Detection

The `STEVAL_MEMS_Tilt_Detection` This application shows how to detect the tilt event using the LSM6DSV16X accelerometer.

## STEVAL_MEMS_Wake_Up_Detection

The `STEVAL_MEMS_Wake_Up_Detection` This application shows how to detect the wake-up event using the LSM6DSV16X accelerometer.

## Dependencies

The examples in this repository requires the following STM32duino libraries:

- STM32duino LIS2DU12: https://github.com/stm32duino/LIS2DU12

- STM32duino LSM6DSV16X: https://github.com/stm32duino/LSM6DSV16X

- STM32duino LPS22DF: https://github.com/stm32duino/LPS22DF

- STM32duino LIS2MDL: https://github.com/stm32duino/LIS2MDL

- STM32duino STTS22H: https://github.com/stm32duino/STTS22H

- STM32duino MP23DB01HP: https://github.com/stm32duino/STEVAL-Audio

- STM32duino ST25DV: https://github.com/stm32duino/ST25DV

