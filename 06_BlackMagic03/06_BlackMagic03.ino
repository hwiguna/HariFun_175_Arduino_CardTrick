// Black Magic Card Trick by Hari Wiguna, 2019
// The secret:
// The chosen card is shown IMMEDIATELY right after the first BLACK suit ODD card. Sometimes on same page, sometimes on next page, but it is ALWAYS the card right after the black odd card.
// Note: Jack is 11*, Queen is 12, King is 13*, and Ace is 14. So Jacks and Kings are odd numbers.

//-- LCD Variables --
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
Adafruit_LiquidCrystal lcd(0);

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

void ReadyToDeal() {
    //         123456789*123456
  lcd.print(" Ready to deal  ");
  lcd.setCursor(0,1);
  lcd.print("out the cards...");
}

Card PickACard(Pile deck) {
  Card card = blankCard;
  bool buttonPressed = false;
  int prevCardIndex = -1;
  while (!buttonPressed) {
    int potValue = analogRead(A0);
    int cardIndex = map(potValue, 0, 1023, 0, 51);
    if (cardIndex != prevCardIndex) { // Only refresh screen if chosen card changes
      prevCardIndex = cardIndex;
      card = deck.PeekCard(cardIndex);
      lcd.clear();
      lcd.print("Pick a card...");
      lcd.setCursor(0,1);
      lcd.print(card.CardToString());
    }

    if (digitalRead(button) == LOW) {
      buttonPressed = true;
      delay(200); // ignore any button bounce noise
    }
    delay(50);
  }

  //-- Confirm chosen card --
  lcd.clear();
  lcd.print("You've chosen");
  lcd.setCursor(0,1);
  lcd.print(card.CardToString());

  return card;
}

void SetupLCD() {
  lcd.begin(16, 2); // 16 columns, 2 rows
  lcd.clear();
  lcd.print("* Magic Trick *");
  lcd.setCursor(0,1);
  lcd.print(" by Hari Wiguna "); 
  lcd.setBacklight(HIGH);
  delay(1500);
}

void SetupInputs() {
  pinMode(button, INPUT_PULLUP);
}

void setup() {
  SetupLCD();
  Serial.begin(115200);
  SetupInputs();

  //-- Unit Testing --
//  Pile testDeck = Pile(); // Unlike in C#, you don't say new Class.
//  testDeck.UnitTest();
}


void loop() {
  //-- Prepare deck --
  Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  deck.InitFullDeck();

  //-- Let user pick a card --
  Card chosenCard = PickACard(deck); // Let user pick a card
  WaitForButtonPress();

  //-- Shuffle the deck --
  deck.Shuffle();
  ReadyToDeal();
  WaitForButtonPress();

  //-- Perform Magic! --
  Magician shinLim = Magician(deck);
  shinLim.SetChosenCard( chosenCard );
  shinLim.PerformMagic();
}

