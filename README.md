# Zeeshan's Trivia Game

This project is a trivia game with a buzzer and math problems, inspired by the Jeopardy theme. It uses an Arduino with an LCD display, buttons for player input, and LEDs to indicate the active player.

## Components

- Arduino
- LiquidCrystal I2C LCD
- Buttons (A0-A3 for players, A4 for correct, A5 for incorrect, D12 for reset)
- LEDs (D2, D3, D4, D5, D6, D7, D8 for correct/incorrect and players)
- Buzzer (D9)
- Resistors
- Wires and breadboard

## Features

- Four players can buzz in to answer math problems
- LCD displays the current math problem
- Jeopardy theme plays when a player buzzes in
- LEDs indicate the active player
- Buttons for correct/incorrect answers with corresponding sounds and LED indications

## Circuit Diagram

1. Connect the LCD to the Arduino using I2C.
2. Connect the buttons to A0, A1, A2, A3 for players, D10 for correct, D11 for incorrect, and D12 for reset.
3. Connect the LEDs to D2, D3, D4, D5, D6, D7, and D8.
4. Connect the buzzer to D9.
5. Use resistors as needed for the buttons and LEDs.

## Code

The Arduino code initializes the components and manages the game logic. It handles player input, displays math problems, and plays sounds.

### Libraries

- `pitches.h` for note definitions.
- `Wire.h` and `LiquidCrystal_I2C.h` for LCD.

### Melody

The Jeopardy melody is defined using arrays for the notes and durations:

```cpp
int jeopardyMelody[] = { NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F4, NOTE_C5, NOTE_F5, NOTE_C5, 0, NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F4, NOTE_C5, NOTE_F5, NOTE_C5, 0, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, 0 };
int jeopardyNoteDuration[] = { 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 750, 250, 250, 250, 250, 250, 500, 500, 500, 500, 500, 500, 500, 500, 750, 250, 500, 500, 500, 500, 500, 1500 };
