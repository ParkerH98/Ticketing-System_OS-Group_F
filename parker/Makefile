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
	rm *.o server client


# target: depenencies
# 	action