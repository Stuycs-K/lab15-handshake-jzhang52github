#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  write(to_server, "a", 1);
  char buffer[2];
  read(from_server, buffer, sizeof(buffer));
  printf("Buffer: %s\n", buffer);
  return 0;
}
