class Magician {
  public:
    Magician(Pile deck);
    SetChosenCard(Card chosenCard);
    PerformMagic(byte numberOfGuesses);
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
}

Magician::PerformMagic(byte numberOfGuesses) {
  Serial.println("\nPresenting ShinLim!");
  bool hasShownMarker = false;
  bool hasShownChosenCard = false;

  while (!hasShownChosenCard) {
    Card card1 = blankCard;
    Card card2 = blankCard;

    if (!hasShownMarker) { // Have we shown marker yet? NO
      bool isTimeForMarker = random(0, 2) == 0; // Fifty-fifty chance if we should show marker card now
      if (isTimeForMarker) { // Is it time to show marker? YES
        bool showChosenOnSamePage = random(0, 2) == 0; // Fifty-fifty chance if we should show chosen card on same page as marker card
        if (showChosenOnSamePage) { // 
          card1 =  _deck.TakeMarkerCard(_chosenCard); // Show marker card...
          card2 = _chosenCard; // immediately follow with chosen card on same page.
          hasShownChosenCard = true;
        } else {
          card1 =  _deck.TakeNonMarkerCard(_chosenCard); // show random non-marker card
          card2 =  _deck.TakeMarkerCard(_chosenCard); // show marker card to indicate that first card on next page is chosen card. 
        }
        hasShownMarker = true;
      }

      if (hasShownMarker && !hasShownChosenCard) {
          card1  = _chosenCard;
          card2 =  _deck.TakeNonMarkerCard(_chosenCard); // show random non-marker card
      }

      card1.Print();
      card2.Print();
    }
  }

  byte maxAttempts = numberOfGuesses;
  for (byte attempt = 0; attempt < maxAttempts; attempt++) {
    // If this is the attempt before we're supposed to reveal...
    if (attempt == (maxAttempts - 1)) {
      // Show an odd black card or even red card
      Card markerCard = _deck.TakeMarkerCard(_chosenCard);
      markerCard.Print();
      _chosenCard.Print();
    }
    else {
      Card markerCard = _deck.TakeNonMarkerCard(_chosenCard);
      markerCard.Print();
    }

    if ((attempt % 2) != 0) {
      Serial.println();
      delay(1000);
    }
  }
}

