#ifndef Pile_h
#define Pile_h

#include "Card.h"

class Pile {
  public:
    byte maxCards = 48; // 0..47
    Pile();
    void InitFullDeck();
    void Clear();
    void AddTop(Card newCard);
    Card RemoveTopCard();
    void PrintAll();
    void Shuffle();
    Card TakeMarkerCard();
    Card TakeNonMarkerCard();
    void RemoveByIndex(byte index);
    byte RemoveCard(Card card);
    Card PeekCard(byte index);
    void UnitTest();
  private:
    Card _cards[52];
    byte _numberOfCards;

    bool IsBlackCard(Card card);
    bool IsMarkerCard(Card card);
};

//=== IMPLEMENTATION ===

Pile::Pile() {
  _numberOfCards = 0;
}

void Pile::InitFullDeck() {
  int cardIndex = 0;
  for (byte s = 1; s <= 4; s++) {
    for (byte v = 2; v <= 13; v++) {
      _cards[cardIndex++] = Card(v, s);
    }
  }
  _numberOfCards = 48;
}

void Pile::Shuffle() {
  for (byte i=0; i<_numberOfCards; i++) {
    if ((i % 3)==0) {
      lcd.print("."); // print one dot every third loop iterations because we only have 16 chars for 48 cards
      delay(150);
    }
    Card temp = _cards[i];
    int randomIndex = random(0,_numberOfCards);
    _cards[i] = _cards[randomIndex];
      _cards[randomIndex] = temp;
  }
}

void Pile::AddTop(Card newCard) {
}

Card Pile::RemoveTopCard() {
  Card topCard = _cards[0]; // Element 0 is top most card, 47 is bottom most card.
  // Shift all cards one position to top of card.
  for (byte i=0; i<(maxCards-1); i++) {
    _cards[i] = _cards[i+1];
  }
  _cards[maxCards-1] = blankCard;
  _numberOfCards--;
  return topCard;
}

void Pile::PrintAll() {
  for (byte i = 0; i < _numberOfCards; i++) {
    _cards[i].Print();
  }
}

void Pile::Clear() {
  for (byte i = 0; i < maxCards; i++) {
    _cards[i] = blankCard;
  }
  _numberOfCards = 0;
}

bool Pile::IsBlackCard( Card card ) {
  return (card.Suit() == CLUB) || (card.Suit() == SPADE);
}

Card Pile::PeekCard(byte index) {
  return _cards[index];
}

void Pile::RemoveByIndex(byte index) {
  for (byte i=index; i<(maxCards-1); i++) {
    _cards[i] = _cards[i+1];
  }
  _cards[maxCards-1] = blankCard;
  _numberOfCards--;
}

bool Pile::IsMarkerCard(Card card) {
  return IsBlackCard(card) && card.IsOdd();
}

Card Pile::TakeMarkerCard() {
  Card result = blankCard;
  for (byte i = 0; i < _numberOfCards; i++) {
    Card card = _cards[i];
    if (IsMarkerCard(card)) {
      result = _cards[i];
      RemoveByIndex(i);
      break;
    }
  }
  return result;
}

byte Pile::RemoveCard(Card cardToRemove) {
  byte index = -1;
  for (byte i = 0; i < _numberOfCards; i++) {
    Card card = _cards[i];
    if ((card.Value()==cardToRemove.Value()) && (card.Suit()==cardToRemove.Suit())) {
      index = i;
      RemoveByIndex(i);
      break;
    }
  }
  return index;
}

Card Pile::TakeNonMarkerCard() {
  Card result = blankCard;
  for (byte i = 0; i < _numberOfCards; i++) {
    Card card = _cards[i];
    if (!IsMarkerCard(card)) {
      result = card;
      RemoveByIndex(i);
      break;
    }
  }
  return result;
}

void Pile::UnitTest() {
  Serial.println("BLANK DECK:");
  Clear();
  PrintAll();

  Serial.println("FULL DECK:");
  InitFullDeck();
  PrintAll();

  Serial.println("\nTOP CARD:");
  Card topCard = RemoveTopCard();
  topCard.Print();

  Serial.println("\nTOP CARD AGAIN:");
  topCard = RemoveTopCard();
  topCard.Print();

  Serial.println("SHUFFLED DECK:");
  Shuffle();
  PrintAll();

  Serial.println("\nTOP MARKER:");
  topCard = TakeMarkerCard();
  topCard.Print();
}
#endif
