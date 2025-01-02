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
  printf("Server created WKP\n");
  if (p1 < 0){
    perror("Pipe creation failed");
    exit(1);
  }
  printf("Server waiting for WKP connection\n");
  from_client = open("WKP", O_RDONLY);
  if (from_client < 0){
    perror("Failed to open pipe");
  }
  printf("Server removing WKP\n");
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
  char ppName[256];
  read(wkp, ppName, sizeof(ppName));
  printf("Server read SYN: %s\n", ppName);
  *to_client = open(ppName, O_WRONLY);
  printf("Server opened PP\n");
  if (*to_client < 0){
    perror("Failed to open PP");
    exit(1);
  }
  srand(getpid());
  int ran = rand();
  char synAck[256];
  sprintf(synAck, "%d", ran);
  write(*to_client,synAck,sizeof(synAck));
  printf("Server writing %d to client\n", ran);
  from_client = open(ppName, O_RDONLY);
  if (from_client < 0){
    perror("Failed to open PP");
    exit(1);
  }
  char temp[256];
  read(from_client, temp, sizeof(temp));
  int msg = atoi(temp);
  printf("Server reading %d from client\n", msg);
  close(from_client);
  return *to_client;
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
  int pp;
  char ppName[256];
  sprintf(ppName, "%d", getpid());
  pp = mkfifo(ppName, 0600);
  printf("Client created PP\n");
  if (pp < 0){
    perror("Pipe creation failed");
    exit(1);
  }
  int wkp = open("WKP", O_WRONLY);
  printf("Client opened WKP\n");
  if (wkp < 0){
    perror("Failed to open WKP");
    exit(1);
  }
  write(wkp, ppName, sizeof(ppName));
  close(wkp);
  printf("Client waiting for PP connection\n");
  from_server = open(ppName, O_RDONLY);
  if (from_server < 0){
    perror("Failed to open PP");
    exit(1);
  }
  char temp[256];
  read(from_server,temp,sizeof(temp));
  int msg = atoi(temp);
  printf("Client reading %d from server\n", msg);
  int updatedMsg = msg+1;
  sprintf(temp, "%d", updatedMsg);
  close(from_server);
  *to_server = open(ppName, O_WRONLY);
  if (*to_server < 0){
    perror("Failed to open PP");
    exit(1);
  }
  printf("Client sending %s to server\n", temp);
  write(*to_server, temp, sizeof(temp));
  return *to_server;
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
