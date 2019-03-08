// Black Magic Card Trick by Hari Wiguna, 2019
// The secret:
// The position of the first black suit card indicates
// the position of where the chosen card would appear in next batch.

#include "Pile.h"
#include "Magician.h"


Card PickACard() {
  return Card(7,DIAMOND);
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));


  //Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  //deck.UnitTest();
}

void loop() {
  //-- Prepare deck --
  Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  deck.InitFullDeck();
  deck.Shuffle();

  //-- Let user pick a card --
  Card chosenCard = PickACard();
  byte numberOfGuesses = random(1,9); // between 1 and 8 cards or 1 to 4 screens of two cards each.

  //-- Instantiate Magician! --
  Magician shinLim = Magician(deck);
  shinLim.SetChosenCard( chosenCard );
  shinLim.PerformMagic(numberOfGuesses);

  delay(5000);
}

// 123456789*123456
// Queen of Diamond

