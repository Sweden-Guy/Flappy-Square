#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPin = 2;

//==== Bird physics ====//
float birdY = 32;
float velocity = 0;
float gravity = 0.8;
float jumpForce = -3.5;

//==== Pipes ====//
int pipeX = 128;
int pipeGap = 20; // The gap size bird flies through
int pipeTopHeight;

//==== Game state ====//
bool gameOver = false;
int score = 0;

//==== High score ====//
int highScore = 0;

void resetGame() {
  birdY = 32;
  velocity = 0;
  pipeX = 128;
  pipeTopHeight = random(10, 40);
  score = 0;
  gameOver = false;
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(0));

  // Load the high score from EEPROM
  highScore = EEPROM.read(0);

  resetGame();
}

void saveHighScore() {
  if (score > highScore) {
    highScore = score;
    EEPROM.write(0, highScore);  // Saves the high score to the memory
  }
}

void showGameOver() {
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 5);
  display.print("GAME OVER");

  display.setTextSize(1);
  display.setCursor(20, 35);
  display.print("Score: ");
  display.print(score);

  display.setCursor(20, 50);
  display.print("High:  ");
  display.print(highScore);

  display.display();
}

void loop() {

  if (gameOver) {
    showGameOver();

    if (digitalRead(buttonPin) == LOW) {
      delay(200);
      resetGame();
    }
    return;
  }

  //==== Jump ====//
  if (digitalRead(buttonPin) == LOW) {
    velocity = jumpForce;
  }

  //==== Bird physics ====//
  velocity += gravity;
  birdY += velocity;

  //==== Pipe movement ====//
  pipeX -= 2;

  if (pipeX < -20) {
    pipeX = 128;
    pipeTopHeight = random(10, 40);
    score++;
  }

  //==== Collisions ====//
  if (birdY < 0 || birdY > SCREEN_HEIGHT - 8) {
    saveHighScore();
    gameOver = true;
  }

  //==== Collisions pipes ====//
  if (pipeX < 20 && pipeX > 0) {
    if (birdY < pipeTopHeight || birdY > pipeTopHeight + pipeGap) {
      saveHighScore();
      gameOver = true;
    }
  }


  display.clearDisplay();

  //==== Bird sprite ====//
  display.fillRect(10, birdY, 8, 8, WHITE);

  //==== Pipes ====//
  display.fillRect(pipeX, 0, 7, pipeTopHeight, WHITE);
  display.fillRect(pipeX, pipeTopHeight + pipeGap, 7, SCREEN_HEIGHT, WHITE);

  //==== Score display ====//
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(score);

  //==== Draw high score ====// 
  display.setCursor(65, 0);
  display.print("Hi: ");
  display.print(highScore);

  display.display();

  delay(20);
}
