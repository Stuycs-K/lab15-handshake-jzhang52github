#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  int error = write(to_client, "b", 1);
  if (error < 0) {
    perror("Write to client failed");
    exit(1);
  }
  printf("To client: b\n");
  char buffer[2];
  error = read(from_client, buffer, sizeof(buffer));
  if (error < 0) {
    perror("Read from client failed");
    exit(1);
  }
  buffer[error] = '\0';
  printf("From client: %s\n", buffer);
  return 0;
}
