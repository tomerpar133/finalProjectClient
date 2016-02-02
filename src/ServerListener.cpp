/*
 * ServerListener.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: tomer
 */

#include "ServerListener.h"

ServerListener::ServerListener(TCPSocket* server, Client* client) {
	this->tcpServer = server;
	this->client = client;
}

ServerListener::~ServerListener() {

}

void ServerListener::run()
{
	while (true)
	{
		if (!isServerSocketClosed())
		{
			int code = ClientUtils::readCommand(this->tcpServer);
			this->execute(code);
		}
		else
		{
			this->client->disconnectFromServer();
			break;
		}
	}
}

void ServerListener::execute(int code)
{
	// TODO: add functionality
	switch(code)
	{
		case OPEN_SESSION_WITH_PEER:
	
			break;
	
		case SEND_MSG_TO_PEER:
	
			break;
	
		case CLOSE_ROOM:
	
			break;
		case USER_ENTER_ROOM:
			
			break;
		case USER_LEAVE_ROOM:
			
			break;
		default:
			break;
	}
}

bool ServerListener::isServerSocketClosed()
{
	int n = 0;
	ioctl(this->tcpServer->getSocketFd(), FIONREAD, &n);

	return n == 0;
}
