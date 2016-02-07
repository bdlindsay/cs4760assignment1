#include "log.h"

typedef struct list_struct {
	data_t item;
	struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

// add message edited from Robins & Robins programming ex. 2.7
int addMsg(data_t data, char *argv0) {
	log_t *newNode;
	int nodeSize;
	log_t *curPtr = NULL;
	int itemNum = 0;
	// allocate the node - 10 for ": Error: "\0
	nodeSize = sizeof(log_t) + strlen(data.string) + strlen(argv0) + 10;
	if((newNode = (log_t *)(malloc(nodeSize))) == NULL) { /*couldn't add node*/
		perror("Error Malloc failure: additional details: ");
		return -1;
	}
	// set data for new node
	newNode->item.time = data.time;
	newNode->item.string = (char *)newNode + sizeof(log_t);
	strcpy(newNode->item.string, argv0);
	newNode->item.string = strcat(newNode->item.string, ": Error: ");
	newNode->item.string = strcat(newNode->item.string, data.string);
	newNode->next = NULL;
	// add it to the linked list
	if (headptr == NULL) { // if log is empty set the headptr
		headptr = newNode;
	} else {
		tailptr->next = newNode;
	}
	tailptr = newNode;

	return 0;
}

void clearLog(void) {
	log_t *tmpNode;
	// free the memory for the entire list
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
	// total string length plus 1 for \0 : numOfEntires * 2 to add formatting to log
	entireLogHolder = malloc(sizeof(char)*(size+1+(numOfEntries*2))); 
	if(entireLogHolder == NULL) {
		perror("Error Malloc failure: additional details: ");
		return NULL;
	}
	// format and combine the logs into one char*
	curNode = headptr;
	while (curNode != NULL) { // concat each string to the log holder
		entryForFormat = ctime(&curNode->item.time);
		if( strlen(entryForFormat) > 1) { // remove the line break at the end
			entryForFormat[strlen(entryForFormat)-1] = ':';
		}	
		entryForFormat = strcat(entryForFormat, curNode->item.string);
		entireLogHolder = strcat(entireLogHolder, entryForFormat);
		entireLogHolder = strcat(entireLogHolder, "\n");
		curNode = curNode->next;
	}	
	entireLogHolder += (strlen(entireLogHolder) - size - (numOfEntries-1));
	return entireLogHolder;
}

int saveLog(char *filename) {
	FILE * fp;
	char *logToWrite;
	// prepare to append to log.txt
	fp = fopen("log.txt", "a");
	if(!fp) {
		perror("Open file error: ");
		return -1;
	}	
	// get the log to write to the file
	logToWrite = getLog();
	// if there is no logs saved
	if(logToWrite == NULL) {
		printf("Log is empty\n");
		return 0;
	}	
	// write to the file
	fprintf(fp,"%s\n", logToWrite);
	fclose(fp);
	return 0;
}	


