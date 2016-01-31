#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

int addMsg(data_t data) {
	log_t *newNode;
	int nodeSize;
	log_t *curPtr = NULL;
	int itemNum = 0;
	nodeSize = sizeof(log_t) + strlen(data.string) + 1;
	if((newNode = (log_t *)(malloc(nodeSize))) == NULL) { /*couldn't add node*/
		return -1;
	}
	newNode->item.time = data.time;
	newNode->item.string = (char *)newNode + sizeof(log_t);
	strcpy(newNode->item.string, data.string);
	newNode->next == NULL;
	if (headptr == NULL) { // if log is empty set the headptr
		printf("Setting headpt\n");
		headptr = newNode;
	} else {
		printf("Setting item\n");
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
}

char *getLog(void) {
	int numOfEntries = 0;
	int size = 1;
	log_t *curNode = headptr;
	char *entireLogHolder = NULL;
	char *entryForFormat = NULL;
	if (headptr == NULL) { // nothing to return if empty list
		return NULL;
	} 
	// cycle through linked list and get total string length
	while (curNode != NULL) { // should always go through at least once
		numOfEntries++;
		size += strlen(curNode->item.string);
		size += strlen(ctime(&curNode->item.time));
		curNode = curNode->next;
	}
	//printf("NumEntries: %d Size: %d\n", numOfEntries, size);
	entireLogHolder = malloc(sizeof(char)*(size+1+numOfEntries)); // total string length plus 1 for \0
	if(entireLogHolder == NULL) {
		printf("malloc failed\n");
		return NULL;
	}
	curNode = headptr;
	while (curNode != NULL) { // concat each string to the log holder
		//printf("\n getLog: getting data for entry: %d\n", counter);
		entryForFormat = ctime(&curNode->item.time);
		if( strlen(entryForFormat) > 1) { // remove the line break at the end
			entryForFormat[strlen(entryForFormat)-1] = ':';
		}	
		entryForFormat = strcat(entryForFormat, curNode->item.string);
		//printf("|%s|", entireLogHolder);
		entireLogHolder = strcat(entireLogHolder, entryForFormat);
		entireLogHolder = strcat(entireLogHolder, "\n");
		curNode = curNode->next;
	}	
	entireLogHolder += (strlen(entireLogHolder) - size - (numOfEntries-1));
	//printf("\n RETURN: %d --  %s\n", strlen(entireLogHolder), entireLogHolder);
	return entireLogHolder;
}

int saveLog(char *filename) {
	FILE * fp;
	char *logToWrite = NULL;
	fp = fopen("log.txt", "a");
	logToWrite = getLog();
	if(logToWrite == NULL) {
		printf("Log is empty\n");
		return 0;
	}	
	fprintf(fp, "Testing fprintf...\n%s\n", logToWrite);
	fclose(fp);
	return 0;
}	


