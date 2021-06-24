/**
 * @file: ftp_client_command.cpp
 * @author: Name, Student Number, Section, CSCI 460, VIU
 * @version: 1.0.0
 * @modified: June 24, 2020
 *
 */
#include"../include/ftp_client_control.hpp"
#include"../include/ftp_client_ui.hpp"
#include"../include/ftp_server_response.hpp"
#include"../include/ftp_client_command.hpp"
#include <stdlib.h>
#include <string.h>
//#include <iostream>
//#include <string>
const int DATA_SOCKET_RECEIVE_BUFFER_SIZE=65536;
using namespace std;


void handleCommandHelp(){
// Displays following help text on the user terminal
  printf("Usage: csci460Ftp>> [ help | user | pass | pwd | dir | cwd | cdup | get | quit ] \n");
  printf("        help                    Gives the list of FTP commands available and how to use them. \n");
  printf("        user    <username>      Sumbits the <username> to FTP server for authentication. \n");
  printf("        pass    <password>      Sumbits the <password> to FTP server for authentication. \n");
  printf("        pwd                     Requests FTP server to print current directory. \n");
  printf("        dir                     Requests FTP server to list the entries of the current directory. \n");
  printf("        cwd     <dirname>       Requests FTP server to change current working directory. \n");
  printf("        cdup                    Requests FTP server to change current directory to parent directory. \n");
  printf("        get     <filename>      Requests FTP server to send the file with <filename>. \n");
  printf("        quit                    Requests to end FTP session and quit. \n");
}


void handleCommandUser(string username, string serverResponses[], int& serverResponseCount){
  // Sends a 'USER <username>' request meesage to the FTP Server.
  string user = "USER " + username;
  // Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter value "true"
  handleSimpleCommand(user,true,serverResponses,serverResponseCount);
}



void handleCommandPassword(string password, string serverResponses[], int& serverResponseCount){
  // Sends a 'PASS <password>' request message to the FTP Server.
  string pass = "PASS " + password;
  // Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter "true"
  handleSimpleCommand(pass,true,serverResponses,serverResponseCount);
}

void handleCommandDirectory(string serverResponses[], int& serverResponseCount){
// Calls handlePassive() function to do the followings:
//      -send a 'PASV' request message to the FTP server.
//      -receive the response against PASV request message from the server.
//      -update 'serverResponses' and 'serverResponseCount' parameters based on PASV responses.
//      -retrieve data-connection listener port number from the successful response.
//      -requests a data connection to the server at the listener port at the server.
  handlePassive(serverResponses,serverResponseCount);
// If the data connection is successful, calls handleNLIST() function to do the followings:
//      -send a 'NLST' request message to the server on the control connection.
//      -receive the response against NLST request from the server on the control connection.
//      -retrieve the list of entries of the current directory at the server on the data connection from the successful response..
//      -update 'serverResponses' and 'serverResponseCount' parameters based on NLST responses.
}

void handleCommandPrintDirectory(string serverResponses[], int& serverResponseCount){
  // Sends a 'PWD' request message to FTP Server.
  string pwd = "PWD";
  // Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter "false"
  handleSimpleCommand(pwd,false,serverResponses,serverResponseCount);
}


void handleCommandChangeDirectory(string path, string serverResponses[], int& serverResponseCount){
  // Sends a 'CWD <path>' request message to the FTP Server.
  string cwd = "CWD " + path;
  // Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter "false"
  handleSimpleCommand(cwd,false,serverResponses,serverResponseCount);
}


void handleCommandChangeDirectoryUp(string serverResponses[], int& serverResponseCount){
  // Sends a 'CDUP' request message to FTP Server.
  string cdup = "CDUP";
  // Calls function handleSimpleCommandResponse() with "checkAuthentication" parameter "false"
  handleSimpleCommand(cdup,false,serverResponses,serverResponseCount);
}

void handleCommandGetFile(string filename, string serverResponses[], int& serverResponseCount){
// Calls handlePassive() function to do the followings:
//      -send a 'PASV' request message to the FTP server.
//      -receive the response against PASV request message from the server.
//      -update 'serverResponses' and 'serverResponseCount' parameters based on PASV responses.
//      -retrieve data-connection listener port number from the successful response.
//      -requests a data connection to the server at the listener port at the server.
 handlePassive(serverResponses,serverResponseCount);
// If the data connection is successful, calls handleRETR() function to do the followings:
//      -send a 'RETR <filename>' request message to the server on the control connection.
//      -receive the response against RETR request from the server on the control connection.
//      -retrieve the content of the file on the data connection from the successful response.
//      -save the content of the file with <filename> at local folder.
//      -update 'serverResponses' and 'serverResponseCount' parameters based on RETR responses.
}



void handleCommandQuit(string serverResponses[], int& serverResponseCount){
  // Sends a 'QUIT' request message to FTP Server.
  string squit = "QUIT";
  // Returns server responses and response count through 'serverResponses' and 'serverResponseCount' parameters respectively.
  handleSimpleCommand(squit,false,serverResponses,serverResponseCount);
}




void handlePassive( string serverResponses[], int& serverResponseCount){
// Sends a 'PASV' request message to the FTP server.
// Receives the response against PASV request message from the server.
// Updates 'serverResponses' and 'serverResponseCount' parameters based on PASV responses.
  sendOnControl("PASV", 4);
  char buffer[DATA_SOCKET_RECEIVE_BUFFER_SIZE];
  receiveOnControl(buffer, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
  string sbuffer = {buffer};
  serverResponses = &sbuffer;
  serverResponseCount = 1;
  int intbuffer = atoi(buffer);
  
// If the response is a successful one, retrives data-connection listener port number form the response.
  if(intbuffer<400){
    // Retrives data-connection listener port number form the response
    // using function getHostIPAndPortFromPassiveSuccessResponse().
    char hostIP[100];
    int hostPort;
    getHostIPAndPortFromPassiveSuccessResponse(buffer,hostIP,hostPort);
    // Requests a data connection to the server on the listener port at the server.
    connectToServerData(hostIP, hostPort);
  }
}




void handleNLIST(string serverResponses[], int& serverResponseCount){
// Sends a 'NLST' request message to the server on the control connection.
// Receives the response against NLST request from the server on the control connection.
// Updates 'serverResponses' and 'serverResponseCount' parameters based on NLST responses.
  string nlst= "NLST";
  sendOnControl(nlst.c_str(),nlst.length());
  char buffer[DATA_SOCKET_RECEIVE_BUFFER_SIZE];
  receiveOnControl(buffer, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
  string sbuffer = {buffer};
  serverResponses = &sbuffer;
  serverResponseCount = 1;
  int intbuffer = atoi(buffer);
  
// If the response is successful, retrieves the list of entries in server's current directory
// on the data connection.
// Adds the list of directory entries to 'serverResponses' and updates 'serverResponseCount'.

  if(intbuffer >=400){
    
  }

}

void handleSimpleCommand(string ftpCommand, bool checkAuthentication, string serverResponses[], int& serverResponseCount){
// Sends 'ftpCommand' request message to FTP server on the control connection.
// Receives the response from the server against the request.
// Returns server responses and response count through 'serverResponses' and 'serverResponseCount' parameters respectively.
  
  sendOnControl(ftpCommand.c_str(),ftpCommand.length());
  char buffer[DATA_SOCKET_RECEIVE_BUFFER_SIZE];
  receiveOnControl(buffer, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
  string sbuffer = {buffer};
  serverResponses = &sbuffer;
  serverResponseCount = 1;
  int intbuffer = atoi(buffer);

  // If the response is unsuccessful and checkAuthentication parameter value is true, quits the application.

  if(intbuffer >=400 && checkAuthentication == true){
    handleCommandQuit(serverResponses,serverResponseCount);
  }
}

void getHostIPAndPortFromPassiveSuccessResponse(char* response, char* hostIP, int& hostPort){
// Retrieves IP address of FTP Server from the response string into reference 'hostIP'.
// Retrives data-connection listening port number of FTP server from the response string into reference 'hostPort'.
// The example of a successful response message is "227 Entering Passive Mode (192,168,1,65,202,143)."
// From the above response message 'hostIP' will be 192.168.1.65 and 'hostPort'will be (202x256 + 143) or 51855.
// (202x256 + 143) or 51855.
  char* token;
  const char d[] = "(,.)";
  
  token = strtok (response, d);
  //token is 227 Entering passive mode
  string ip;
  token = strtok(NULL,d);
  //token is 192
  ip=token;
  for(int i=0;i<=2;i++){
    token = strtok(NULL, d);
    //token is 168&1&65
    ip=ip+"."+token;
  }
  strcpy(hostIP,ip.c_str());

  char*a;
  token = strtok(NULL,d);
  //token is 202
  a=token;
  char*b;
  token = strtok(NULL,d);
  //token is 143
  b=token;
  hostPort = atoi(a)*256 + atoi(b);

}
void handleRETR(string filename, string serverResponses[], int& serverResponseCount){
// Sends a 'RETR <filename>' request message to the server on the control connection.
// Receives the response against RETR request from the server on the control connection.
// Updates 'serverResponses' and 'serverResponseCount' parameters based on RETR responses.
// If the response is successful, retrieves the content of the file on the data connection.
// Saves the file in the local directory at the client computer.
  string retr = "RETR " + filename;
  sendOnControl(retr.c_str(),retr.length());
  char buffer[DATA_SOCKET_RECEIVE_BUFFER_SIZE];
  receiveOnControl(buffer, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
  string sbuffer = {buffer};
  serverResponses = &sbuffer;
  serverResponseCount = 1;
  int intbuffer = atoi(buffer);
  if(intbuffer < 400){
    receiveOnData(buffer, DATA_SOCKET_RECEIVE_BUFFER_SIZE);
  }
  }
