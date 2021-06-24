/**
 * @file: ftp_client_connection.cpp
 * @author: Anson Su, 578677684, F20N03, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: Sep 22, 2020
 *
 */
//#include "../include/ftp_client_ui.hpp"
//#include "../include/ftp_client_connection.hpp"
//#include "../include/ftp_client_control.hpp"
#include "../include/ftp_client_connection.hpp"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string>
using namespace std;

void connectToServer(int& socketDescriptor, bool& isConnected, const char* serverIP, int serverPort){
// Sends a connection request on severPort of a sever whose IP address is equal to serverIP.
// If a connection has been established as a result of the request sets the connection descriptor value
// to reference 'socketDescriptor' and sets reference 'isConnected' to 'true'.
  struct addrinfo server, *res;
  memset(&server, 0 ,sizeof server);
  server.ai_family = AF_UNSPEC;
  server.ai_socktype = SOCK_STREAM;
  //  int sock = socketDescriptor;
  //memset(&server, 0 sizeof server);
  string port = to_string(serverPort);
  char const* cport = port.c_str();
  getaddrinfo(serverIP, cport, &server, &res);
  
  printf("start socket\n");
  int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if(sock == -1){
    printf("bad socket\n");
    exit(0);
  }else{
    printf("good socket\n");
    socketDescriptor = sock;
  }
  

  printf("start connect\n");
  int connection = connect(socketDescriptor , res->ai_addr  ,res->ai_addrlen);
  //int connection = connect(socketDescriptor , serverIP  ,res->ai_addrlen);
  
  if(connection == -1){
    isConnected = 0;
    printf("bad connection\n");
  }else{
    printf("good connection\n");
    isConnected = 1;
  }
}

void disconnectFromServer(int& socketDescriptor, bool& isConnected){
// Closes network connection represented by reference 'socketDescriptor' and
// sets reference 'isConnected' to 'false'.
  printf("start disconnect\n");
  int c = close(socketDescriptor);
  if(c == 0){
    printf("good disconnect\n");
    isConnected = 0;
  }else{
    printf("bad disconnect\n");
    //exit(0);
  }
}

int sendToServer(int sockDescriptor, const char* message, int messageLength){
// Sends 'message' of length 'messageLength' bytes to the server
// on the network connection represented by 'sockDescriptor'.
  printf("start send\n");
  int s = send(sockDescriptor, message , messageLength, 0);
  if(s == -1){
    printf("cannot send\n");
    exit(0);
  }else{
    printf("good send\n");
  }
  //return send(sockDescriptor, message , messageLength, 0);
  return s;
}

int receiveFromServer(int sockDescriptor, char* message, int messageLength){
// Receives 'message' of length 'messageLength' bytes from the server
// on the network connection represented by 'sockDescriptor'.
  // return recv(sockDescriptor, message , messageLength,0);
  printf("receive start\n");
  int r = recv(sockDescriptor, message , messageLength, 0);
  if(r == -1){
    printf("cannot receive\n");
    exit(0);
  }else{
    printf("good receive\n");
  }
  //return send(sockDescriptor, message , messageLength, 0);
  return r;

}
