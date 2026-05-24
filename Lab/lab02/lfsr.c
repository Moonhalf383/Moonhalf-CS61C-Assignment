#include "lfsr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lfsr_calculate(uint16_t *reg) { /* YOUR CODE HERE */
  *reg =
      *reg >> 1 |
      (((*reg & 1) ^ ((*reg >> 2) & 1) ^ ((*reg >> 3) & 1) ^ ((*reg >> 5) & 1))
       << 15);
}
