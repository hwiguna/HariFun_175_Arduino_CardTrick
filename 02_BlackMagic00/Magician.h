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
}

Magician::PerformMagic() {
  Serial.println("\nPresenting ShinLim!");
  byte maxAttempts = 4;
  for (byte attempt=0; attempt<maxAttempts; attempt++) {
    // If this is the attempt before we're supposed to reveal...
    if (attempt == (maxAttempts-1)) {
      // Show an odd black card or even red card
      Card markerCard = _deck.TakeMarkerCard(_chosenCard);
      markerCard.Print();
      _chosenCard.Print();
    }
    else {
      Card markerCard = _deck.TakeNonMarkerCard(_chosenCard);
      markerCard.Print();
    }
  }
}

