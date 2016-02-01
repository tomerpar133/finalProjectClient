/*
 * Client.cpp
 *
 *  Created on: Feb 1, 2016
 *      Author: tomer
 */

#include "Client.h"

Client::Client() {
	// TODO Auto-generated constructor stub

}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

void Client::connectToServer(string ip)
{
	cout << "connecting to server in ip " << ip << endl;
}

vector<string> Client::listUsers()
{
	cout << "printing the user list" << endl;
	return vector<string>();
}

vector<string> Client::listConnectedUsers()
{
	cout << "printing the connected user list" << endl;
	return vector<string>();
}

vector<string> Client::listRooms()
{
	cout << "printing the rooms" << endl;
	return vector<string>();
}

vector<string> Client::listRoomUsers(string room)
{
	cout << "showing users in room " << room << endl;
	return vector<string>();
}

void Client::login(string username, string password)
{
	cout << "login user: " << username << ", pass: " << password << endl;
}

void Client::registerUser(string username, string password)
{
	cout << "register user: " << username << ", pass: " << password << endl;
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

void Client::status()
{
	cout << "printing the status" << endl;
}

void Client::closeSession()
{
	cout << "closing the session" << endl;
}

void Client::disconnectFromServer()
{
	cout << "disconnecting from server" << endl;
}
