#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  size_t n = hand->n_cards;
  for (size_t i = 0; i < n; i++) {
    card_t * card = hand->cards[i];
    print_card(*card);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  size_t n = d->n_cards;
  for (size_t i = 0; i < n; i++) {
    card_t * card = d->cards[i];
    if ((*card).value == c.value && (*card).suit == c.suit) {
      return 1;
    }
  }
  return 0;
}

void shuffle(deck_t * d){
  if (!d || d->n_cards < 2){
    return;
  }
  size_t n = d->n_cards;
  for (size_t i = n - 1; i > 0; i--) {
    size_t r = random() % (i + 1);
    card_t * temp = d->cards[i];
    d->cards[i] = d->cards[r];
    d->cards[r] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  if (d->n_cards != 52) {
    printf("Deck has %zu cards. Should have 52.\n", d->n_cards);
    assert(0);
  }
  char values[] = {'0', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K', 'A'};
  char suits[] = {'s', 'h', 'c', 'd'};
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      card_t c = card_from_letters(values[i], suits[j]);
      if (deck_contains(d, c) == 0) {
	printf("Deck is missing card:");
	print_card(c);
	assert(0);
      }
    }
  }
}
