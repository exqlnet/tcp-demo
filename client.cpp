#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define MAXLINE 4096

int main(int argc, char** argv) {
  int sockfd, n;
  char recvline[MAXLINE], sendline[MAXLINE];
  sockaddr_in servaddr;

  char* remote_addr;
  if (argc != 2) {
    remote_addr = "127.0.0.1";
  } else {
    remote_addr = argv[1];
  }

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      printf("create socket error error: %s(errno: %d)\n", strerror(errno), errno);
  }

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);

  if (inet_pton(AF_INET, remote_addr, &servaddr.sin_addr) <= 0) {
    printf("inet_pton error for %s\n", remote_addr);
    return 0;
  }

  if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0){
      printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
      return 0;
  }

  printf("send msg to server: ");
  fgets(sendline, MAXLINE, stdin);

  if (send(sockfd, sendline, strlen(sendline), 0) < 0) {
      printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
      return 0;
  }

  close(sockfd);



  return 0;
}