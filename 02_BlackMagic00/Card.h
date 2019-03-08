#ifndef Card_h
#define Card_h

#include "Arduino.h"

#define CLUB 1
#define DIAMOND 2
#define HEART 3
#define SPADE 4

#define ACE 1
#define JACK 10
#define QUEEN 11
#define KING 12

class Card {
  public:
    Card(byte inValue, byte inSuit);
    Card();

    String ValueToString(byte value);
    String SuitToString(byte suit);
    String CardToString();
    void Print();
    bool IsOdd();
    void Swap(Card &card1, Card &card2);

    byte Value(); // 1..12
    byte Suit(); // 1..4

  private:
    byte _value;
    char _suit;

};

//=== IMPLEMENTATION ===

void Card::Swap(Card &card1, Card &card2) {
    Card temp = card1;
    card1 = card2;
    card2 = temp;
}

Card::Card(byte inValue, byte inSuit)
{
  _value = inValue;
  _suit = inSuit;
}

Card::Card()
{
  _value = 0;
  _suit = 0;
}

byte Card::Value() {
  return _value;
}

byte Card::Suit() {
  return _suit;
}

String Card::ValueToString(byte value) {
  String result = "?";
  switch (value) {
    case ACE: result = "Ace"; break;
    case JACK: result = "Jack"; break;
    case QUEEN: result = "Queen"; break;
    case KING: result = "King"; break;
    default: result = String(value); break;
  }
  return result;
}

String Card::SuitToString(byte suit) {
  String result = "?";
  switch (suit) {
    case CLUB: result = "Club"; break;
    case DIAMOND: result = "Diamond"; break;
    case HEART: result = "Heart"; break;
    case SPADE: result = "Spade"; break;
  }
  return result;
}

String Card::CardToString() {
  return ValueToString(_value) + " of " + SuitToString(_suit);
}

void Card::Print() {
  Serial.println( CardToString() );
}

bool Card::IsOdd() {
  return (_value % 2) != 0;
}

//=== GLOBAL CONSTANTS ===

const Card blankCard = Card(0,0);

#endif
