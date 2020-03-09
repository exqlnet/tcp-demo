#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <winsock2.h>
#include <windows.h>
#define MAXLINE 4096



LPSTR ConvertErrorCodeToString(DWORD ErrorCode)  
{  
	HLOCAL LocalAddress=NULL;  
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,ErrorCode,0,(PTSTR)&LocalAddress,0,NULL);  
	return (LPSTR)LocalAddress;  
}

void printErrorMsg() {
  DWORD dw = GetLastError();
  printf("error(%d): %s\n", dw, ConvertErrorCodeToString(dw));
}


int main(int argc, char** argv) {
  int n;
  SOCKET sockfd = INVALID_SOCKET;
  char recvline[MAXLINE], sendline[MAXLINE];
  sockaddr_in servaddr;
  DWORD dw = GetLastError();


  WORD sockVersion = MAKEWORD(2,2);  
  WSADATA wsaData;  
  if(WSAStartup(sockVersion, &wsaData)!=0)  
  {  
      return 0;  
  }

  

  char* remote_addr;
  if (argc != 2) {
    remote_addr = "127.0.0.1";
  } else {
    remote_addr = argv[1];
  }

  if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
    printErrorMsg();
    return 0;
  }
  dw = GetLastError();

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(6666);
  servaddr.sin_addr.S_un.S_addr = inet_addr(remote_addr);
  
  printf("connecting to %s ...\n", remote_addr);
  if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) == SOCKET_ERROR){
    printErrorMsg();
    return 0;
  }

  printf("send msg to server: ");
  fgets(sendline, MAXLINE, stdin);

  if (send(sockfd, sendline, strlen(sendline), 0) < 0) {
    printErrorMsg();
    return 0;
  }

  printf("sended!");

  closesocket(sockfd);


  WSACleanup();

  return 0;
}