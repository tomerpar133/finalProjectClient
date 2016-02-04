/*
 * ServerListener.cpp
 *
 *  Created on: Feb 2, 2016
 *      Author: tomer
 */

#include "ServerListener.h"
#include "TCPMessengerProtocol.h"

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
		//if (!isServerSocketClosed())
		{
			usleep(300000);
			int code = ClientUtils::readCommand(this->tcpServer);
			if (code)
				this->execute(code);
		}
		/*else
		{
			this->client->disconnectFromServer();
			break;
		}*/
	}
}

void ServerListener::execute(int code)
{
	// TODO: add functionality
	string username;
	string ip;

	switch(code)
	{
		case OPEN_SESSION_WITH_PEER:
		{
			string username = ClientUtils::readData(this->tcpServer);
			this->client->passiveOpenSession(username);
			break;
		}
		case CLOSE_SESSION_WITH_PEER:
			this->client->closeSession();
			break;
		case SEND_MSG_TO_PEER:
		{
			// receive message from peer in session or from server
			string message = ClientUtils::readData(this->tcpServer);
			cout << message << endl;
	
			break;
		}
		case CLOSE_ROOM:
		{
			this->client->closeRoom();
			break;
		}
		case USER_ENTER_ROOM:
		{
			username = ClientUtils::readData(this->tcpServer);
			ip = ClientUtils::readData(this->tcpServer);
			this->client->getConferenceManager()->addUser(username, ip);
			break;
		}
		case USER_LEAVE_ROOM:
		{
			ip = ClientUtils::readData(this->tcpServer);
			this->client->getConferenceManager()->removeUser(ip);
			break;
		}
		default:
		{
			cout << "Unhandled command from server " << code << endl;
			break;
		}
	}
}

bool ServerListener::isServerSocketClosed()
{
	int n = 0;
	ioctl(this->tcpServer->getSocketFd(), FIONREAD, &n);

	return n == 0;
}
