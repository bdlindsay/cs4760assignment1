#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct data_struct {
	time_t time;
	char *string;
} data_t;

int addMsg(data_t data, char *argv0);
void clearLog(void);
char *getLog(void);
int saveLog(char *filename);
