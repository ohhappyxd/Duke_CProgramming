#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
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
  if (argc = 3) {
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
  future_card_t fc;
  fc.n_decks = 0;
  fc.decks = NULL;
  deck_t **hands = read_input(f, &n_hands, &fc);

  // Create deck with remaining cards
  deck_t *remaining_deck = build_remaining_deck(hands, n_hands);
  // Create an array to count how many times each hand wins, with
  // one more element for ties.
  int *results = calloc(n_hands + 1, sizeof(*results));

  // Clean up
  fclose(f);
  /*
   - Do each Monte Carlo trial (repeat num_trials times)
        - Shuffle the deck of remaining cards
	  (you wrote shuffle in Course 3)
	- Assign unknown cards from the shuffled deck
	  (you just wrote future_cards_from_deck)
	- Use compare_hands (from Course 3) to
	  figure out which hand won. Note that
	  with potentially more than 2 hands,
	  this is much like finding the max of
	  an array, but using compare_hands
	  instead of >.
        - Increment the win count for the winning
	  hand (or for the "ties" element of the array
	  if there was a tie).
   - After you do all your trials, you just need
     to print your results, free any memory
     you allocated, and close any open files.
  */

  return EXIT_SUCCESS;
}
