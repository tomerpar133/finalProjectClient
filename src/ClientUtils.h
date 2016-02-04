/*
 * MessengerClient.h
 *
 *  Created on: Jan 31, 2016
 *      Author: tomer
 */

#ifndef CLIENTUTILS_H_
#define CLIENTUTILS_H_

#include <string>
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "TCPMessengerProtocol.h"

static pthread_mutex_t lock;

class ClientUtils {
public:
	ClientUtils();
	virtual ~ClientUtils();
	static int readCommand(TCPSocket* peer);

	/**
	 * read data from peer
	 */
	static string readData(TCPSocket* peer);

	/**
	 * send command to peer
	 */
	static void sendCommand(TCPSocket* peer, int command);

	/**
	 * send data to peer
	 */
	static void sendData(TCPSocket* peer, string msg);

	/**
	 * read udp data from peer
	 */
	static string readData(UDPSocket* peer);

	/**
	 * send udp data to peer
	 */
	static void sendData(UDPSocket* sender, string peerIp, string msg);
	
	static bool repliedSuccess(TCPSocket* socket);

};

#endif /* CLIENTUTILS_H_ */
