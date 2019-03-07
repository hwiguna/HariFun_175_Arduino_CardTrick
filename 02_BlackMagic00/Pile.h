#ifndef Pile_h
#define Pile_h

#include "Card.h"

class Pile {
  public:
    Pile();
    void Pile::AddTop(Card newCard);
    Card Pile::TakeTop();
  private:
    Card _cards[52];
};

Pile::Pile()
{
  int cardIndex = 0;
  for (byte s = 0; s < 4; s++) {
    char suit = suits[s];
    for (byte v = 1; v <= 12; v++) {
      _cards[cardIndex] = new Card(v, suit);
    }
  }
}

void Pile::AddTop(Card newCard) {
}

Card Pile::TakeTop() {
  return new Card(1,'C');
}

#endif
