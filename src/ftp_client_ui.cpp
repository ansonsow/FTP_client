/**
 *  @file: ftp_client_ui.hpp
 *  @author: Anson Su, 578677684, F20N03,  CSCI 460, VIU
 *  @version: 1.0.0
 *  @modified: Sep 25 2020
 *
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "../include/ftp_client_ui.hpp"
#include "../include/ftp_client_command.hpp"
void getUserCommand(){
// Displays a command line prompt as follows:
//      CSCI460FTP>>
// Lets user to type command and reads the user command from the prompt.
// Interprets and handles user command by calling function interpreteAndHandleUserCommand().
  printf("  CSCI460FTP>>");
  char str[512];
  scanf("%s",str);
  interpretAndHandleUserCommand(str);
}
void interpretAndHandleUserCommand(std::string command){
// Interprets and handles user command
// Calls appropriate handleCommandXXXX() function from 'ftp_client_command.hpp'.
// Displays all FTP server responses calling showFtpResponse() function.
  std::string c[65536];
  int i=0;
  if(command == FTP_CLIENT_USER_COMMAND_HELP){
    handleCommandHelp();

  }else if(command == FTP_CLIENT_USER_COMMAND_USER){
    char user[512];
    scanf("%s",user);
    handleCommandUser(user,c,i);
    showFtpResponse(c[0]);

  }else if(command == FTP_CLIENT_USER_COMMAND_PASSWORD){
    char pass[512];
    scanf("%s",pass);
    handleCommandPassword(pass,c,i);
    showFtpResponse(c[0]);

  }else if(command == FTP_CLIENT_USER_COMMAND_PRINT_DIRECTORY){
    handleCommandPrintDirectory(c,i);
    showFtpResponse(c[0]);

  }else if(command == FTP_CLIENT_USER_COMMAND_DIRECTORY){
    handleCommandDirectory(c,i);
    showFtpResponse(c[0]);

    
  }else if(command == FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY){
    char dir[512];
    scanf("%s",dir);
    handleCommandChangeDirectory(dir,c,i);
    showFtpResponse(c[0]);

  }else if(command == FTP_CLIENT_USER_COMMAND_CHANGE_DIRECTORY_UP){
    handleCommandChangeDirectoryUp(c,i);
    showFtpResponse(c[0]);

  }else if(command == FTP_CLIENT_USER_COMMAND_GET){
    char file[512];
    scanf("%s",file);
    handleCommandGetFile(file,c,i);
    showFtpResponse(c[0]);

  }else if(command == FTP_CLIENT_USER_COMMAND_QUIT){
    handleCommandQuit(c,i);
    showFtpResponse(c[0]);
    exit(0);
  }
}
void showFtpResponse(std::string response){
// Displays server response to the user.
// For example, success response of user command
//      CSCI460FTP>>user csci460
// should be displayes as
//      331 Username okay, need password.
//
// Success response of user command
//      CSCI460FTP>>dir
// should be  displayed as
//      226 Directory listing (11) entries. Closing data connection.
//
//      D       .
//      D       ..
//      D       bin
//      F       makefile                2631
//      D       include
//      F       README                  0
//      D       build
//      D       resource
//      D       src
  std::cout << response << endl;
}
