#include "cards.h"

int main(void) {
  card_t test_card;
  test_card.value = 14;
  test_card.suit = SPADES;
  assert_card_valid(test_card);
  print_card(test_card);
  test_card = card_from_letters('J', 'd');
  print_card(test_card);
  test_card = card_from_num(51);
  print_card(test_card);
}
