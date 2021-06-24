/**
 * @file: ftp_client_control.cpp
 * @author: Anson Su, 578677684,F20N03 , CSCI 460, VIU
 * @version: 1.0.0
 * @modified: Sep 24 2020
 *
 */

/*#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>*/
//#include "../include/ftp_client_command.hpp"
//#include "../include/ftp_client_ui.hpp"
#include "../include/ftp_client_connection.hpp"
#include "../include/ftp_client_control.hpp"
//#include "ftp_client_connection.cpp"
int controlSocket = -1;
//-- Represents control connection to the server
int dataSocket = -1;
//-- Represents data connection to the server
bool isControlConnected = false;
//-- Represents the status of the control connection
bool isDataConnected = false;
//-- Represents the status of the data connection

void connectToServerControl(const char* serverIP, int serverPort){
  connectToServer(controlSocket, isControlConnected, serverIP, serverPort);
}

void connectToServerData(const char* serverIP, int serverPort){
  connectToServer(dataSocket, isDataConnected, serverIP, serverPort);
}

int sendOnControl(const char* buffer, int length){
  return sendToServer(controlSocket, buffer, length);
}

int sendOnData(const char* buffer, int length){
  return sendToServer(dataSocket, buffer, length);
}

int receiveOnControl(char* buffer, int length){
  return receiveFromServer(controlSocket, buffer, length);
}

int receiveOnData(char* buffer, int length){
  return receiveFromServer(dataSocket, buffer, length);
}

void disconnectControlConnection(){
  disconnectFromServer(controlSocket, isControlConnected);
}

void disconnectDataConnection(){
  disconnectFromServer(dataSocket, isDataConnected);
}

bool isControlConnectionAvailable(){
  return isControlConnected;
}

bool isDataConnectionAvailable(){
  return isDataConnected;
}
