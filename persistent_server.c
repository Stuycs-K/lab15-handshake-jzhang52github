#include "pipe_networking.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>

static void sighandler(int signo){
  if (signo == SIGINT){
    remove("WKP");
    printf("Server removed WKP\n");
    printf("Server exiting due to SIGINT\n");
    exit(0);
  }
}

int main() {
  while (1){
    signal(SIGINT, sighandler);

    int to_client;
    int from_client;
    char buffer[256];
    buffer[256] = '\0';

    from_client = server_handshake( &to_client );

    while(read(from_client, buffer, sizeof(buffer)) > 0){
      printf("From client: %s\n", buffer);
    }

    close(to_client);
    close(from_client);
  }
  return 0;
}
