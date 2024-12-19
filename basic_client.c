#include "pipe_networking.h"

int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );
  printf("From server: %d\n", from_server);
  return 0;
}
