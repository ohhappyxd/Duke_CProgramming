#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

#define DEFAULT_TRIALS 10000

int main(int argc, char ** argv) {
  // Check comman line arguments
  if (argc < 2 || argc > 3) {
    fprintf(stderr, "Usage: poker input.file [num_trials]\n");
    return EXIT_FAILURE;
  }

  long num_trials = DEFAULT_TRIALS;
  if (argc == 3) {
    char *endptr = NULL;
    errno = 0;
    num_trials = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || num_trials <= 0) {
      fprintf(stderr, "Number of trial must be a positive integer.\n");
      return EXIT_FAILURE;
    }
  }

  // Open input file and read the hands in it
  const char *file = argv[1];
  FILE *f = fopen(file, "r");
  if (f == NULL) {
    perror("Could not open input file");
    return EXIT_FAILURE;
  }
  size_t n_hands = 0;
  future_cards_t fc;
  fc.n_decks = 0;
  fc.decks = NULL;
  deck_t **hands = read_input(f, &n_hands, &fc);

  // Create deck with remaining cards
  deck_t *remaining_deck = build_remaining_deck(hands, n_hands);
  // Create an array to count how many times each hand wins, with
  // one more element for ties.
  int *results = calloc(n_hands + 1, sizeof(*results));
  
  // Do Monte Carlo trial for num_trials times
  // For each trial, shuffle remaining deck, assign unknown cards from
  // remaining deck, then compare hands and count the results
  for (long i = 0; i < num_trials; i++) {
    shuffle(remaining_deck);
    future_cards_from_deck(remaining_deck, &fc);

    size_t winning_hand = 0;
    int tie = 0;
    for (size_t j = 1; j < n_hands; j++) {
      int cmp = compare_hands(hands[j], hands[winning_hand]);
      if (cmp > 0) {
	winning_hand = j;
	tie = 0;
      } else if (cmp == 0) {
	tie = 1;
      }
    }
    if (tie) {
      results[n_hands]++;
    } else {
      results[winning_hand]++;
    }
  }
  for (size_t i = 0; i < n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n",
	   i, results[i], (unsigned int)num_trials,
	   (double)(results[i] * 100 / num_trials));
  }
  if (results[n_hands] > 0) {
    printf("And there were %u ties\n", results[n_hands]);
  }
  // Clean up
  fclose(f);
  free(results);
  free_deck(remaining_deck);
  for (size_t i = 0; i < n_hands; i++) {
    free_deck(hands[i]);
  }
  free(hands);
  free(fc.decks);
  
  return EXIT_SUCCESS;
}
