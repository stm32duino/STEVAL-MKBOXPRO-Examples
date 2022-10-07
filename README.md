# STEVAL-Examples

[This repository](This repository) contains some examples that demonstrate how to use the following MEMS sensors on the STEVAL board:

- MP23DB01HP (digital audio)

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
