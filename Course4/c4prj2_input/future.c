#include <stdio.h>
#include <stdlib.h>
#include "future.h"

// Adds ptr into the future cards for the given index
void add_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  if (fc == NULL) {
    return;
  }
  if (index > fc->n_decks) {
    size_t old_n_decks = fc->n_decks;
    size_t new_n_decks = index + 1;
    deck_t * new_decks = realloc(fc->decks, new_n_decks * sizeof(*fc->decks));
    if (new_decks == NULL) {
      perror("Could not reallocate for future cards decks");
      exit(EXIT_FAILURE);
    }

    for (size_t i = old_n_decks; i < new_n_decks; i++) {
      new_decks[i].cards = NULL;
      new_decks[i].n_cards = 0;
    }
    fc->decks = new_decks;
    fc->n_decks = new_n_decks;
  }

  // Add ptr to decks
  deck_t * deck = &fc->decks[index];
  card_t ** new_cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*deck->cards));
  if (new_cards == NULL) {
    perror("Could not reallocate memory for new card in deck");
    exit(EXIT_FAILURE);
  }
  deck->cards = new_cards;
  deck->cards[deck->n_cards] = ptr;
  deck->n_cards++;
}

// Draws cards from the deck and assigns their values and suits
// to the placeholders pointed to in fc
void future_cards_from_deck(deck_t * deck, future_cards_t * fc) {
  size_t draw_index = 0;
  for (size_t i = 0; i < fc->n_decks; i++) {
    if (fc->decks[i].n_cards > 0) {
      if (draw_index >= deck->n_cards) {
	perror("Not enough cards in deck to fill hands");
	exit(EXIT_FAILURE);
      }
      unsigned v = deck->cards[draw_index]->value;
      suit_t s = deck->cards[draw_index]->suit;
      for (size_t j = 0; j < fc->decks[i].n_cards; j++) {
	fc->decks[i].cards[j]->value = v;
	fc->decks[i].cards[j]->suit = s;
      }
      draw_index++;
    }
  }
}
