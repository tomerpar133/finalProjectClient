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
using namespace std;

class Client {
public:
	Client();
	virtual ~Client();

	void connectToServer(string ip);

	vector<string> listUsers();

	vector<string> listConnectedUsers();

	vector<string> listRooms();

	vector<string> listRoomUsers(string room);

	void login(string username, string password);

	void registerUser(string username, string password);

	void openSession(string username);

	void openRoom(string room);

	void sendMessage(string message);

	void status();

	void closeSession();

	void disconnectFromServer();

};

#endif /* CLIENT_H_ */
