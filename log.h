#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_struct {
	time_t time;
	char *string;
} data_t;

static int addMsg(data_t data);
static void clearLog(void);
static char *getLog(void);
static int saveLog(char *filename);
