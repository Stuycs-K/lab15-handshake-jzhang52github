#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  int p1 = mkfifo("WKP", 0600);
  if (p1 < 0){
    perror("Pipe creation failed");
    exit(1);
  }
  from_client = open("WKP", O_RDONLY);
  if (from_client < 0){
    perror("Failed to open pipe");
  }
  remove("WKP");
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  int wkp = server_setup();
  read(wkp, from_client, sizeof(int));
  int pp = open("PP", O_WRONLY);
  if (pp < 0){
    perror("Failed to open PP");
    exit(1);
  }
  srand(getpid());
  int synAck = rand();
  write(pp,synAck,sizeof(int));
  close(pp);
  pp = open("PP", O_RDONLY);
  if (pp < 0){
    perror("Failed to open PP");
    exit(1);
  }
  read(pp, from_client, sizeof(int));
  close(pp);
  remove("PP");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  int p1 = mkfifo("PP", 0600);
  if (p1 < 0){
    perror("Pipe creation failed");
    exit(1);
  }
  int wkp = open("WKP", O_WRONLY);
  if (wkp < 0){
    perror("Failed to open WKP");
    exit(1);
  }
  write(wkp, p1, sizeof(int));
  close(wkp);
  int pp = open("PP", O_RDONLY);
  if (pp < 0){
    perror("Failed to open PP");
    exit(1);
  }
  read(pp,from_server,sizeof(int));
  from_server++;
  close(pp);
  pp = open("PP", O_WRONLY);
  if (pp < 0){
    perror("Failed to open PP");
    exit(1);
  }
  write(pp, from_server, sizeof(int));
  close(pp);
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client;
  return to_client;
}
