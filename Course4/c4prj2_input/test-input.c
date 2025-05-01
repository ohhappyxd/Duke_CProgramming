#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#include "deck.h"
#include "future.h"
#include "input.h"

int main(void) {
  const char *filename = "input.txt";
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Could not open input file");
    return EXIT_FAILURE;
  }

  size_t n_hands = 0;
  future_cards_t fc;
  fc.n_decks = 0;
  fc.decks = NULL;

  deck_t ** hands = read_input(f, &n_hands, &fc);
  fclose(f);

  printf("Read %zu hands:\n", n_hands);
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu: ", i);
    print_hand(hands[i]);
    printf("\n");
  }

  // Show future cards
  printf("Future cards:\n");
  for (size_t i = 0; i < fc.n_decks; i++) {
    printf("?%zu:", i);
    for (size_t j = 0; j < fc.decks[i].n_cards; j++) {
      print_card(*(fc.decks[i].cards[j]));
      printf(" ");
    }
    printf("\n");
  }

  // Clean up
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);

  for (size_t i = 0; i < fc.n_decks; i++) {
    free(fc.decks[i].cards);
  }
  free(fc.decks);

  return EXIT_SUCCESS;
}
