#include "log.h"

int main() {
	data_t entry;
	int dataSize;
	time_t tcurrent;
	char *data;

	data = "test string";
	tcurrent = time(NULL);
	printf("The current time is %s", ctime(&tcurrent));
	// initialize test entry for log
	entry = (data_t){.time = ctime(&tcurrent), .string = data};	
	// add message to log
	addMsg(entry);
	// retrieve entire log
	data = getLog();
	// print entire log
	printf("%s", data);
	saveLog("Logs/log.txt");
	return 0;
}
