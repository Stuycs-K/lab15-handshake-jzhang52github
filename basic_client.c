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
  // char buffer[2];
  // error = read(from_server, buffer, sizeof(buffer));
  // if (error < 0){
  //   perror("Read from server failed");
  //   exit(1);
  // }
  // buffer[error] = '\0';
  // printf("From server: %s\n", buffer);
  return 0;
}
