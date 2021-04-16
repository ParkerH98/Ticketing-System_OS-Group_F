
SOBJS = parker_server_pool.o queue.o

p: pool
	clear
	./pool

pool: $(SOBJS)
	gcc parker_server_pool.o -o pool

parker_server_pool.o: parker_server_pool.c
	gcc -c parker_server_pool.c queue.c
	clear


t: thread
	clear
	./thread

thread: parker_server_threads.o
	gcc parker_server_threads.o -o thread

parker_server_threads.o: parker_server_threads.c
	gcc -c parker_server_threads.c
	clear



s: server
	clear
	./server

server: parker_server.o
	gcc parker_server.o -o server

parker_server.o: parker_server.c
	gcc -c parker_server.c
	clear

c: client
	clear
	./client

client: parker_client.o
	gcc parker_client.o -o client

parker_client.o: parker_client.c
	gcc -c parker_client.c
	clear

clean:
	rm *.o server client thread


# target: depenencies
# 	action