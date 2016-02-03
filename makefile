CC = gcc
CFLAGS = -g
LD = $(CC)
LDFLAGS =
RM = rm

EXE = a.out
SRCS = main.c logLib.c
OBJS = ${SRCS:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $<

all : $(EXE)

$(EXE) : $(OBJS)
	$(LD) -o $@ $(OBJS)

$(OBJS) : log.h

clean :
	-$(RM) -f $(EXE) $(OBJS)

