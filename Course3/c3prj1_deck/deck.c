#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  if (hand == NULL || hand->cards == NULL) {
    return;
  }
  size_t n = hand->n_cards;
  for (size_t i = 0; i < n; i++) {
    if (hand->cards[i] == NULL) {
      continue;
    }
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
void add_card_to(deck_t * deck, card_t c) {
  card_t ** temp = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
  if (temp == NULL) {
    perror("Could not reallocate memory to add card");
    free_deck(deck);
    exit(EXIT_FAILURE);
  }
  deck->cards = temp;

  card_t * card = malloc(sizeof(*card));
  if (card == NULL) {
    perror("Could not reallocate memory for new card");
    free_deck(deck);
    free(temp);
    exit(EXIT_FAILURE);
  }
  card->suit = c.suit;
  card->value = c.value;
  deck->cards[deck->n_cards] = card;
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck) {
  // Create new empty card
  card_t card;
  card.suit = 0;
  card.value = 0;
  // Add empty card to deck, return pointer to it
  add_card_to(deck, card);
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * deck = malloc(sizeof(*deck));
  if (deck == NULL) {
    perror("Could not allocate memory for deck");
    exit(EXIT_FAILURE);
  }
  deck->cards = NULL;
  deck->n_cards = 0;
  for (unsigned i = 0; i < 52; i++) {
    card_t c = card_from_num(i);
    if (!deck_contains(excluded_cards, c)){
      add_card_to(deck, c);
    }
  }
  return deck;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * all_cards = malloc(sizeof(*all_cards));
  if (all_cards == NULL) {
    perror("Could not allocate memory for deck");
    exit(EXIT_FAILURE);
  }
  all_cards->n_cards = 0;
  all_cards->cards = NULL;
  // Add all cards from hands to deck
  for (size_t i = 0; i < n_hands; i++){
    for (size_t j = 0; j < hands[i]->n_cards; j++){
      card_t c = *(hands[i]->cards[j]);
      if (suit_letter(c) != '?'){
        add_card_to(all_cards, c);
      }
    }
  }
  deck_t * remaining =  make_deck_exclude(all_cards);
  free_deck(all_cards);
  return remaining;
}

void free_deck(deck_t * deck){
  if (deck == NULL){
    return;
  }
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
