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
	this->serverListener = NULL;
	this->conferenceMngr = NULL;
}

Client::~Client() {
	if (this->tcpServer)
		delete this->tcpServer;
	if (this->conferenceMngr)
		delete this->conferenceMngr;
	if (this->serverListener)
		delete this->serverListener;
}

void Client::connectToServer(string ip)
{
	cout << "connecting to server in ip " << ip << endl;
	this->tcpServer = new TCPSocket(ip, MSNGR_PORT);
	this->connectionStatus = CONNECTED_TO_SERVER;
	this->serverListener = new ServerListener(this->tcpServer, this);
	this->serverListener->start();
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
	cout << "{ Login user: " << username << ", Pass: " << password << " }" << endl;
	ClientUtils::sendCommand(this->tcpServer, LOGIN);
	ClientUtils::sendData(this->tcpServer, username);
	ClientUtils::sendData(this->tcpServer, password);

	if (ClientUtils::repliedSuccess(this->tcpServer))
	{
		this->username = username;
		cout << "Logged in as " << this->username << endl;
	}
	else
	{
		cout << "Error in login, please try again" << endl;
	}
}

void Client::registerUser(string username, string password)
{
	cout << "{ Register user: " << username << ", Pass: " << password << " }" << endl;
	ClientUtils::sendCommand(this->tcpServer, REGISTER);
	ClientUtils::sendData(this->tcpServer, username);
	ClientUtils::sendData(this->tcpServer, password);

	if (ClientUtils::repliedSuccess(this->tcpServer))
	{
		this->username = username;
		cout << "Registered successfully and logged in as " << this->username << endl;
	}
	else
	{
		cout << "Username is already taken, please pick another" << endl;
	}
}

void Client::openSession(string username)
{
	deleteOldConnections();
	cout << "{ Opening session with user: " << username << " }" << endl;
	ClientUtils::sendCommand(this->tcpServer, OPEN_SESSION_WITH_PEER);
	ClientUtils::sendData(this->tcpServer, username);

	int code = ClientUtils::readCommand(this->tcpServer);

	if (code == SESSION_ESTABLISHED)
	{
		this->status = "connected to " + username;
		this->connectionStatus = CONNECTED_TO_SESSION;
		cout << "Session established." << endl;
	}
	else
	{
		cout << SESSION_REFUSED_MSG << endl;
	}
}

void Client::openRoom(string room)
{
	deleteOldConnections();
	cout << "{ Entering chat room: " << room << " }" << endl;
	ClientUtils::sendCommand(this->tcpServer, OPEN_ROOM);
	ClientUtils::sendData(this->tcpServer, room);
	
	if (ClientUtils::repliedSuccess(this->tcpServer))
	{
		this->status = "connected to room " + room;
		this->connectionStatus = CONNECTED_TO_ROOM;
		cout << "Entered room: " << room << endl;
		this->conferenceMngr = new ConferenceManager(room);
		this->conferenceMngr->start();
	}
	else
	{
		cout << "Could not enter chat room." << endl;
	}
}

void Client::sendMessage(string message)
{
	cout << "sending message: " << message << endl;
	ClientUtils::sendCommand(this->tcpServer, SEND_MSG_TO_PEER);
	ClientUtils::sendData(this->tcpServer, message);
}

string Client::getStatusDescription()
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
	cout << "{ Disconnected from server }" << endl;
	this->connectionStatus = NOT_CONNECTED;
	ClientUtils::sendCommand(this->tcpServer, EXIT);
	this->status = "not connected";

	if (this->serverListener)
	{
		delete this->serverListener;
	}
}

void Client::closeRoom()
{
	cout << "Closing room" << endl;
	
	if (this->conferenceMngr)
	{
		delete conferenceMngr;
		conferenceMngr = NULL;
	}
	
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

int Client::getConnectionStatus()
{
	return this->connectionStatus;
}

ConferenceManager* Client::getConferenceManager()
{
	return this->conferenceMngr;
}

void Client::printListString(string list, string description)
{
	cout << "------------------------------" << endl;
	cout << description << endl;
	cout << "------------------------------" << endl;
	cout << list << endl;
	cout << "------------------------------" << endl;
}
