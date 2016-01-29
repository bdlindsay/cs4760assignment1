#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "log.h"
#define TRAV_INIT_SIZE 8

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addMsg(data_t data) {
	log_t *newNode;
	int nodeSize;

	nodeSize = sizeof(log_t) + strlen(data.string) + 1;
	if((newNode = (log_t *)(malloc(nodeSize))) == NULL) { /*couldn't add node*/
		return -1;
	}

	newNode->item.time = data.time;
	newNode->item.string = (char *)newNode + sizeof(log_t);
	strcpy(newNode->item.string, data.string);
	newNode->next == NULL;
	if (headptr == NULL) {
		headptr = newNode;
	} else {
		tailptr->next = newNode;
	}
	tailptr = newNode;

	return 0;
}

void clearLog(void) {
	log_t *tmpNode;
	while((tmpNode = headptr) != NULL) {
		headptr = headptr->next;
		free(tmpNode);
	}	
	tailptr->next = NULL;
	tailptr = NULL;
}

char *getLog(void) {
	int size = 0;
	log_t *curNode = headptr;
	char *entireLogHolder = NULL;
	if (headptr == NULL) { // nothing to return if empty list
		return NULL;
	}	
	// cycle through linked list and get total string length
	while (curNode != NULL) {
		size += strlen(curNode->item.string);
		curNode = curNode->next;
	}
	entireLogHolder = malloc(sizeof(char)*(size+1)); // total string length plus 1 for \0
	if(entireLogHolder == NULL) {
		printf("malloc failed\n");
		return NULL;
	}
	curNode = headptr;
	// concating extra values at the beginning TODO fix bug
	while (curNode != NULL) { // concat each string to the log holder
		entireLogHolder = strcat(entireLogHolder, curNode->item.string);
		curNode = headptr->next;
	}	
	return entireLogHolder;
}

int saveLog(char *filename) {
	FILE * fp;
	char *logToWrite = NULL;
	fp = fopen(filename, "w");
	logToWrite = getLog();
	if(logToWrite == NULL) {
		printf("getLog returned NULL");
		return -1;
	}	
	fprintf(fp, "Testing fprintf...\n%s\n", logToWrite);
	fputs("Testing fputs...\n", fp);
	fclose(fp);
	return 0;
}	
