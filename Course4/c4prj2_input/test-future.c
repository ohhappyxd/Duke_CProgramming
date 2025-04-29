#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "future.h"

int main(void) {
  // Create a deck to draw from
  deck_t * draw_deck = malloc(sizeof(*draw_deck));
  draw_deck->n_cards = 2;
  draw_deck->cards = malloc(2 * sizeof(*draw_deck->cards));

  card_t * c1 = malloc(sizeof(*c1));
  c1->value = 10;
  c1->suit = SPADES;
  draw_deck->cards[0] = c1;

  card_t * c2 = malloc(sizeof(*c2));
  c2->value = 5;
  c2->suit = HEARTS;
  draw_deck->cards[1] = c2;

  // Create a future_cards_t
  future_cards_t fc;
  fc.n_decks = 0;
  fc.decks = NULL;

  // Add placeholders
  card_t * p1 = malloc(sizeof(*p1));
  p1->value = 0;
  p1->suit = NUM_SUITS;
  add_future_card(&fc, 0, p1);

  card_t * p2 = malloc(sizeof(*p2));
  p2->value = 0;
  p2->suit = NUM_SUITS;
  add_future_card(&fc, 1, p2);

  card_t * p3 = malloc(sizeof(*p3));
  p3->value = 0;
  p3->suit = NUM_SUITS;
  add_future_card(&fc, 1, p3);

  // Before filling
  printf("Before filling future cards:\n");
  print_card(*(fc.decks[0].cards[0]));
  print_card(*(fc.decks[1].cards[0]));
  print_card(*(fc.decks[1].cards[1]));
  printf("\n");

  // Fill in future cards from draw_deck
  future_cards_from_deck(draw_deck, &fc);

  // After filling
  printf("After filling future cards:\n");
  print_card(*(fc.decks[0].cards[0])); // Should be 10 of SPADES
  print_card(*(fc.decks[1].cards[0])); // Should be 5 of HEARTS
  print_card(*(fc.decks[1].cards[1])); // Should be 5 of HEARTS
  printf("\n");
  
  // Cleanup
  free(c1);
  free(c2);
  free(draw_deck->cards);
  free(draw_deck);

  free(p1);
  free(p2);
  free(p3);

  for (size_t i = 0; i < fc.n_decks; i++) {
    free(fc.decks[i].cards);
  }
  free(fc.decks);

  return 0;
}
