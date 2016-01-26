#include <stdlib.h>
#include <string.h>
#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addMsg(data_t data) {
	return 0;
}

void clearLog(void) {
}

char *getLog(void) {
	return NULL;
}

int saveLog(char *filename) {
	return 0;
}	
