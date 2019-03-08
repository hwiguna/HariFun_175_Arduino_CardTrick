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
  bool isFirstPage = true;

  do until (hasShownMarker && hasShownChosenCard) {
    Card card1 = blankCard;
    Card card2 = blankCard;

    if (!hasShownMarker) { // Have we shown marker yet? NO
      bool isTimeForMarker = Random(0, 2) == 0; // Fifty-fifty chance if we should show marker card now
      if (isTimeForMarker) { // Is it time to show marker? YES
        if (isFirstPage) { // 
          card1 =  _deck.TakeMarkerCard(_chosenCard); // On first page,
          card2 = _chosenCard;
          hasShownMarker = true;
        }
      }

      ShowTwoCards(isFirstPage);
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

