String chosenCard = "KS";

String suitSequence = "CDHS"; // Club Diamond Heart Spade
String numberSequence = "A23456789JQK"; //A234 5678 9JQK
// A23456 789JQK

// The secret:
// First card value indicates the SUIT of the chosen card:
// Ace is 1 = Club
// 2 = Diamond
// 3 = Heart
// 4 = Spade
// The four sequence repeats with:
// 5 = Club, 6 = Diamond, 7 = Heart, 8 = Spade
// 9 = Club, Jack = Diamond, Queen = Heart, King = Spade

// The first card value ALSO indicates the highest bit of the VALUE of the chosen card
// 

byte SuitToIndex(char suit) {
  byte suitIndex = 4; // bad!
  for (byte i=0; i<4; i++) {
    if (suit == suitSequence[i]) {
      suitIndex = i;
      break;
    }
  }
  return suitIndex;
}

char GetCardSuitCode(String card) {
  char suit = card[1];
  byte suitIndex = SuitToIndex(suit);
  int randomGroup = 2; //random(0,3); // 0,1, or 2
  return numberSequence[randomGroup*4 + suitIndex];
}

byte GetCardNumber(String card) {
  byte number = 13; // bad!
  char value = card[0];
  for (byte i=0; i<13; i++) {
    if (value == numberSequence[i]) {
      number = i;
      break;
    }
  }
  return number;
}

void setup() {
  Serial.begin(9600);
  Serial.println(GetCardNumber(chosenCard));
  char chosenCardSuitCode = GetCardSuitCode(chosenCard);
  Serial.println(chosenCardSuitCode);
}

void loop() {
}
