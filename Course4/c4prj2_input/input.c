#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "deck.h"
#include "cards.h"
#include "future.h"

// Read a line into a hand
deck_t * hand_from_string(const char * str, future_cards_t * fc) {
  deck_t * hand = malloc(sizeof(*hand));
  if (hand == NULL) {
    perror("Could not allocate memory for hand");
    exit(EXIT_FAILURE);
  }
  hand->n_cards = 0;
  hand->cards = NULL;

  const char * ptr = str;
  while (*ptr != '\n' && *ptr != '\0'){
    if (isspace(*ptr)) {
      ptr++;
      continue;
    }

    if (*ptr == '?') {
      ptr++;
      char * endptr;
      long idx = strtol(ptr, &endptr, 10);
      if (endptr == ptr || idx < 0) {
	perror("Invalide future card");
	exit(EXIT_FAILURE);
      }
      card_t * placeholder = add_empty_card(hand);
      add_future_card(fc, (size_t)idx, placeholder);
      ptr = endptr;
    } else {
      if (*(ptr + 1) == '\0') {
	perror("Invalide card input");
	exit(EXIT_FAILURE);
      }
      card_t c = card_from_letters(*ptr, *(ptr + 1));
      add_card_to(hand, c);
      ptr += 2;
    }
  }
  return hand;
}

// Read a file of hands into a decks array
deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
  char * line = NULL;
  size_t size = 0;
  ssize_t nread;
  deck_t ** hands = NULL;
  *n_hands = 0;
  
  while ((nread = getline(&line, &size, f)) != -1) {
    deck_t * hand = hand_from_string(line, fc);
    if (hand->n_cards < 5) {
      perror("A hand must have at least 5 cards");
      exit(EXIT_FAILURE);
    }
    hands = realloc(hands, (*n_hands + 1) * sizeof(*hands));
    if (hands == NULL) {
      perror("Could not reallocate for hands");
      exit(EXIT_FAILURE);
    }
    hands[*n_hands] = hand;
    (*n_hands)++;
  }
  free(line);
  return hands;
}
