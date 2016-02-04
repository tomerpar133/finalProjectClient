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
	while(true)
	{
		cout << ClientUtils::readData(&this->socket) << endl;
	}
}

void ConferenceManager::sendMessage(string message)
{
	for(std::map<string,string>::iterator iter = this->ipToUsernameMap.begin(); iter != this->ipToUsernameMap.end(); ++iter)
		ClientUtils::sendData(&this->socket, iter->first, message);
}

ConferenceManager::~ConferenceManager()
{
	this->socket.cclose();
}
