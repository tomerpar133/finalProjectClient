#ifndef CONFERENCEMANAGER_H_
#define CONFERENCEMANAGER_H_

#include <string>
#include <map>
#include <string.h>
#include "ClientUtils.h"
#include "UDPSocket.h"
#include "MThread.h"
#include "TCPMessengerProtocol.h"

using namespace std;

class ConferenceManager : public MThread
{
	UDPSocket socket;
	string roomName;
	map<string, string> ipToUsernameMap; // IP to Username routing map
	
public:
	ConferenceManager(string roomName);
	void sendMessage(string message);
	void addUser(string username, string ip);
	void removeUser(string ip);
	virtual ~ConferenceManager();
	void run();
};

#endif /*CONFERENCEMANAGER_H_*/
