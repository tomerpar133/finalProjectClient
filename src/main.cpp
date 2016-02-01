/*
 * main.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: tomer
 */

#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include "Client.h";

using namespace std;
typedef void (*commandHandler)();
map<string, commandHandler> commandsMap;
Client client;

void printInstructions()
{
	cout<<"----------------------------------------------------------"<<endl;
	cout<<"c <ip> - connect to server"<<endl;
	cout<<"lu - print the user list"<<endl;
	cout<<"lcu - print the connected users list"<<endl;
	cout<<"lr - print all rooms"<<endl;
	cout<<"lru <room name> - print all users in this room"<<endl;
	cout<<"login <user> <password> - login with the user and password"<<endl;
	cout<<"register <user> <password> - register the new user with the given password and login the user."<<endl;
	cout<<"o <username> - open a session with the user"<<endl;
	cout<<"or <room name> - enter a chat room"<<endl;
	cout<<"s <message> - send a message"<<endl;
	cout<<"l - print the current status of the client"<<endl;
	cout<<"cs - disconnect the open session / exit from a room"<<endl;
	cout<<"d - disconnect from server"<<endl;
	cout<<"x - exit"<<endl;
	cout<<"----------------------------------------------------------"<<endl;
}

void connectToServer()
{
	string ip;
	cin >> ip;

	client.connectToServer(ip);
}

void listUsers()
{
//	cout << "printing the user list" << endl;
	client.listUsers();
}

void listConnectedUsers()
{
//	cout << "printing the connected user list" << endl;
	client.listConnectedUsers();
}

void listRooms()
{
//	cout << "printing the rooms" << endl;
	client.listRooms();
}

void listRoomUsers()
{
	string room;
	cin >> room;
//	cout << "showing users in room " << room << endl;
	client.listRoomUsers(room);
}

void login()
{
	string username;
	string password;
	cin >> username;
	cin >> password;
//	cout << "login user: " << username << ", pass: " << password << endl;
	client.login(username, password);
}

void registerUser()
{
	string username;
	string password;
	cin >> username;
	cin >> password;
//	cout << "register user: " << username << ", pass: " << password << endl;

	client.registerUser(username, password);
}

void openSession()
{
	string username;
	cin >> username;
//	cout << "opening session with user: " << username << endl;
	client.openSession(username);
}

void openRoom()
{
	string room;
	cin >> room;
//	cout << "entering chat room: " << room << endl;
	client.openRoom(room);
}

void sendMessage()
{
	string message;
	cin >> message;
//	cout << "sending message: " << message << endl;
	client.sendMessage(message);
}

void status()
{
//	cout << "printing the status" << endl;
	client.status();
}

void closeSession()
{
//	cout << "closing the session" << endl;
	client.closeSession();
}

void disconnectFromServer()
{

//	cout << "disconnecting from server" << endl;
	client.disconnectFromServer();
}

void kill()
{
	exit(0);
}

int main()
{
	cout<<"Welcome to the client"<<endl;
	printInstructions();

	commandsMap["c"] = connectToServer;
	commandsMap["lu"] = listUsers;
	commandsMap["lcu"] = listConnectedUsers;
	commandsMap["lr"] = listRooms;
	commandsMap["lru"] = listRoomUsers;
	commandsMap["login"] = login;
	commandsMap["register"] = registerUser;
	commandsMap["o"] = openSession;
	commandsMap["or"] = openRoom;
	commandsMap["s"] = sendMessage;
	commandsMap["l"] = status;
	commandsMap["cs"] = closeSession;
	commandsMap["d"] = disconnectFromServer;
	commandsMap["x"] = kill;

	while(true){
		string command;
		cin >> command;

		if (commandsMap.find(command) != commandsMap.end())
		{
			commandsMap[command]();
		}
		else
		{
			cout<<"wrong input"<<endl;
			printInstructions();
		}
	}

	return 0;
}

