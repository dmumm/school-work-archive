#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

int max_chars(char[][], int);
int max_index(char[][], int);
int min_chars(char[][], int);
int min_index(char[][], int);
void show_all(char[][], int);

#define MAX_TWEET_SIZE 200
#define MAX_TWEETS 1000
