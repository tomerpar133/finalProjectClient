/*
 * Client.h
 *
 *  Created on: Feb 1, 2016
 *      Author: tomer
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#define NOT_CONNECTED			0
#define CONNECTED_TO_SERVER		1
#define CONNECTED_TO_ROOM		2
#define CONNECTED_TO_SESSION	3

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "ClientUtils.h"
#include "ServerListener.h"
using namespace std;

class Client {
	TCPSocket* tcpServer;
	string status;
	string username;
	int connectionStatus;

	// todo: add serverlistener


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

	void closeRoom();

	void deleteOldConnections();

	void printListString(string list, string description);
};

#endif /* CLIENT_H_ */
