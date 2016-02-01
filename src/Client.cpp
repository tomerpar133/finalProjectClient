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
	this->connectedToServer = false;
	this->username = "";
}

Client::~Client() {
	// TODO Auto-generated destructor stub
	delete this->tcpServer;
}

void Client::connectToServer(string ip)
{
	cout << "connecting to server in ip " << ip << endl;
	this->tcpServer = new TCPSocket(ip, MSNGR_PORT);
	this->connectedToServer = true;
}

void Client::listUsers()
{
	cout << "printing the user list" << endl;
	ClientUtils::sendCommand(this->tcpServer, LIST_USERS);
	string usersList = ClientUtils::readData(this->tcpServer);
	cout << usersList;
}

void Client::listConnectedUsers()
{
	cout << "printing the connected user list" << endl;
	ClientUtils::sendCommand(this->tcpServer, LIST_CONNECTED_USERS);
	string connectedUsersList = ClientUtils::readData(this->tcpServer);
	cout << connectedUsersList;
}

void Client::listRooms()
{
	cout << "printing the rooms" << endl;
	ClientUtils::sendCommand(this->tcpServer, LIST_ROOMS);
	string roomsList = ClientUtils::readData(this->tcpServer);
	cout << roomsList;
}

void Client::listRoomUsers(string room)
{
	cout << "showing users in room " << room << endl;
	ClientUtils::sendCommand(this->tcpServer, LIST_ROOM_USERS);
	ClientUtils::sendData(this->tcpServer, room);
	string roomsList = ClientUtils::readData(this->tcpServer);
	cout << roomsList;
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
	cout << "opening session with user: " << username << endl;
	ClientUtils::sendCommand(this->tcpServer, OPEN_SESSION_WITH_PEER);
	ClientUtils::sendData(this->tcpServer, username);
	this->status = "connected to " + username;
}

void Client::openRoom(string room)
{
	cout << "entering chat room: " << room << endl;
	this->status = "connected to room " + room;
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
	return this->connectedToServer;
}

void Client::closeSession()
{
	cout << "closing the session" << endl;
	ClientUtils::sendCommand(this->tcpServer, CLOSE_SESSION_WITH_PEER);
	this->status = "not connected";
}

void Client::disconnectFromServer()
{
	cout << "disconnecting from server" << endl;
	this->connectedToServer = false;
	ClientUtils::sendCommand(this->tcpServer, EXIT);
	this->status = "not connected";
}
