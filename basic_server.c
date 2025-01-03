#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  // write(to_client, "b", 1);
  // char buffer[2];
  // read(from_client, buffer, sizeof(buffer));
  // printf("Buffer: %s\n", buffer);
  return 0;
}
