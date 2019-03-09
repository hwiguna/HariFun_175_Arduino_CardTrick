class Magician {
  public:
    Magician(Pile deck);
    SetChosenCard(Card chosenCard);
    PerformMagic(SoftwareSerial lcd);
  private:
    Card _chosenCard;
    Pile _deck;
};

//=== IMPLEMENTATION ===

Magician::Magician(Pile deck) {
  _deck = deck;
  _chosenCard = blankCard;
}

Magician::SetChosenCard(Card chosenCard) {
  _chosenCard = chosenCard;
  byte index = _deck.RemoveCard(_chosenCard);
  Serial.print("\nRemoved chosen card from location ");
  Serial.println(index);
}

Magician::PerformMagic(SoftwareSerial lcd) {
  Serial.println("\nWas it one of these cards?");
  bool hasShownMarker = false;
  bool hasShownChosenCard = false;

  while (!hasShownChosenCard) {
    Card card1 = blankCard;
    Card card2 = blankCard;

    if (!hasShownMarker) { // Have we shown marker yet? NO
      bool isTimeForMarker = random(0, 2) == 0; // Fifty-fifty chance if we should show marker card now
      if (isTimeForMarker) { // Is it time to show marker? YES
        bool showChosenOnSamePage = random(0, 2) == 0; // Fifty-fifty chance if we should show chosen card on same page as marker card or on next page
        if (showChosenOnSamePage) { //
          card1 =  _deck.TakeMarkerCard(); // Show marker card...
          card2 = _chosenCard; // immediately follow with chosen card on same page.
          hasShownChosenCard = true;
        } else {
          card1 =  _deck.TakeNonMarkerCard(); // show random non-marker card
          card2 =  _deck.TakeMarkerCard(); // show marker card to indicate that first card on next page is chosen card.
        }
        hasShownMarker = true; // either way, we would have shown marker.
      }
      else { // Not time to show marker yet, so just show two random cards.
          card1 =  _deck.TakeNonMarkerCard(); // show random non-marker card
          card2 =  _deck.TakeNonMarkerCard(); // show random non-marker card
      }
    }
    else { // We have shown marker on previous page, so it's time to show chosen card
      if (!hasShownChosenCard) {
        card1  = _chosenCard;
        card2 =  _deck.TakeNonMarkerCard(); // show random non-marker card
        hasShownChosenCard = true;
      }
    }

    card1.Print();
    card2.Print();
    Serial.println();

    while (digitalRead(4)!=LOW) {
      delay(100);
    }

    lcd.print(clearScreen);
    lcd.println(card1.CardToString());
    lcd.println(card2.CardToString());

  }

  Serial.println("Take a bow!\n");
}

