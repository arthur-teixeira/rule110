#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 90

typedef enum {
  ALIVE,
  DEAD,
} CellState;

void print_gen(CellState gen[COLS]) {
  for (size_t i = 0; i < COLS; i++) {
    switch (gen[i]) {
    case ALIVE:
      putchar('*');
      break;
    case DEAD:
      putchar(' ');
      break;
    }
  }
  putchar('\n');
}

CellState compute_cell(CellState a, CellState b, CellState c) {
  if (a == ALIVE && b == ALIVE && c == ALIVE) return DEAD; // 111
  if (a == ALIVE && b == ALIVE && c == DEAD) return ALIVE; // 110
  if (a == ALIVE && b == DEAD && c == ALIVE) return ALIVE; // 101
  if (a == ALIVE && b == DEAD && c == DEAD) return DEAD; // 100
  if (a == DEAD && b == ALIVE && c == ALIVE) return ALIVE; // 011
  if (a == DEAD && b == ALIVE && c == DEAD) return ALIVE; // 010
  if (a == DEAD && b == ALIVE && c == DEAD) return ALIVE; // 010
  if (a == DEAD && b == DEAD && c == ALIVE) return ALIVE; // 001
  if (a == DEAD && b == DEAD && c == DEAD) return DEAD; // 000

  assert(0 && "unreachable");
}

void compute_next_gen(CellState new[COLS], CellState prev[COLS]) {
  for (size_t i = 1; i < COLS - 1; i++) {
    new[i] = compute_cell(prev[i-1], prev[i], prev[i+1]);
  }
}

int main(void) {
  CellState gen[COLS];
  CellState buffer[COLS];
  for (size_t i = 0; i < COLS; i++) {
    gen[i] = DEAD;
    buffer[i] = DEAD;
  }
  gen[COLS - 1] = ALIVE;

  for (size_t i = 0; i < COLS; i++) {
    compute_next_gen(buffer, gen);
    print_gen(buffer);

    for (size_t i = 0; i < COLS; i++) {
      gen[i] = buffer[i];
    }
  }

  return 0;
}
