// Copyright 2022 brietamm@student.21-school.ru,
// yurihyde@student.21-school.ru,
// nymossha@student.21-school.ru

#include <stdio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define SCORE_X 10
#define ROCKET_POS1 12
#define ROCKET_POS2 12
#define CENTER_X 40
#define CENTER_Y 13
#define POINTS_TO_WIN 21

void render_field(int rocket1, int rocket2, int ball_x, int ball_y,
  int sc_pl1, int sc_pl2);

int move_ball_x(int current_pos_x, int speed_x);

int move_ball_y(int current_pos_y, int speed_y);

int roumd(int score1, int score2, int last_winner);

int move_rocket(int rocket, char ch);

void winner_screen(int winner);

int main() {
  int last_winner = 1;
  char restart = 'y';
  while (restart == 'y' || restart == 'Y') {
    int score_player1_score = 0, score_player2_score = 0;
    while ((score_player1_score < POINTS_TO_WIN) &&
           (score_player2_score < POINTS_TO_WIN)) {
      last_winner = roumd(score_player1_score, score_player2_score,
                          last_winner);
      if (last_winner == 1) {
        score_player1_score += 1;
      } else {
        score_player2_score += 1;
      }
    }
    if (score_player1_score == POINTS_TO_WIN) {
      winner_screen(1);
    } else {
      winner_screen(2);
    }
    scanf("%c", & restart);
  }
  return 0;
}

int move_ball_x(int current_pos_x, int speed_x) {
  int new_position_x = current_pos_x + speed_x;
  if ((new_position_x >= 0) && (new_position_x <= SCREEN_WIDTH)) {
    return new_position_x;
  }
  return -1;
}

int move_ball_y(int current_pos_y, int speed_y) {
  int new_position_y = current_pos_y + speed_y;
  if ((new_position_y >= 0) && (new_position_y <= SCREEN_HEIGHT)) {
    return new_position_y;
  }
  return -1;
}

int roumd(int score1, int score2, int last_winner) {
  int current_rocket1_pos = ROCKET_POS1, current_rocket2_pos = ROCKET_POS2;
  int current_ball_x_pos = CENTER_X, current_ball_y_pos = CENTER_Y;
  int current_ball_speed_x = 1 * last_winner, current_ball_speed_y = 1;
  char ch1 = ' ', trash = ' ';
  render_field(current_rocket1_pos, current_rocket2_pos, current_ball_x_pos,
    current_ball_y_pos, score1, score2);
  while (1) {
    scanf("%c", & ch1);
    while (trash != '\n') {
        scanf("%c", & trash);
    }
    trash = ' ';

    if (ch1 == 'A' || ch1 == 'a' || ch1 == 'Z' ||
        ch1 == 'z' || ch1 == 'K' || ch1 == 'k' ||
        ch1 == 'M' || ch1 == 'm' || ch1 == ' ' || ch1 == '\n') {
        if (ch1 == 'A' || ch1 == 'a' || ch1 == 'Z' || ch1 == 'z') {
            current_rocket1_pos = move_rocket(current_rocket1_pos, ch1);
            }
        if (ch1 == 'K' || ch1 == 'k' || ch1 == 'M' || ch1 == 'm') {
            current_rocket2_pos = move_rocket(current_rocket2_pos, ch1);
            }
        current_ball_x_pos = move_ball_x(current_ball_x_pos,
                                         current_ball_speed_x);
        current_ball_y_pos = move_ball_y(current_ball_y_pos,
                                         current_ball_speed_y);
    }

    if ((current_ball_y_pos == SCREEN_HEIGHT - 2) ||
        (current_ball_y_pos == 1)) {
      current_ball_speed_y = -1 * current_ball_speed_y;
    }
    if (current_ball_x_pos == 2) {
      return -1;
    }
    if (current_ball_x_pos == SCREEN_WIDTH - 3) {
      return 1;
    }
    if ((current_ball_x_pos == SCREEN_WIDTH - 4) || (current_ball_x_pos == 3)) {
      if (current_ball_x_pos == 3) {
        if (((current_rocket1_pos <= current_ball_y_pos + 1) &&
            (current_rocket1_pos >= current_ball_y_pos - 1))) {
          current_ball_speed_x = -1 * current_ball_speed_x;
        }
      }
      if (current_ball_x_pos == SCREEN_WIDTH - 4) {
        if (((current_rocket2_pos <= current_ball_y_pos + 1) &&
            (current_rocket2_pos >= current_ball_y_pos - 1))) {
          current_ball_speed_x = -1 * current_ball_speed_x;
        }
      }
    }
    render_field(current_rocket1_pos, current_rocket2_pos,
                 current_ball_x_pos, current_ball_y_pos,
                 score1, score2);
  }
}


// Moving platforms
int move_rocket(int rocket, char ch) {
  if ((ch == 'A' || ch == 'a' || ch == 'K' || ch == 'k') && (rocket - 3 >= 0)) {
    return --rocket;
  } else if ((ch == 'Z' || ch == 'z' || ch == 'M' || ch == 'm') &&
    (rocket + 3 <= SCREEN_HEIGHT - 1)) {
    return ++rocket;
  } else {
    return rocket;
  }
}

void render_field(int rocket1, int rocket2,
  int ball_x, int ball_y, int sc_pl1, int sc_pl2) {
  printf("\033[0d\033[2J");
  for (int y = -5; y < SCREEN_HEIGHT; ++y) {
    if (y == -3) {
      for (int x = 0; x < SCREEN_WIDTH; ++x) {
        if (x == 0 || x == 40 || x == SCREEN_WIDTH - 1) {
          putchar('|');
        } else if (x == SCORE_X) {
          printf("Player 1 score: %d", sc_pl1);
          if (sc_pl1 < 10) {
            x += 16;   // 16 is the srlen("Player 1 score: %d")
              // when sc_pl1 < 10, otherwise 17
          } else {
              x += 17;
            }
        } else if (x == SCORE_X + 40) {
          printf("Player 2 score: %d",
            sc_pl2);   // 16 is the srlen("Player 2 score: %d")
            // when sc_pl2 < 10, otherwise 17
          if (sc_pl2 < 10) {
              x += 16;
            } else {
                x += 17;
                }
        } else  {
            putchar(' ');
            }
      }
    } else if (y == -5) {
      for (int x = 0; x < SCREEN_WIDTH; ++x) {
        putchar('v');
      }
    } else if (y == -1) {
      for (int x = 0; x < SCREEN_WIDTH; ++x) {
        putchar('^');
      }
    } else {
      for (int x = 0; x < SCREEN_WIDTH; ++x) {
        if ((y == 0 || y == SCREEN_HEIGHT - 1) &&
            x != 0 && x != SCREEN_WIDTH - 1) {
          // check for borders
          putchar('-');
        } else if (x == ball_x && y == ball_y) {
          putchar('@');
        } else if ((x == 0 || x == SCREEN_WIDTH / 2 ||
            x == SCREEN_WIDTH - 1) && y != 0 && y != SCREEN_HEIGHT - 1) {
          // check for borders
          putchar('|');  // don't forget to add 'if(roc_y)' in mov_func
        } else if ((x == 2 && (y == rocket1 - 1 ||
                               y == rocket1 || y == rocket1 + 1)) ||
          // check for rockets
          (x == SCREEN_WIDTH - 3 && (y == rocket2 - 1 ||
                                     y == rocket2 || y == rocket2 + 1))) {
          printf("|");
        } else if ((x == 0 && y == 0) || (x == SCREEN_WIDTH - 1 && y == 0) ||
          // check for corners
          (x == SCREEN_WIDTH - 1 && y == SCREEN_HEIGHT - 1) ||
                   (x == 0 && y == SCREEN_HEIGHT - 1) ||
          (x == 0 && y == -2) || (x == SCREEN_WIDTH - 1 && y == -2)) {
          putchar('+');
        } else {
          putchar(' ');
        }
      }
    }
    putchar('\n');
  }
}

void winner_screen(int winner) {
    if (winner == 1) {
        for (int y = -5; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                if (y == -5 || y == SCREEN_HEIGHT - 1) {
                    // check for borders
                    printf("*");
                } else if (x == 0 || x == SCREEN_WIDTH - 1) {
                    // check for borders
                    printf("*");
                } else if (x == 9 && y == 8) {
                    printf("    ____  __             "
                           "            ___            _     ");
                    x += 57;
                } else if (x == 9 && y == 9) {
                    printf("   / __ \\/ /___ ___  _____ "
                           " _____   <  /  _      __(_)___ ");
                    x += 57;
                } else if (x == 9 && y == 10) {
                    printf("  / /_/ / / __ `/ / / / _ \\/ ___/"
                           "   / /  | | /| / / / __ \\");
                    x += 57;
                } else if (x == 9 && y == 11) {
                    printf(" / ____/ / /_/ / /_/ /  __/ /  "
                           "    / /   | |/ |/ / / / / /");
                    x += 57;
                } else if (x == 9 && y == 12) {
                    printf("/_/   /_/\\__,_/\\__, /\\___/_/   "
                           "   /_/    |__/|__/_/_/ /_/ ");
                    x += 57;
                } else if (x == 9 && y == 13) {
                    printf("              /____/              "
                           "                        ");
                    x += 57;
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else {
        for (int y = -5; y < SCREEN_HEIGHT; ++y) {
            for (int x = 0; x < SCREEN_WIDTH; ++x) {
                if (y == 0 || y == SCREEN_HEIGHT - 1) {
                    // check for borders
                    printf("*");
                } else if ((x == 0 || x == SCREEN_WIDTH - 1) &&
                           y != SCREEN_HEIGHT - 1) {
                    // check for borders
                    printf("*");
                } else if (x == 8 && y == 10) {
                    printf("    ____  __               "
                           "          ___               _     ");
                    x += 60;
                } else if (x == 8 && y == 11) {
                    printf("   / __ \\/ /___ ___  _____  _____  "
                           " |__ \\    _      __(_)___ ");
                    x += 60;
                } else if (x == 8 && y == 12) {
                    printf("  / /_/ / / __ `/ / / / _ \\/ ___/  "
                           " __/ /   | | /| / / / __ \\");
                    x += 60;
                } else if (x == 8 && y == 13) {
                    printf(" / ____/ / /_/ / /_/ /  __/ /   "
                           "   / __/    | |/ |/ / / / / /");
                    x += 60;
                } else if (x == 8 && y == 14) {
                    printf("/_/   /_/\\__,_/\\__, /\\___/_/   "
                           "   /____/    |__/|__/_/_/ /_/ ");
                    x += 60;
                } else if (x == 8 && y == 15) {
                    printf("              /____/                  "
                           "                       ");
                    x += 60;
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    printf("Do you want to continue? [y/n]\n");
}


// TODO(brietamm): TO FIX A LOT OF ELIF STATEMENTS
// TODO(brietamm): TO CREATE HEADERS
// TODO(brietamm): MAYBE TO USE STRUCTS

// TODO(brietamm): TRY TO REWRITE ROUND FUNC
// TODO(brietamm): TRY TO ADD ASYNCHRONIC MOD
// TODO(brietamm): TO CREATE README
