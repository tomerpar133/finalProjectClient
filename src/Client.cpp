/*
 * Client.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: tomer
 */

#include "Client.h"

Client::Client() {
	// TODO Auto-generated constructor stub
	this->status = "";
	this->tcpServer = NULL;
	this->connectedToServer = false;

}

Client::~Client() {
	// TODO Auto-generated destructor stub
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
}

void Client::registerUser(string username, string password)
{
	cout << "register user: " << username << ", pass: " << password << endl;
	ClientUtils::sendCommand(this->tcpServer, REGISTER);
	ClientUtils::sendData(this->tcpServer, username);
	ClientUtils::sendData(this->tcpServer, password);
}

void Client::openSession(string username)
{
	cout << "opening session with user: " << username << endl;
}

void Client::openRoom(string room)
{
	cout << "entering chat room: " << room << endl;
}

void Client::sendMessage(string message)
{
	cout << "sending message: " << message << endl;
}

string Client::getStatus()
{
	cout << "printing the status" << endl;
	return this->status;
}

bool Client::isConnected()
{
	return this->connectedToServer;
}

void Client::closeSession()
{
	cout << "closing the session" << endl;
}

void Client::disconnectFromServer()
{
	cout << "disconnecting from server" << endl;
}
