// Black Magic Card Trick by Hari Wiguna, 2019
// The secret:
// The position of the first black suit card indicates
// the position of where the chosen card would appear in next batch.

//-- LCD Variables --
#include <SoftwareSerial.h>

#define rxPin 255       // Not used, so set to invalid pin #
#define txPin 3         // Connect BPI/BPK's SER input to this pin.
#define inverted 1     // In setup, 1=inverted, 0=noninverted

const char clearScreen[ ] = { 254, 1, 254, 128, 0 };
const char line1[ ] = { 254, 128, 0 };
const char line2[ ] = { 254, 192, 0 };

SoftwareSerial lcd =  SoftwareSerial(rxPin, txPin, inverted);

//-- BUTTON --
byte button = 4; // Digital pin 4

//-- Magic trick classes --
#include "Pile.h"
#include "Magician.h"

void WaitForButtonPress() {
  while (digitalRead(4) != LOW) {
    delay(100);
  }
  delay(500); // ignore switch bounce
}

Card PickACard(Pile deck) {
  Card card = blankCard;
  bool buttonPressed = false;
  int prevCardIndex;
  while (!buttonPressed) {
    int potValue = analogRead(A0);
    int cardIndex = map(potValue, 0, 1023, 0, 47);
    if (cardIndex != prevCardIndex) { // Only refresh screen if chosen card changes
      prevCardIndex = cardIndex;
      card = deck.PeekCard(cardIndex);
      lcd.print(clearScreen);
      lcd.print("Pick a card...");
      lcd.print(line2);
      lcd.print(card.CardToString());
    }

    if (digitalRead(button) == LOW) {
      buttonPressed = true;
      delay(200); // ignore any button bounce noise
    }
    delay(50);
  }

  //-- Confirm chosen card --
  lcd.print(clearScreen);
  lcd.print("You've chosen");
  lcd.print(line2);
  lcd.print(card.CardToString());

  return card;
}

void SetupLCD() {
  digitalWrite(txPin, LOW);   // Stop bit state for inverted serial
  pinMode(txPin, OUTPUT);
  lcd.begin(9600);    // Set the data rate
}

void SetupInputs() {
  pinMode(button, INPUT_PULLUP);
}

void setup() {
  Serial.begin(115200);
  SetupInputs();
  SetupLCD();

  randomSeed(analogRead(A5));
  //-- Unit Testing --
  Pile testDeck = Pile(); // Unlike in C#, you don't say new Class.
  testDeck.UnitTest();
}

void loop() {
  //-- Prepare deck --
  Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  deck.InitFullDeck();

  //-- Let user pick a card --
  Card chosenCard = PickACard(deck); // Let user pick a card
  WaitForButtonPress();

  //-- Shuffle the deck --
  lcd.print(clearScreen);
  lcd.print("Shuffling cards");
  lcd.print(line2);
  deck.Shuffle();
  delay(500);
  lcd.print(clearScreen);
  delay(500);

  //-- Ready to deal --
  lcd.print("  Ready to deal");
  WaitForButtonPress();
  lcd.print(clearScreen);
  delay(500);

  //-- Perform Magic! --
  Magician shinLim = Magician(deck);
  shinLim.SetChosenCard( chosenCard );
  shinLim.PerformMagic(lcd);
}

