#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "linear.h"
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
#define INF HUGE_VAL


void exit_input_error(int line_num);

static char* readline(FILE *input);


void exit_with_help();

void read_problem(const char *filename);

void do_predict(FILE *input, FILE *output);