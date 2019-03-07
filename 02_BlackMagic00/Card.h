#ifndef Card_h
#define Card_h

#include "Arduino.h"

String suits = "CDHS"; // Club Diamond Heart Spade

class Card {
  public:
    Card(byte value, char suit);
    Card();
    void Card::SetStatus(byte newStatus);
    byte Card::GetStatus();
    byte Card::GetValue();
    char Card::GetSuit();
    String Card::ValueToString(byte value);
    String Card::SuitToString(char suit);
    String Card::GetCard();
  private:
    byte _value;
    char _suit;
    byte _status; // 0=unplayed, 1=in play, 2=discarded
};

Card::Card(byte value, char suit)
{
  _value = value;
  _suit = suit;
}

Card::Card()
{
  _value = 0;
  _suit = ' ';
}

void Card::SetStatus(byte newStatus) {
  _status = newStatus;
}

byte Card::GetStatus() {
  return _status;
}

byte Card::GetValue() {
  return _value;
}

char Card::GetSuit() {
  return _suit;
}

String Card::ValueToString(byte value) {
  String result = "?";
  switch (value) {
    case 1: result = "Ace"; break;
    case 10: result = "Jack"; break;
    case 11: result = "Queen"; break;
    case 12: result = "King"; break;
    default: result = String(value); break;
  }
}

String Card::SuitToString(char suitCode) {
  String suit = "?";
  switch (suitCode) {
    case 'C': suit = "Club"; break;
    case 'D': suit = "Diamond"; break;
    case 'H': suit = "Heart"; break;
    case 'S': suit = "Spade"; break;
  }
}

String Card::GetCard() {
  return ValueToString(_value) + " of " + SuitToString(_suit);
}

#endif
