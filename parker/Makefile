#==========================
#		Constants
#==========================
CC = gcc
CFLAGS = -Wall
SOBJS = parker_server.o queue.o
COBJS = parker_client.o
EXECS = s c
HEADER = ../header.h


#==========================
#		Client
#==========================
obj/parker_client.o: parker_client.c $(HEADER)  # step 2
	$(CC) $(CFLAGS) -c parker_client.c

c: $(COBJS) # step 1
	$(CC) $(CFLAGS) -o c $(COBJS)
	


#==========================
#		Server
#==========================
obj/parker_server.o: parker_server.c $(HEADER)  # step 3
	$(CC) $(CFLAGS) -c parker_server.c

obj/queue.o: queue.c # step 2
	$(CC) $(CFLAGS) -c queue.c

s: $(SOBJS) # step 1
	$(CC) $(CFLAGS) -o s $(SOBJS) 
	clear


#==========================
#		Utilities
#==========================
clean:
	rm *.o $(EXECS)
