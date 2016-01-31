/*
 * MessengerClient.h
 *
 *  Created on: Jan 31, 2016
 *      Author: tomer
 */

#ifndef MESSENGERCLIENT_H_
#define MESSENGERCLIENT_H_

#include <string>
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "TCPMessengerProtocol.h"

class MessengerClient {
public:
	MessengerClient();
	virtual ~MessengerClient();
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

#endif /* MESSENGERCLIENT_H_ */
