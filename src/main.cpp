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

using namespace std;
typedef void (*commandHandler)();
map<string, commandHandler> commandsMap;

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
	cout << "connecting to server in ip " << ip << endl;
}

void listUsers()
{
	cout << "printing the user list" << endl;
}

void listConnectedUsers()
{
	cout << "printing the connected user list" << endl;
}

void listRooms()
{
	cout << "printing the rooms" << endl;
}

void listRoomUsers()
{
	string room;
	cin >> room;
	cout << "showing users in room " << room << endl;
}

void login()
{
	string username;
	string password;
	cin >> username;
	cin >> password;
	cout << "login user: " << username << ", pass: " << password << endl;
}

void registerUser()
{
	string username;
	string password;
	cin >> username;
	cin >> password;
	cout << "register user: " << username << ", pass: " << password << endl;
}

void openSession()
{
	string username;
	cin >> username;
	cout << "opening session with user: " << username << endl;
}

void openRoom()
{
	string room;
	cin >> room;
	cout << "entering chat room: " << room << endl;
}

void sendMessage()
{
	string message;
	cout << "sending message: " << message << endl;
}

void status()
{
	cout << "printing the status" << endl;
}

void closeSession()
{
	cout << "closing the session" << endl;
}

void disconnectFromServer()
{
	cout << "disconnecting from server" << endl;
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

