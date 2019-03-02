#include "Card.h"

String chosenCard = "KS";

// The secret:
// The position of the first black suit card indicates
// the position of where the chosen card would appear in next batch.

String suits = "CDHS"; // Club Diamond Heart Spade
Card deck[52];

void setup() {
  int cardIndex = 0;
  for (byte s=0; s<4; s++) {
    char suit = suits[i];
    for (byte v=1; v<=12; v++) {
      deck[cardIndex] = Card(v, suit);
    }
  }
}

void loop() {
}
