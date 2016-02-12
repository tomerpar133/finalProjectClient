/*
1 * UDPSocket.h
 *
 *  Created on: Feb 6, 2013
 *      Author: Eliav Menachi
 */

#ifndef UDPSOCKET_H_
#define UDPSOCKET_H_

#include <netinet/in.h>
#include <inttypes.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>
#include "TCPMessengerProtocol.h"

using namespace std;

class UDPSocket{

private:
	int socketFd;
	struct sockaddr_in myAddress;
	struct sockaddr_in senderAddress;
	socklen_t senderAddresLength ;


public:
	/**
	 * constructor: initialize a UDP socket and binds it on the given port.
	 * if no port is specified a default port 9999 is set.
	 * this UDP socket can be used both for server socket and client socket
	 */
	UDPSocket(int port = PEER_PORT);
	/**
	 * reads an incoming message from the UDP socket.
	 * the message is copied into the given buffer up to the specified length
	 */
	int recv(char* buffer, int length);
	/**
	 * sends the given message as a UDP message to the given address specified by IP and port
	 */
	int sendTo(const char* msg, size_t msgSize, string ip, int port);

	/**
	 * close the UDP socket
	 */
	void cclose();
	/**
	 * return the the current ip
	 */
	string getIp();
};

#endif /* UDPSOCKET_H_ */
