#include "labyrinth.h"
#include "../testkit/testkit.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // check the arguments
  if (argc <= 1) {
    perror("Error:Invalid number of arguments.Please check the help");
    return 1;
  }
}

void printUsage() {
  printf("Usage:\n");
  printf("  labyrinth --map map.txt --player id\n");
  printf("  labyrinth -m map.txt -p id\n");
  printf("  labyrinth --map map.txt --player id --move direction\n");
  printf("  labyrinth --version\n");
}

bool isValidPlayer(char playerId) {
  if (playerId >= '0' && playerId <= '9') {
    return true;
  }
  return false;
}

bool loadMap(Labyrinth *labyrinth, const char *filename) {
  // basic tool for check the file
  FILE *file;
  char ch;

  // num of row and col
  int rNum, cNum = 0;

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Can't open this file");
    return 1;
  }

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      rNum++;
      cNum = 0;
      continue;
    }
    // row,col 's num are illegal
    if (rNum >= MAX_ROWS || cNum >= MAX_COLS) {
      perror("row or col 's num is out of limit");
      return false;
    }
    labyrinth->map[rNum][cNum] = ch;
    cNum++;
  }

  labyrinth->cols = cNum;
  labyrinth->rows = rNum;

  fclose(file);

  return true;
}

Position findPlayer(Labyrinth *labyrinth, char playerId) {
  Position pos = {-1, -1};

  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; i++) {
      if (labyrinth->map[i][j] == playerId) {
        pos.row = i;
        pos.col = j;
      }
    }
  }
  return pos;
}

Position findFirstEmptySpace(Labyrinth *labyrinth) {
  Position pos = {-1, -1};

  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; i++) {
      if (labyrinth->map[i][j] == '.') {
        pos.row = i;
        pos.col = j;
      }
    }
  }
  return pos;
}

bool isEmptySpace(Labyrinth *labyrinth, int row, int col) {
  // TODO: Implement this function
  if (labyrinth->map[row][col] == '.') {
    return true;
  }
  return false;
}

bool movePlayer(Labyrinth *labyrinth, char playerId, const char *direction) {
  // TODO: Implement this function
  return false;
}

bool saveMap(Labyrinth *labyrinth, const char *filename) {
  // TODO: Implement this function
  return false;
}

// Check if all empty spaces are connected using DFS
void dfs(Labyrinth *labyrinth, int row, int col,
         bool visited[MAX_ROWS][MAX_COLS]) {
  // TODO: Implement this function
}

bool isConnected(Labyrinth *labyrinth) {
  // TODO: Implement this function
  return false;
}
