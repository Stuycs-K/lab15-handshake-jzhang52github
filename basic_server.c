#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  write(to_client, "b", 1);
  char buffer[2];
  buffer[2] = '\0';
  int error;
  while (1) {
      error = read(from_client, buffer, sizeof(buffer));
      if (error < 0) {
          perror("Read from client failed");
          exit(1);
      }
      printf("From client: %s\n", buffer);
    }
  return 0;
}
