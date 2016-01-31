#include "log.h"

int main() {
	data_t entry;
	int dataSize;
	time_t tcurrent;
	char *data;
	FILE *fp;

	clearLog();
	data = "test string";
	tcurrent = time(NULL);
	// initialize test entry for log
	entry = (data_t){.time = tcurrent, .string = data}; // need ctime(&tcurrent) to get output time string	
	// add message to log
	addMsg(entry);

	// perror & getopt example TODO
	rename("fakeFile.txt", "fakefile.txt"); // rename incase it exists
	fp = fopen("fakeFile.txt", "r");
	if (fp == NULL) {// should be true always
		perror("PError: ");
		// log for perror
		tcurrent = time(NULL);
		entry = (data_t){.time = tcurrent, .string = "Error: "}; 
		addMsg(entry);
	}	
	// another random 'error'
	tcurrent = time(NULL);
	entry = (data_t){.time = tcurrent, .string = "Error2: "};
	addMsg(entry);
	// another random 'error'
	/*tcurrent = time(NULL);
	entry = (data_t){.time = tcurrent, .string = "Error3: "};
	addMsg(entry);*/
	// retrieve entire log
	data = getLog();
	// print entire log
	printf("The whole log:\n%s\n", data);
	saveLog(NULL);
	return 0;
}
