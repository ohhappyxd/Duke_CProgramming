#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
  assert(c.value >= 2 && c.value <= VALUE_ACE);
  assert(c.suit >= SPADES && c.suit <= CLUBS);
}

const char * ranking_to_string(hand_ranking_t r) {
  switch (r) {
  case STRAIGHT_FLUSH: return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND: return "FOUR_OF_A_KIND";
  case FULL_HOUSE: return "FULL_HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE_OF_A_KIND";
  case TWO_PAIR: return "TWO_PAIR";
  case PAIR: return "PAIR";
  case NOTHING: return "NOTHING";
  default: return "UNKNOWN_RANKING";
    }
}

char value_letter(card_t c) {
  char letter = '?';
  if (c.value <= 9 && c.value >= 2) {
    letter = c.value + 48;
  } else if (c.value == 10) {
    letter = c.value + 38;
  } else {
    switch (c.value) {
    case VALUE_JACK: {letter ='J'; break;}
    case VALUE_QUEEN: {letter = 'Q'; break;}
    case VALUE_KING: {letter = 'K'; break;}
    case VALUE_ACE: {letter = 'A'; break;}
    default: {letter = '?';}
    }
  }
  return letter;
}


char suit_letter(card_t c) {
  char letter = '?';
  switch (c.suit) {
  case SPADES: {letter = 's'; break;}
  case HEARTS: {letter ='h'; break;}
  case DIAMONDS: {letter = 'd'; break;}
  case CLUBS: {letter = 'c'; break;}
  default: {letter = 'u';}
    }
  return letter;
}

void print_card(card_t c) {
  char value = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c", value, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  unsigned value;
  if (value_let == '0') {
    value = 10;
  } else if (value_let >= 50 && value_let <= 57) {
    value = value_let - '0';
  } else {
    switch (value_let) {
    case 'J': value = VALUE_JACK; break;
    case 'Q': value = VALUE_QUEEN; break;
    case 'K': value = VALUE_KING; break;
    case 'A': value = VALUE_ACE; break;
    default: printf("Invalide value"); exit(EXIT_FAILURE);
    }
  }
  suit_t suit;
  switch (suit_let) {
  case 's': suit = SPADES; break;
  case 'h': suit = HEARTS; break;
  case 'd': suit = DIAMONDS; break;
  case 'c': suit = CLUBS; break;
  default: printf("Invalide suit."); exit(EXIT_FAILURE);
  }
  card_t temp;
  temp.value = value;
  temp.suit = suit;
  assert_card_valid(temp);
  return temp;
}

card_t card_from_num(unsigned c) {
  assert(c < 52);
  // 0-12 for spades, 13-25 for hearts, 26-38 for diamonts, 39-51 for clubs.  
  card_t temp;
  temp.suit = (suit_t)(c / 13);
  temp.value = c % 13 + 2;
  return temp;
}
