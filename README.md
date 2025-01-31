# Zeeshan's Trivia Game

This project is a trivia game with a buzzer and math problems, inspired by the Jeopardy theme. It uses an Arduino with an LCD display, buttons for player input, and LEDs to indicate the active player. 

Once the host presses their start button, a question will be displayed on the LCD display. All players have an oppurtunity to answer by clicking thier buttons first. Who ever clicekd it first has a LED turn on to indicate it's their turn. The jeoprdy music starts and they have to asnwer the question before the song ends. If they answer incorrectly the host pushes their red button and an LED turns red. The answer to the math question is than displayed on the LCD display. If the person gets it right the host presses the green button which turns on its respective green LED. The LCD than displays "Correct". The game can be restarted by the host clicking their start button twice, once to end the game and another to start a new one.

Project Demonstration: **https://drive.google.com/drive/folders/1FCn6abQFn24HuT76HCELtPaLLmH7FwMW?usp=sharing**
- PDf containing the schematic diagram and parts used.
[Computer Engineering Trivia Game.pdf](https://github.com/user-attachments/files/18613975/Computer.Engineering.Trivia.Game.pdf)

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

I've organized the code using multiple functions not only for clarity but also to enhance maintainability. Breaking down the code into smaller functions makes it easier to understand, modify, and maintain. This approach aligns with professional coding practices, providing a foundation for versatile and adaptable code. By compartmentalizing different functionalities, the overall structure becomes more efficient, promoting ease of maintenance and future modifications.

##Function prototype:
Used to declare the existence and signatures of functions before their actual implementations in the code. Here's a brief explanation of why I used function prototypes:
- Order Independence: Function prototypes allowed me to declare the functions at the beginning of the code, providing the compiler with information about the functions' names, return types, and parameter types. This allowed me to define the functions later in the code, and the compiler will still recognize them.
- Type Checking: Function prototypes enable the compiler to perform type checking when functions are called. By declaring the function signatures in advance, I ensured that the functions are used correctly, with the correct number and types of arguments.
- Readability and Documentation: Including function prototypes serves as documentation for anyone reading the code. It provides a quick reference to understand the purpose of each function and its expected inputs and outputs.
- Compiler Warnings: Function prototypes help the compiler issue warnings if there are inconsistencies between function declarations and definitions. This can catch potential errors early in the development process. 
### Libraries

- `pitches.h` for note definitions.
- `Wire.h` and `LiquidCrystal_I2C.h` for LCD.

### Melody

The Jeopardy melody is defined using arrays for the notes and durations:

```cpp
int jeopardyMelody[] = { NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F4, NOTE_C5, NOTE_F5, NOTE_C5, 0, NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F4, NOTE_C5, NOTE_F5, NOTE_C5, 0, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_F4, 0 };
int jeopardyNoteDuration[] = { 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 750, 250, 250, 250, 250, 250, 500, 500, 500, 500, 500, 500, 500, 500, 750, 250, 500, 500, 500, 500, 500, 1500 };
