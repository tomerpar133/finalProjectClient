#include "ConferenceManager.h"

ConferenceManager::ConferenceManager(string roomName)
{
	this->roomName = roomName;
}

void ConferenceManager::addUser(string username, string ip)
{
	cout << username << " has joined the chat." << endl;
	this->ipToUsernameMap[ip] = username;
}

void ConferenceManager::removeUser(string ip)
{
	cout << this->ipToUsernameMap[ip] << " has left the chat." << endl;
	this->ipToUsernameMap.erase(ip);
}

void ConferenceManager::run()
{
	char messageBuffer[MAX_MSG_SIZE];
	while(true)
	{
		messageBuffer[0] = 0;
		this->socket.recv(messageBuffer, MAX_MSG_SIZE);
		
		if (messageBuffer[0] != 0)
		{
			cout << messageBuffer << endl;
		}
	}
}

void ConferenceManager::sendMessage(string message)
{
	for(std::map<string,string>::iterator iter = this->ipToUsernameMap.begin(); iter != this->ipToUsernameMap.end(); ++iter)
		this->socket.sendTo(message, iter->first,PEER_PORT);
}

ConferenceManager::~ConferenceManager()
{
}
