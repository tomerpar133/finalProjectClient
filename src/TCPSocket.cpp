/*
 * TCPSocket.cpp
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#include <iostream>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include "TCPSocket.h"
using namespace std;

TCPSocket::TCPSocket(int connected_sock,struct sockaddr_in serverAddr,struct sockaddr_in peerAddr){
	//TODO: initialize local class properties;
	socketFd = connected_sock;
	myAddress = serverAddr;
	peerAddress = peerAddr;
}


TCPSocket::TCPSocket(int port){
	//TODO: open TCP socket
	socketFd = socket(AF_INET, SOCK_STREAM, 0);

	if (socketFd < 0)
	{
		perror("Error creating socket myAddress");
	}

	//TODO: set the server address for binding
	bzero(&myAddress, sizeof(myAddress));
	myAddress.sin_family = AF_INET;
	myAddress.sin_port = htons(port);

	//TODO: bind the socket to the address
	if (bind(socketFd, (struct sockaddr*)&myAddress, sizeof(myAddress)) < 0)
	{
		perror("Error binding myAddress");
	}
}


TCPSocket::TCPSocket(string peerIp, int port){
	//TODO: open TCP socket
	socketFd = socket(AF_INET, SOCK_STREAM, 0);

	if (socketFd < 0)
	{
		perror("Error creating socket peer");
		close(socketFd);
	}

	//TODO: set the peer address to connect to
	bzero(&peerAddress, sizeof(peerAddress));
	peerAddress.sin_family = AF_INET;
	peerAddress.sin_port = htons(port);
	peerAddress.sin_addr.s_addr = inet_addr(peerIp.data());

	//TODO: connect the socket to the peer server
	if (connect(socketFd, (struct sockaddr*)&peerAddress, sizeof(peerAddress)) < 0)
	{
		perror("Error binding peer");
		close(socketFd);
	}
}


TCPSocket* TCPSocket::listenAndAccept(){
	//TODO: listen on the socket
	listen(socketFd, 1);

	//TODO: call accept on the socket
	socklen_t size = sizeof(peerAddress);
	int acceptFd = accept(socketFd, (struct sockaddr*)&peerAddress,&size);

	//TODO: return new TCPSocket object holding the new secondary server socket returned from the accept call

	return new TCPSocket(acceptFd, myAddress, peerAddress);
}


int TCPSocket::recv(char* buffer, int length){
	//TODO: read from the socket

	return read(socketFd, buffer, length);
}


int TCPSocket::send(const char* msg, int len){
	//TODO: write on the socket

	return write(socketFd, msg, len);
}


void TCPSocket::cclose(){
	//TODO: shutdown and close the socket
	shutdown(socketFd, SHUT_RDWR);
	close(socketFd);
}

string TCPSocket::getClientAsString()
{
	char port[30];
	sprintf(port, "%u", htons(this->peerAddress.sin_port));
	return this->fromAddr() + ":" + port;
}

string TCPSocket::fromAddr(){
	//TODO: return the session destination peer address

	return inet_ntoa(peerAddress.sin_addr);
}
