#include "log.h"

int main(int argc, char *argv[]) {
	data_t entry;
	int dataSize;
	time_t tcurrent;
	char *data;
	FILE *fp;
	int aflag = 0; // option to do the if stmt
	char *mvalue = NULL; // should log any value given here
	int c;

	// clear any old log that could exist
	clearLog();
	// getopt example
	while((c = getopt(argc, argv, "am:")) != -1) { // ck options
		switch(c) {
			case 'a':
				aflag = 1; 
				break;
			case 'm':
				mvalue = optarg;
				// send mvalue to logger 
				tcurrent = time(NULL);
				entry = (data_t){.time = tcurrent, .string = mvalue};
				addMsg(entry, argv[0]);
				break;
			case '?':
				if(optopt == 'm') { // init and add entry to log
					tcurrent = time(NULL);
					data = "Error: option -m requires an argument";
					entry = (data_t){.time = tcurrent, .string = data};
					addMsg(entry, argv[0]);
				} else { // init and add entry to log
					tcurrent = time(NULL);
					data = "Error: options available are  a & c";
					entry = (data_t){.time = tcurrent, .string = data};
					addMsg(entry, argv[0]);
				}
				break;
			default:
				printf("Unknown error occured");
		}
	}
	// perror example	
	if (aflag == 1) {// only do if user sets a flag
		rename("fakeFile.txt", "fakefile.txt"); // rename incase it exists
		fp = fopen("fakeFile.txt", "r");
		if (fp == NULL) {// should be true always
			perror("PError: ");
			// log for perror
			tcurrent = time(NULL);
			entry = (data_t){.time = tcurrent, .string = strerror(1)}; 
			addMsg(entry, argv[0]);
		}	
	}
	// another random 'error'
	tcurrent = time(NULL);
	entry = (data_t){.time = tcurrent, .string = "Test Error Entry"};
	addMsg(entry, argv[0]);
	// another random 'error'
	tcurrent = time(NULL);
	entry = (data_t){.time = tcurrent, .string = "Test Error Entry 2"};
	addMsg(entry, argv[0]);
	// another random 'error'
	tcurrent = time(NULL);
	entry = (data_t){.time = tcurrent, .string = "Test Error Entry 3"};
	addMsg(entry, argv[0]);
	// retrieve entire log
	data = getLog();
	// print entire log
	printf("The whole log:\n%s\n", data);
	saveLog("log.txt");
	return 0;
}
