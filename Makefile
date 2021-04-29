#==========================
#		Constants
#==========================
CC = gcc
CFLAGS = -Wall
SOBJS = driver_server.o
COBJS = driver_client.o
EXECS = s c
HEADER = header.h


#==========================
#		Client
#==========================
driver_client.o: driver_client.c $(HEADER)  # step 2
	$(CC) $(CFLAGS) -c driver_client.c

c: $(COBJS) # step 1
	$(CC) $(CFLAGS) -o c $(COBJS)
	


#==========================
#		Server
#==========================
driver_server.o: driver_server.c $(HEADER)  # step 3
	$(CC) $(CFLAGS) -c driver_server.c
	


#queue.o: queue.c # step 2
#	$(CC) $(CFLAGS) -c queue.c

s: $(SOBJS) # step 1
	$(CC) $(CFLAGS) -o s $(SOBJS) 
	


#==========================
#		Utilities
#==========================
clean:
	rm *.o $(EXECS) *.txt
