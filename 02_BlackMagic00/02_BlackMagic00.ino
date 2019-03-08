// Black Magic Card Trick by Hari Wiguna, 2019
// The secret:
// The position of the first black suit card indicates
// the position of where the chosen card would appear in next batch.

#include "Pile.h"
#include "Magician.h"


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));


  Pile deck = Pile(); // Unlike in C#, you don't say new Class.
  //deck.UnitTest();
  deck.InitFullDeck();
  deck.Shuffle();

  Magician shinLim = Magician(deck);
  shinLim.SetChosenCard( Card(QUEEN,HEART) );
  shinLim.PerformMagic();
}

void loop() {
}

// 123456789*123456
// Queen of Diamond

