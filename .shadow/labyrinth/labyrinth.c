#include "labyrinth.h"
#include "../testkit/testkit.h"
#include <assert.h>
// #include <bits/getopt_ext.h>
#include <bits/getopt_core.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// directions=[up,down,left,right]
const char *directions[4] = {"up", "down", "left", "right"};

int up[2] = {-1, 0};
int down[2] = {1, 0};
int left[2] = {0, -1};
int right[2] = {0, 1};

int direction_vectors[4][2] = {
    {-1, 0}, // up
    {1, 0},  // down
    {0, -1}, // left
    {0, 1}   // right
};

// struct for long options
static struct option long_options[] = {
    {"map", required_argument, 0, 'm'},    // --map|-m file
    {"player", required_argument, 0, 'p'}, // --player|-p ID
    {"move", required_argument, 0, 1000},  // --move DIRECTION
    {"version", no_argument, 0, 1001},     // --version
    {0, 0, 0, 0}};

// labyrinth [-m|--map FILE] [-p|--player ID] [--move DIRECTION] [--version]

int main(int argc, char *argv[]) {
  // check the arguments
  if (argc <= 1) {
    perror("Error:Invalid number of arguments.Please check the help");
    return 1;
  }

  // Initiate
  Labyrinth *labyrinth = (Labyrinth *)malloc(sizeof(Labyrinth));
  char player;

  int opt;
  int option_index = 0;

  // flags
  int player_flag = 0;

  while ((opt = getopt_long(argc, argv, "m:p:", long_options, &option_index)) !=
         -1) {
    switch (opt) {
    case 1001: // --version
      printf("%s", VERSION_INFO "1.0\n");
      printf("%s", "Presented By JYY&SillyCheese:)\n");
      printUsage();
      return 0;

    case 'm': //--map|-m

      if (loadMap(labyrinth, optarg)) {

        if (!isConnected(labyrinth)) {
          perror("The map is not connected!\n");
          return 1;
        }

        // print map
        for (int i = 0; i < labyrinth->rows; i++) {
          printf("%s\n", labyrinth->map[i]);
        }
        // printf("map  test\n");

      } else {
        return 1;
      }
      break;

    case 'p': //--player
      if (strlen(optarg) > 1) {
        printf("%s\n", optarg);
        perror("args is too many!");
        return 1;
      }
      if (isValidPlayer(optarg[0])) {
        player = optarg[0];
        player_flag = 1;
      } else {
        return 1;
      }
      break;

    case 1000: //--move DIRECTION
      if (player_flag == 1) {

        // check move
        printf("%s\n", "move test");

        if (movePlayer(labyrinth, player, optarg)) {
          player_flag = 0;
          return 0;
        } else {
          return 1;
        }
      } else {
        return 1;
      }
      break;

    case '?':
      fprintf(stderr, "unknown options: -%c\n", optopt);
      printUsage();
      return 1;
      break;
    }
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

  // printf("load test \n");

  //  num of row and col
  int rNum = 0, cNum = 0;

  file = fopen(filename, "r");
  if (file == NULL) {
    perror("Can't open this file");
    return false;
  }

  int c_tNum = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      rNum++;
      c_tNum = cNum;
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

  labyrinth->cols = c_tNum;
  labyrinth->rows = rNum;

  fclose(file);

  return true;
}

Position findPlayer(Labyrinth *labyrinth, char playerId) {
  Position pos = {-1, -1};

  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; j++) {
      if (labyrinth->map[i][j] == playerId) {
        pos.row = i;
        pos.col = j;
        break;
      }
    }
  }
  return pos;
}

Position findFirstEmptySpace(Labyrinth *labyrinth) {
  Position pos = {-1, -1};

  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; j++) {
      if (labyrinth->map[i][j] == '.') {
        pos.row = i;
        pos.col = j;
        break;
      }
    }
  }
  return pos;
}

bool isEmptySpace(Labyrinth *labyrinth, int row, int col) {
  if (labyrinth->map[row][col] == '.') {
    return true;
  }
  return false;
}

bool movePlayer(Labyrinth *labyrinth, char playerId, const char *direction) {

  Position Playerpos = {-1, -1};

  if (isValidPlayer(playerId)) {
    Playerpos = findPlayer(labyrinth, playerId);

    // if player is not in the map now
    if (Playerpos.row == -1 && Playerpos.col == -1) {

      Position newPlayerpos = findFirstEmptySpace(labyrinth);

      if (newPlayerpos.row == -1 && newPlayerpos.col == -1) {
        perror("the map now is no empty space now");
        return false;
      }

      // update new gamer position
      labyrinth->map[newPlayerpos.row][newPlayerpos.col] = playerId;

      return true;
    }

    // if player need to up
    if (strcmp(direction, "up") == 0) {
      printf("mp test \n");
      Position newpos = {Playerpos.row + up[0], Playerpos.col + up[1]};
      if (isEmptySpace(labyrinth, newpos.row, newpos.col)) {

        // remove old gamer position
        labyrinth->map[Playerpos.row][Playerpos.col] = '.';

        // update new gamer position
        labyrinth->map[newpos.row][newpos.col] = playerId;

        return true;
      }
    }

    // if player need to down
    if (strcmp(direction, "down")) {
      Position newpos = {Playerpos.row + down[0], Playerpos.col + down[1]};
      if (isEmptySpace(labyrinth, newpos.row, newpos.col)) {

        // remove old gamer position
        labyrinth->map[Playerpos.row][Playerpos.col] = '.';

        // update new gamer position
        labyrinth->map[newpos.row][newpos.col] = playerId;

        return true;
      }
    }

    // if player need to left
    if (strcmp(direction, "left")) {
      Position newpos = {Playerpos.row + left[0], Playerpos.col + left[1]};
      if (isEmptySpace(labyrinth, newpos.row, newpos.col)) {

        // remove old gamer position
        labyrinth->map[Playerpos.row][Playerpos.col] = '.';

        // update new gamer position
        labyrinth->map[newpos.row][newpos.col] = playerId;

        return true;
      }
    }

    // if player need to right
    if (strcmp(direction, "right")) {
      Position newpos = {Playerpos.row + right[0], Playerpos.col + right[1]};
      if (isEmptySpace(labyrinth, newpos.row, newpos.col)) {

        // remove old gamer position
        labyrinth->map[Playerpos.row][Playerpos.col] = '.';

        // update new gamer position
        labyrinth->map[newpos.row][newpos.col] = playerId;

        return true;
      }
    }
  }

  return false;
}

bool saveMap(Labyrinth *labyrinth, const char *filename) {
  FILE *file = fopen(filename, "w");

  // if file cant be open
  if (file == NULL) {
    perror("can't open this file to save map");
    return false;
  }

  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; j++) {
      fprintf(file, "%c", labyrinth->map[i][j]);
      if (j == labyrinth->cols - 1 && i != labyrinth->rows - 1) {
        fprintf(file, "%c", '\n');
      }
    }
  }

  return true;
}

// Check if all empty spaces are connected using DFS
void dfs(Labyrinth *labyrinth, int row, int col,
         bool visited[MAX_ROWS][MAX_COLS]) {
  // has been visited
  if (visited[row][col] == true) {
    return;
  }

  if (labyrinth->map[row][col] == '#') {
    return;
  }

  // traversal this node for all directions if it is a empty or player
  if (labyrinth->map[row][col] == '.' ||
      (labyrinth->map[row][col] >= '0' && labyrinth->map[row][col] <= '9')) {
    visited[row][col] = true;
    for (int i = 0; i < 4; i++) {
      dfs(labyrinth, row + direction_vectors[i][0],
          col + direction_vectors[i][1], visited);
    }
  }
}

bool isConnected(Labyrinth *labyrinth) {
  // initiate visited
  bool visited[MAX_ROWS][MAX_COLS];
  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; j++) {
      visited[i][j] = false;
    }
  }

  Position pos = findFirstEmptySpace(labyrinth);
  // dfs
  dfs(labyrinth, pos.row, pos.col, visited);

  // check whether all empty node has been visited
  for (int i = 0; i < labyrinth->rows; i++) {
    for (int j = 0; j < labyrinth->cols; j++) {
      if (labyrinth->map[i][j] == '.' ||
          (labyrinth->map[i][j] >= '0' && labyrinth->map[i][j] <= '9')) {
        if (visited[i][j] == false) {
          return false;
        }
      }
    }
  }
  return true;
}
