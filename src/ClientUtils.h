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

class ClientUtils {
public:
	ClientUtils();
	virtual ~ClientUtils();
	static int readCommandFromPeer(TCPSocket* peer);

	/**
	 * read data from peer
	 */
	static string readDataFromPeer(TCPSocket* peer);

	/**
	 * send command to peer
	 */
	static void sendCommandToPeer(TCPSocket* peer, int command);

	/**
	 * send data to peer
	 */
	static void sendDataToPeer(TCPSocket* peer, string msg);

	/**
	 * read udp data from peer
	 */
	static string readDataFromPeer(UDPSocket* peer);

	/**
	 * send udp data to peer
	 */
	static void sendDataToPeer(UDPSocket* peer, string msg);

};

#endif /* CLIENTUTILS_H_ */
