#include <stdio.h>

#define ANSI_COLOR_BOLD    "\x1b[1m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define error(format, ...) fprintf(stderr, ANSI_COLOR_BOLD ANSI_COLOR_RED format ANSI_COLOR_RESET, ##__VA_ARGS__);

struct TrustworthyCommand {
  char *name;
  int parameters;
  void *callback;
};

static struct TrustworthyCommand commands[] = {
  {"version", 0, NULL},
  {NULL, 0, NULL}
};

int main(int argc, char *argv[]) {
  for (int i = 0; 1; i++) {
    struct TrustworthyCommand command = commands[i];
    if (command.name == NULL) {
      break;
    }

    printf("Command: %s\n", command.name);
  }
  return 0;
}
