/*
 * Client.h
 *
 *  Created on: Feb 1, 2016
 *      Author: tomer
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "ClientUtils.h"
using namespace std;

class Client {
	TCPSocket* tcpServer;
	string status;
	bool connectedToServer;

public:
	Client();
	virtual ~Client();

	void connectToServer(string ip);

	void listUsers();

	void listConnectedUsers();

	void listRooms();

	void listRoomUsers(string room);

	void login(string username, string password);

	void registerUser(string username, string password);

	void openSession(string username);

	void openRoom(string room);

	void sendMessage(string message);

	string getStatus();

	bool isConnected();

	void closeSession();

	void disconnectFromServer();

};

#endif /* CLIENT_H_ */
