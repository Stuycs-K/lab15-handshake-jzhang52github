#include "pipe_networking.h"

int main() {
  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  int error = write(to_server, "a", 1);
  if (error < 0){
    perror("Write to server failed");
    exit(1);
  }
  printf("To server: a\n");
  return 0;
}
