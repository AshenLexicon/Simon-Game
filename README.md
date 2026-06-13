# Simon Game - ATtiny1626

An embedded C Simon-style memory game built for the QUTy ATtiny1626 development board.

## Overview

This project implements a Simon memory game where the board plays a sequence of tones and display cues, and the user repeats the sequence using four pushbuttons. The game uses timer-based timing, debounced GPIO input, PWM buzzer output, ADC-controlled playback delay, SPI display output, and a finite state machine.

## Features

- Four-button Simon memory gameplay
- Pseudo-random sequence generation using an LFSR
- PWM buzzer tones
- 7-segment display output
- ADC-controlled playback speed
- Pushbutton debouncing
- Finite state machine for game logic

## Hardware / Tools

- QUTy ATtiny1626 development board
- Embedded C
- PlatformIO / VS Code
- Pushbuttons
- 7-segment display
- Piezo buzzer
- Potentiometer

## How It Works

The game generates a sequence of steps using a linear feedback shift register. During each round, the board plays the sequence using tones and display patterns. The user then repeats the sequence with the pushbuttons.

If the user enters the sequence correctly, the game advances to the next round. If the user enters an incorrect input, the game displays a failure state and restarts.

## Main Technical Components

- GPIO input with internal pull-up resistors
- Timer interrupt based timing
- Button debouncing
- PWM tone generation
- ADC input for playback delay
- SPI-style display output
- State-machine based game flow

## Skills Demonstrated

- Embedded C programming
- Microcontroller peripheral configuration
- GPIO input/output
- Timer interrupts
- PWM
- ADC
- SPI communication
- Debouncing
- State machines
- Embedded debugging

## Future Improvements

- Add UART commands
- Add high-score storage
- Add EEPROM support
- Add difficulty levels
- Add improved display animations
- Add a startup menu

## Author

William Ludlow  
Second-year Electrical Engineering student at Queensland University of Technology.
