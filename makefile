.PHONY: clean run compile

server: server
	@./server

client: client
	@./client

compile: persistent_server.o basic_client.o
	@gcc -o server persistent_server.o -lm
	@gcc -o client basic_client.o -lm

persistent_server.o: persistent_server.c pipe_networking.h
	@gcc -c persistent_server.c pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c pipe_networking.o

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
