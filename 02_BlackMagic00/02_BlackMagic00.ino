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

  Pile testDeck = Pile(); // Unlike in C#, you don't say new Class.
  testDeck.UnitTest();
}

void loop() {
  //-- Prepare deck --
  Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  deck.InitFullDeck();
  deck.Shuffle();

  //-- Instantiate Magician! --
  Magician shinLim = Magician(deck);
  Card chosenCard = PickACard(); // Let user pick a card
  shinLim.SetChosenCard( chosenCard );
  shinLim.PerformMagic();

  delay(5000);
}

