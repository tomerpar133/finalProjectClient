/*
 * ServerListener.h
 *
 *  Created on: Feb 2, 2016
 *      Author: tomer
 */

#ifndef SERVERLISTENER_H_
#define SERVERLISTENER_H_

#include <sys/ioctl.h>
#include "MThread.h"
#include "TCPSocket.h"
#include "Client.h"
#include "ClientUtils.h"

class Client;
class ServerListener : public MThread {
	TCPSocket* tcpServer;
	Client* client;

public:
	ServerListener(TCPSocket* server, Client* client);
	virtual ~ServerListener();

	void run();
	bool isServerSocketClosed();
	void execute(int code);
};

#endif /* SERVERLISTENER_H_ */
