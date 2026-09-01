#include <iostream>

#define NUM_ROWS 5
#define NUM_COLS 4

class Grid {
public:
  Grid() {
    // Allocate a 2D grid
    for (int r = 0; r < NUM_ROWS; r++) {
      grid[r] = new int[NUM_COLS];
      for (int c = 0; c < NUM_COLS; c++) {
        grid[r][c] = r * NUM_COLS + c;
      }
    }
  }

  ~Grid() {
    for (int r = 0; r < NUM_ROWS; r++) {
      delete[] grid[r];
    }
  }

  // BUG: Off-by-one error - starts at NUM_ROWS instead of NUM_ROWS-1
  int findInLastColumn(int value) {
    for (int r = NUM_ROWS; r >= 0; r--) {   // BUG: Should be NUM_ROWS - 1
      if (grid[r][NUM_COLS - 1] == value) { // Out of bounds on first iteration!
        return r;
      }
    }
    return -1;
  }

  void print() {
    for (int r = 0; r < NUM_ROWS; r++) {
      for (int c = 0; c < NUM_COLS; c++) {
        std::cout << grid[r][c] << " ";
      }
      std::cout << "\n";
    }
  }

private:
  int *grid[NUM_ROWS];
};

int main() {
  Grid grid;

  std::cout << "Grid contents:\n";
  grid.print();

  std::cout << "\nSearching for value 15 in last column...\n";
  int row = grid.findInLastColumn(15);

  if (row >= 0) {
    std::cout << "Found at row " << row << "\n";
  } else {
    std::cout << "Not found\n";
  }

  return 0;
}
