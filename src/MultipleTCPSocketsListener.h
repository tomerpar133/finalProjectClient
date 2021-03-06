/*
 * MultipleTCPSocketsListener.h
 *
 *  Created on: Feb 14, 2013
 *      Author: efi
 */

#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <sys/time.h>
#include "TCPMessengerProtocol.h"
#include "TCPSocket.h"

using namespace std;


class MultipleTCPSocketsListener{
private:
	typedef vector<TCPSocket*> tSocketsContainer;
	tSocketsContainer sockets;

public:
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	void addSocket(TCPSocket* socket);

	/*
	 * Add the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	TCPSocket* listenToSocket();

private:
	/**
	 * This method returns the biggest fd in the vector or 0 if not found
	 */
	int findBiggestFd(fd_set* readFd);
};


#endif /* MULTIPLETCPSOCKETSLISTENER_H_ */
