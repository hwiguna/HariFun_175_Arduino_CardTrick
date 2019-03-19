
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
      bool isTimeForMarker = random(5) == 4L; // 0,1,2,3,4. So 1 in 5 chance we should show marker card now
      if (isTimeForMarker) { // Is it time to show marker? YES
        bool showChosenOnSamePage = random(3) == 2L; // 0,1,2. So, 1 in 3 chance we should show chosen card on same page as marker card
        if (showChosenOnSamePage) {
          card1 =  _deck.TakeMarkerCard(); // Show marker card on first row...
          card2 = _chosenCard; // followed immediately with chosen card on second row of same page.
          hasShownChosenCard = true;
        } else {
          card1 =  _deck.TakeNonMarkerCard(); // show random non-marker card
          card2 =  _deck.TakeMarkerCard(); // show marker card to indicate that first card on NEXT page is chosen card.
        }
        hasShownMarker = true; // either way, we would have shown marker.
      }
      else { // Not time to show marker yet, so just show two random cards.
        card1 =  _deck.TakeNonMarkerCard(); // show random non-marker card
        card2 =  _deck.TakeNonMarkerCard(); // show random non-marker card
      }
    }
    else { // We have shown marker on previous page, so it's time to show chosen card
      if (!hasShownChosenCard) { // and we have NOT shown chosen card...
        card1  = _chosenCard; // Show chosen card on row 1
        card2 =  _deck.TakeNonMarkerCard(); // Show random non-marker card on second row
        hasShownChosenCard = true;
      } else {
        // The show is over, but let them keep spitting out remaining cards
        card1 =  _deck.RemoveTopCard();
        card2 =  _deck.RemoveTopCard();
      }
    }

    //-- Show the two cards --
    lcd.clear();
    if (card1.Value() == 0) {
      lcd.print(" No more cards! ");
      isOutOfCards = true;
    } else {
      lcd.print(card1.CardToString());
      lcd.setCursor(0, 1);
      lcd.print(card2.CardToString());
    }

    WaitForButtonPress2();
  }

  Serial.println("Take a bow!\n");
}

