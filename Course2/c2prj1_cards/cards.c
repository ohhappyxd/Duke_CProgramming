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
  case STRAIGHT_FLUSH: return "STRAIGHT FLUSH";
  case FOUR_OF_A_KIND: return "FOUR OF A KIND";
  case FULL_HOUSE: return "FULL HOUSE";
  case FLUSH: return "FLUSH";
  case STRAIGHT: return "STRAIGHT";
  case THREE_OF_A_KIND: return "THREE OF A KIND";
  case TWO_PAIR: return "TWO PAIR";
  case PAIR: return "PAIR";
  case NOTHING: return "NOTHING";
  default: return "UNKNOWN RANKING";
    }
}

char value_letter(card_t c) {
  unsigned v = c.value;
  if (v <= 9 && v >= 2) {
    return v + 48;
  } else if (v == 10) {
    return v + 38;
  } else {
    switch (v) {
    case 11: return "J";
    case 12: return "Q";
    case 13: return "K";
    case 14: return "A";
    default: return "U";
    }
  }
}


char suit_letter(card_t c) {
  suit_t s = c.suit;
  switch (s) {
  case SPADES: return "s";
  case HEARTS: return "h";
  case DIAMONDS: return "d";
  case CLUBS: return "c";
    }
}

void print_card(card_t c) {
  char value = value_letter(c);
  char suit = suit_letter(c);
  printf("%c%c", value, suit);
}

card_t card_from_letters(char value_let, char suit_let) {
  unsigned value;
  if (value_let == "0") {
    value = 10;
  } else if (value_let >= 50 && value_let <= 57) {
    value = value_let - "0";
  } else {
    switch (value_let) {
    case "J": value = 11; break;
    case "Q": value = 12; break;
    case "K": value = 13; break;
    case "A": value = 14; break;
    default: printf("Invalide value"); exit(EXIT_FAILURE);
    }
  }
  suit_t suit;
  switch (suit_let) {
  case "s": suit = SPADE;
  case "h": suit = HEARTS;
  case "d": suit = DIAMONDS;
  case "c": suit = CLUBS;
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
  card_t temp;
  return temp;
}
