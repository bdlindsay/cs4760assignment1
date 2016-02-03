# cs4760assignment1
# Brett Lindsay
# 2-2-16
The main.c program is a test driver for logLib.c. Compile the code using the Makefile and the corresponding a.out can be used with the follow options:
-a : the program will use perror to send out an error message resulting from code designed to have an error as an example. 
-m [message] : -m "message here" will send the user specified message to be recorded in the log. 

recommended usage: a.out -am "my message"

Following the printing of the entire log for the program, the log will be saved to a file name log.txt in the working directory. 
