#include "ll_cycle.h"
#include <stddef.h>

int ll_has_cycle(node *head) {
  /* your code here */
  if (!head)
    return 0;
  node *tortoise = head;
  node *hare = head;
  if (!hare->next)
    return 0;
  while (1) {
    hare = hare->next;
    if (!hare)
      return 0;
    hare = hare->next;
    if (!hare)
      return 0;
    tortoise = tortoise->next;
    if (tortoise == hare)
      return 1;
  }
  return 0;
}
