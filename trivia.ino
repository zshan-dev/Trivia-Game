#include <pitches.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Melody for Jeopardy theme
int jeopardyMelody[] = { NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F4,
                         NOTE_C5, NOTE_F5, NOTE_C5, 0,
                         NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F5,
                         NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_CS5,
                         NOTE_C5, NOTE_F5, NOTE_C5, NOTE_F4,
                         NOTE_C5, NOTE_F5, NOTE_C5, 0,
                         NOTE_F5, NOTE_D5, NOTE_C5, NOTE_AS4,
                         NOTE_A4, NOTE_G4, NOTE_F4, 0 };

// Duration for each note in the Jeopardy melody
int jeopardyNoteDuration[] = { 500, 500, 500, 500, 500, 500, 500, 500,
                                500, 500, 500, 500, 750, 250, 250, 250, 250, 250,
                                500, 500, 500, 500, 500, 500, 500, 500,
                                750, 250, 500, 500, 500, 500, 500, 1500 };

// Pin Definitions
#define button1 A0
#define button2 A1
#define button3 A2
#define button4 A3
#define buttonR 12  // RESET BUTTON
#define LEDR 7      // LED connected to RESET BUTTON
#define LED1 6
#define LED2 5
#define LED3 4
#define LED4 3
#define BUZZER 9

#define buttonCorrect 10
#define LEDCorrect 2
#define buttonIncorrect 11
#define LEDIncorrect 8

#define BACKLIGHT_PIN  7
#define LED_ON  1
// Define LCD parameters
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool gameStarted = false;  // Flag to indicate if the game has started
int activePlayer = 0;      // Variable to store the active player
bool stopMelody = false; // Flag to indicate whether to stop the Jeopardy melody
bool showAnswer = false; // Define a flag to determine whether to show the answer
int currentNum1; // num1 for the math problem
int currentNum2; // num2 for the math problem
char currentOperator; // variable holding the operation

// Function prototypes 
void resetGame();         // Resets the game state
void processPlayers();    // Processes player inputs and game logic
void activatePlayer(int player);    // Activates a specific player and displays a math problem
void checkCorrectButton();          // Checks if the correct button is pressed
void checkIncorrectButton();        // Checks if the incorrect button is pressed
void playJeopardyMelody();          // Plays the Jeopardy theme melody
void playCorrectSound();            // Plays a sound indicating a correct answer
void playIncorrectSound();          // Plays a sound indicating an incorrect answer
void displayMathProblem();           // Displays a math problem on the LCD
int calculateAnswer();              // Calculates the answer to the displayed math problem
void displayAnswer();               // Displays the correct answer to the math problem


void setup() {
  Serial.begin(9600);
  pinMode(buttonR, INPUT_PULLUP);
  pinMode(LEDR, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  // Initialize Correct and Incorrect buttons and LEDs
  pinMode(buttonCorrect, INPUT_PULLUP);
  pinMode(buttonIncorrect, INPUT_PULLUP);
  pinMode(LEDCorrect, OUTPUT);
  pinMode(LEDIncorrect, OUTPUT);

  // Turn off all LEDs initially
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LEDR, LOW);
  
  // LCD Initialization
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Zeeshans Trivia!");
}

void loop() {
  // Read the state of the reset button
  int buttonRState = digitalRead(buttonR);

  // If the reset button is pressed
  if (buttonRState == LOW) {
    resetGame();
  }

  // If the game has started
  if (gameStarted) {
    processPlayers();
    
    // Check for Correct and Incorrect buttons
    checkCorrectButton();
    checkIncorrectButton();
  }
}

// Reset the game state and variables
void resetGame() {
  // Blink the LED connected to the reset button
  digitalWrite(LEDR, HIGH);
  delay(200);
  digitalWrite(LEDR, LOW);

  // Wait for the reset button to be released
  while (digitalRead(buttonR) == LOW) {
    delay(10); // Delay to avoid button debouncing
  }

  // Reset the stopMelody flag
  stopMelody = false;

  // Check the current game state
  if (!gameStarted) {
    // Start the game
    gameStarted = true;
    activePlayer = 0;     // Reset the active player
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Starting!!");
    Serial.println("Game started.");
  } else {
    // Reset the game
    gameStarted = false;  // Set the flag to indicate the game has ended
    activePlayer = 0;     // Reset the active player
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game Done!");
    // Serial.println("Game reset."); // used for debugging

    // Turn off all player LEDs
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
}

// Process player inputs and activate the corresponding player to click their button first
void processPlayers() {
  int b1State = digitalRead(button1);
  int b2State = digitalRead(button2);
  int b3State = digitalRead(button3);
  int b4State = digitalRead(button4);

  if (activePlayer == 0) {
    if (b1State == LOW) {
      activePlayer = 1;
      activatePlayer(activePlayer);
      playJeopardyMelody();
    } else if (b2State == LOW) {
      activePlayer = 2;
      activatePlayer(activePlayer);
      playJeopardyMelody();
    } else if (b3State == LOW) {
      activePlayer = 3;
      activatePlayer(activePlayer);
      playJeopardyMelody();
    } else if (b4State == LOW) {
      activePlayer = 4;
      activatePlayer(activePlayer);
      playJeopardyMelody();
    }
  }
}

// Activate the player, display a math problem, and turn on the corresponding LED
void activatePlayer(int player) {

  // Used for debugging
  // Serial.print("Activated Player: ");
  // Serial.println(player);

  // Display a math problem for the player
  displayMathProblem();

  // Turn off all LEDs
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  // Turn on the LED for the active player
  switch (player) {
    case 1:
      digitalWrite(LED1, HIGH);
      break;
    case 2:
      digitalWrite(LED2, HIGH);
      break;
    case 3:
      digitalWrite(LED3, HIGH);
      break;
    case 4:
      digitalWrite(LED4, HIGH);
      break;
    default:
      break;
  }
}

// Check if the correct button is pressed and handle accordingly
void checkCorrectButton() {
  int buttonCorrectState = digitalRead(buttonCorrect);

  if (buttonCorrectState == LOW) {
    // Turn on Correct LED
    digitalWrite(LEDCorrect, HIGH);
    // Play correct sound
    playCorrectSound();
    // Wait for the button to be released
    while (digitalRead(buttonCorrect) == LOW) {
      delay(100); // Delay to avoid button debouncing
    }
    // Turn off Green LED
    digitalWrite(LEDCorrect, LOW);
  }
}

// Check if the incorrect button is pressed and handle accordingly
void checkIncorrectButton() {
  int buttonIncorrectState = digitalRead(buttonIncorrect);

  if (buttonIncorrectState == LOW) {
    // Turn on Incorrect LED
    digitalWrite(LEDIncorrect, HIGH);
    // Play incorrect sound
    playIncorrectSound();
    // Wait for the button to be released
    while (digitalRead(buttonIncorrect) == LOW) {
      delay(200); // Delay to avoid button debouncing
    }
    // Turn off Red LED
    digitalWrite(LEDIncorrect, LOW);
  }
}

// Play the Jeopardy theme melody
void playJeopardyMelody() {
  // Beep sound before playing the Jeopardy melody
  tone(BUZZER, NOTE_A5, 100);
  delay(800);
  noTone(BUZZER);

  // Play Jeopardy melody
  for (int i = 0; i < sizeof(jeopardyMelody) / sizeof(int); i++) {
    int noteDuration = jeopardyNoteDuration[i];

    // Check for reset button during melody play
    int buttonRState = digitalRead(buttonR);
    if (buttonRState == LOW) {
      resetGame();
      return; // Exit the function if the reset button is pressed
    }

    // Check for Incorrect button during melody play
    int buttonIncorrectState = digitalRead(buttonIncorrect);
    if (buttonIncorrectState == LOW) {
      stopMelody = true;
      digitalWrite(LEDIncorrect, HIGH);
      playIncorrectSound();
      displayAnswer();
      delay(800);
      digitalWrite(LEDIncorrect, LOW);
      break; // Exit the loop if the Incorrect button is pressed
    }
    
    // Check for Correct button during melody play
    int buttonCorrectState = digitalRead(buttonCorrect);
    if (buttonCorrectState == LOW) {
      stopMelody = true;
      digitalWrite(LEDCorrect, HIGH);
      playCorrectSound();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Correct!!");
      delay(800);
      digitalWrite(LEDCorrect, LOW);
      break; // Exit the loop if the Correct button is pressed
    }

    tone(BUZZER, jeopardyMelody[i], noteDuration);
    delay(noteDuration + 30);

    if (stopMelody) {
      stopMelody = false;
      break; // Exit the loop if the stopMelody flag is set
    }
  }

  noTone(BUZZER);
}

// Play sound indicating correct answer
void playCorrectSound() {
  tone(BUZZER, NOTE_A6, 1000);
  delay(1000);
  noTone(BUZZER);
}

// Play sound indicating incorrect answer
void playIncorrectSound() {
  tone(BUZZER, NOTE_G3, 1000);
  delay(1000);
  noTone(BUZZER);
}

// Generate a random math problem and display it on the LCD
void displayMathProblem() {
  currentNum1 = random(1, 10);
  currentNum2 = random(1, 10);
  char operators[] = {'+', '-', '*'};
  currentOperator = operators[random(0, 3)];

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Math Problem:");

  lcd.setCursor(0, 1);
  lcd.print(currentNum1);
  lcd.print(" ");
  lcd.print(currentOperator);
  lcd.print(" ");
  lcd.print(currentNum2);
}

// Calculate and return the answer to the current math problem
int calculateAnswer() {
  switch (currentOperator) {
    case '+':
      return currentNum1 + currentNum2;
    case '-':
      return currentNum1 - currentNum2;
    case '*':
      return currentNum1 * currentNum2;
    default:
      return 0;
  }
}

// Display the correct answer to the current math problem on the LCD
void displayAnswer() {
  int answer = calculateAnswer();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Problem Answer:");
  lcd.setCursor(0, 1);
  lcd.print(answer);
}
