class Magician {
  public:
    Magician(Pile deck);
    SetChosenCard(Card chosenCard);
    PerformMagic();
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

void WaitForButtonPress2() {
  while (digitalRead(4) != LOW) {
    delay(100);
  }
  delay(500); // ignore switch bounce
}

Magician::PerformMagic() {
  Serial.println("\nWas it one of these cards?");
  bool hasShownMarker = false;
  bool hasShownChosenCard = false;
  bool isOutOfCards = false;

  while (!isOutOfCards) {
    Card card1 = blankCard;
    Card card2 = blankCard;

    if (!hasShownMarker) { // Have we shown marker yet? NO
      bool isTimeForMarker = random(5) == 4L; // 1 in 4 chance if we should show marker card now
      if (isTimeForMarker) { // Is it time to show marker? YES
        bool showChosenOnSamePage = random(3) == 2L; // Fifty-fifty chance if we should show chosen card on same page as marker card or on next page
        if (showChosenOnSamePage) {
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
      } else {
        // The show is over, but let them keep spitting out remaining cards
        card1 =  _deck.RemoveTopCard();
        card2 =  _deck.RemoveTopCard();
      }
    }

    lcd.clear();
    if (card1.Value() == 0) {
      //         123456789*123456
      lcd.print(" No more cards! ");
      isOutOfCards = true;
    } else {
      lcd.print(card1.CardToString());
      lcd.setCursor(0, 1);
      lcd.print(card2.CardToString());
      //      card1.Print();
      //      card2.Print();
      //      Serial.println();
    }

    WaitForButtonPress2();
  }

  Serial.println("Take a bow!\n");
}

