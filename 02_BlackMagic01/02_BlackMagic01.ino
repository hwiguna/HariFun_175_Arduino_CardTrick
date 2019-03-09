// Black Magic Card Trick by Hari Wiguna, 2019
// The secret:
// The position of the first black suit card indicates
// the position of where the chosen card would appear in next batch.

//-- LCD Variables --
#include <SoftwareSerial.h>

#define rxPin 255       // Not used, so set to invalid pin #
#define txPin 3         // Connect BPI/BPK's SER input to this pin.
#define inverted 1     // In setup, 1=inverted, 0=noninverted

const char clearScreen[ ] = {
  254, 1, 254, 128, 0
};
const char message[ ] = "Hello World!" ;
SoftwareSerial lcd =  SoftwareSerial(rxPin, txPin, inverted);

//-- BUTTON --
byte button = 4; // Digital pin 4


//-- Magic trick classes --
#include "Pile.h"
#include "Magician.h"


Card PickACard(Pile deck) {
  Card card = blankCard;
  bool buttonPressed = false;
  while (!buttonPressed) {
    int potValue = analogRead(A0);
    int cardIndex = map(potValue, 0, 1023, 0, 47);

    lcd.print(clearScreen);
    lcd.println("Pick a card...");
    card = deck.PeekCard(cardIndex);
    lcd.print(card.CardToString());

    if (digitalRead(button) == LOW) buttonPressed = true;
    delay(50);
  }
  return card;
  //return Card(7,DIAMOND);
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
  SetupLCD();
  Serial.begin(115200);
  //randomSeed(analogRead(0));

  Pile testDeck = Pile(); // Unlike in C#, you don't say new Class.
  testDeck.UnitTest();
}

void loop() {
  //-- Prepare deck --
  Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  deck.InitFullDeck();

  //-- Instantiate Magician! --
  Magician shinLim = Magician(deck);
  Card chosenCard = PickACard(deck); // Let user pick a card
  lcd.print(clearScreen);
  lcd.println("You picked:");
  lcd.println(chosenCard.CardToString());

  deck.Shuffle();
  shinLim.SetChosenCard( chosenCard );
  shinLim.PerformMagic(lcd);

  delay(5000);
}

