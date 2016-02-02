/*
 * UDPSocket.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: Eliav Menachi
 */

#include "UDPSocket.h"
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

UDPSocket::UDPSocket(int port){
	// create a UDP socket
    socketFd = socket(AF_INET, SOCK_DGRAM, 0);

	// Create an address for the socket
	bzero((char*)&myAddress, sizeof(myAddress));
	myAddress.sin_family = (short)AF_INET;
	myAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	myAddress.sin_port = htons(port);
	senderAddresLength = sizeof(senderAddress);

	if (bind(socketFd, (struct sockaddr*)&myAddress, sizeof(myAddress)) < 0)
	{
		perror("unable to bind");
	}
}

int UDPSocket::recv(char* buffer, int length){
	// call receive from on the socket and save the address of the sender for the reply method

	return recvfrom(socketFd,
				    buffer,
					length,
					0,
					(struct sockaddr *) &senderAddress,
					&senderAddresLength);
}

int UDPSocket::sendTo(string msg, string ip, int port){
	// create an address struct for the destination
	bzero((char*)&senderAddress, sizeof(senderAddress));
	senderAddress.sin_family = (short)AF_INET;
	senderAddress.sin_port = htons(port);


	// call send to and sent the message to the destination address
	return sendto(socketFd,
				  msg.data(),
				  msg.length(),
				  0,
				  (struct sockaddr*)&senderAddress,
				  sizeof(senderAddress));
}

void UDPSocket::cclose(){
	// shutdown and close the socket
	shutdown(socketFd, SHUT_RDWR);
	close(socketFd);
}

string UDPSocket::getIp(){
	// return the IP address of the last received message as a string
	return inet_ntoa(myAddress.sin_addr);
}



