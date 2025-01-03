#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  write(to_server, "a", 1);
  char buffer[2];
  buffer[2] = '\0';
  int error;
  error = read(from_server, buffer, sizeof(buffer));
  if (error < 0){
    perror("Read from server failed");
    exit(1);
  }
  printf("From server: %s\n", buffer);
  return 0;
}
