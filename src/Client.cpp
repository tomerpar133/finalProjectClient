/*
 * Client.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: tomer
 */

#include "Client.h"

Client::Client() {
	this->status = "not connected";
	this->tcpServer = NULL;
	this->username = "";
	this->connectionStatus = NOT_CONNECTED;
}

Client::~Client() {
	// TODO Auto-generated destructor stub
	delete this->tcpServer;
}

void Client::connectToServer(string ip)
{
	cout << "connecting to server in ip " << ip << endl;
	this->tcpServer = new TCPSocket(ip, MSNGR_PORT);
	this->connectionStatus = CONNECTED_TO_SERVER;
}

void Client::listUsers()
{
	ClientUtils::sendCommand(this->tcpServer, LIST_USERS);
	string usersList = ClientUtils::readData(this->tcpServer);
	printListString(usersList, "user list");
}

void Client::listConnectedUsers()
{
	ClientUtils::sendCommand(this->tcpServer, LIST_CONNECTED_USERS);
	string connectedUsersList = ClientUtils::readData(this->tcpServer);
	printListString(connectedUsersList, "connected users list");
}

void Client::listRooms()
{
	ClientUtils::sendCommand(this->tcpServer, LIST_ROOMS);
	string roomsList = ClientUtils::readData(this->tcpServer);
	printListString(roomsList, "rooms list");
}

void Client::listRoomUsers(string room)
{
	ClientUtils::sendCommand(this->tcpServer, LIST_ROOM_USERS);
	ClientUtils::sendData(this->tcpServer, room);
	string roomsUsersList = ClientUtils::readData(this->tcpServer);
	printListString(roomsUsersList, "users in room " + room);
}

void Client::login(string username, string password)
{
	cout << "login user: " << username << ", pass: " << password << endl;
	ClientUtils::sendCommand(this->tcpServer, LOGIN);
	ClientUtils::sendData(this->tcpServer, username);
	ClientUtils::sendData(this->tcpServer, password);

	string loginResult = ClientUtils::readData(this->tcpServer);

	if (loginResult == SUCCESS)
	{
		this->username = username;
		cout << "you are logged in as " << this->username << endl;
	}
	else
	{
		cout << "error in login, please try again" << endl;
	}
}

void Client::registerUser(string username, string password)
{
	cout << "register user: " << username << ", pass: " << password << endl;
	ClientUtils::sendCommand(this->tcpServer, REGISTER);
	ClientUtils::sendData(this->tcpServer, username);
	ClientUtils::sendData(this->tcpServer, password);

	string registerResult = ClientUtils::readData(this->tcpServer);

	if (registerResult == SUCCESS)
	{
		this->username = username;
		cout << "you are registered and logged in as " << this->username << endl;
	}
	else
	{
		cout << "username is already taken, please use another one" << endl;
	}
}

void Client::openSession(string username)
{
	deleteOldConnections();
	cout << "opening session with user: " << username << endl;
	ClientUtils::sendCommand(this->tcpServer, OPEN_SESSION_WITH_PEER);
	ClientUtils::sendData(this->tcpServer, username);

	int code = ClientUtils::readCommand(this->tcpServer);

	if (code == SESSION_ESTABLISHED)
	{
		this->status = "connected to " + username;
		this->connectionStatus = CONNECTED_TO_SESSION;
	}
	else
	{
		cout << SESSION_REFUSED_MSG;
	}
}

void Client::openRoom(string room)
{
	deleteOldConnections();
	cout << "entering chat room: " << room << endl;
	this->status = "connected to room " + room;
	this->connectionStatus = CONNECTED_TO_ROOM;
}

void Client::sendMessage(string message)
{
	cout << "sending message: " << message << endl;
	ClientUtils::sendCommand(this->tcpServer, SEND_MSG_TO_PEER);
	ClientUtils::sendData(this->tcpServer, message);
}

string Client::getStatus()
{
	cout << "printing the status: " << this->status << endl;
	return this->status;
}

bool Client::isConnected()
{
	return this->connectionStatus != NOT_CONNECTED;
}

void Client::closeSession()
{
	cout << "closing the session" << endl;
	ClientUtils::sendCommand(this->tcpServer, CLOSE_SESSION_WITH_PEER);
	this->status = "not connected";
	this->connectionStatus = CONNECTED_TO_SERVER;
}

void Client::disconnectFromServer()
{
	cout << "disconnecting from server" << endl;
	this->connectionStatus = NOT_CONNECTED;
	ClientUtils::sendCommand(this->tcpServer, EXIT);
	this->status = "not connected";
}

void Client::closeRoom()
{
	cout << "closing room" << endl;
	ClientUtils::sendCommand(this->tcpServer, CLOSE_ROOM);
	this->status = "not connected";
	this->connectionStatus = CONNECTED_TO_SERVER;
}

void Client::deleteOldConnections()
{
	if (this->connectionStatus == CONNECTED_TO_SESSION)
	{
		closeSession();
	}

	if (this->connectionStatus == CONNECTED_TO_ROOM)
	{
		closeRoom();
	}
}

void Client::printListString(string list, string description)
{
	cout << "------------------------------" << endl;
	cout << description << endl;
	cout << "------------------------------" << endl;
	cout << list << endl;
	cout << "------------------------------" << endl;
}
