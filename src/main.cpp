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
#include "Client.h"

using namespace std;
typedef void (*commandHandler)();
map<string, commandHandler> commandsMap;
map<string, commandHandler> offlineCommandsMap;
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
	client.listUsers();
}

void listConnectedUsers()
{
	client.listConnectedUsers();
}

void listRooms()
{
	client.listRooms();
}

void listRoomUsers()
{
	string room;
	cin >> room;
	client.listRoomUsers(room);
}

void login()
{
	string username;
	string password;
	cin >> username;
	cin >> password;
	client.login(username, password);
}

void registerUser()
{
	string username;
	string password;
	cin >> username;
	cin >> password;
	client.registerUser(username, password);
}

void openSession()
{
	string username;
	cin >> username;
	client.openSession(username);
}

void openRoom()
{
	string room;
	cin >> room;
	client.openRoom(room);
}

void sendMessage()
{
	string message;
	cin >> message;
	client.sendMessage(message);
}

void status()
{
	client.getStatus();
}

void closeSession()
{
	client.closeSession();
}

void disconnectFromServer()
{

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

	commandsMap["lu"] = listUsers;
	commandsMap["lcu"] = listConnectedUsers;
	commandsMap["lr"] = listRooms;
	commandsMap["lru"] = listRoomUsers;
	commandsMap["login"] = login;
	commandsMap["register"] = registerUser;
	commandsMap["o"] = openSession;
	commandsMap["or"] = openRoom;
	commandsMap["s"] = sendMessage;
	commandsMap["cs"] = closeSession;
	commandsMap["d"] = disconnectFromServer;
	offlineCommandsMap["c"] = connectToServer;
	offlineCommandsMap["l"] = status;
	offlineCommandsMap["x"] = kill;

	while(true){
		string command;
		cin >> command;

		if (offlineCommandsMap.find(command) != offlineCommandsMap.end())
		{
			offlineCommandsMap[command]();
		}
		else if (commandsMap.find(command) != commandsMap.end())
		{
			if (client.isConnected())
				commandsMap[command]();
			else
				cout << "Invalid operation, connect to a server first" << endl;
		}
		else
		{
			cout<<"wrong input"<<endl;
			printInstructions();
		}
	}

	return 0;
}

