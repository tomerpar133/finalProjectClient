#include "MultipleTCPSocketsListener.h"
#include <sys/select.h>
//#include <libexplain/select.h>
/*
 * Add the given socket to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSocket(TCPSocket* socket )
{
	if (socket == NULL)
	{
		return;
	}
	this->sockets.push_back(socket);
}

/*
 * Set the given sockets to the socket list to be listen on
 */
void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec)
{
	// set the given sockets as the socket list to selct from
	for (unsigned int i = 0; i < socketVec.size(); i++)
	{
		addSocket(socketVec[i]);
	}
}
TCPSocket* MultipleTCPSocketsListener::listenToSocket()
{
	if (sockets.empty())
	{
		return NULL;
	}
	
	// create local set for the select function (fd_set)
	fd_set readFd;
	FD_ZERO(&readFd);


	// fill the set with file descriptors from the socket list using (FD_SET macro)
	
	int biggestSocket = 0;
	
	for (unsigned int i = 0; i < this->sockets.size(); i++)
	{
		int currentFd = this->sockets[i]->getSocketFd();
		FD_SET(currentFd, &readFd);

		if (currentFd > biggestSocket)
		{
			biggestSocket = currentFd;
		}
	}
	struct timeval timeout;
	timeout.tv_sec = TIMEOUT;
	timeout.tv_usec = 0;
	int numOfActiveFds = select(biggestSocket + 1, &readFd, NULL, NULL, &timeout);
	TCPSocket* activeClient = NULL;
	if (numOfActiveFds > 0)
	{
		for (unsigned int i = 0; i < this->sockets.size(); i++)
		{
			TCPSocket* currentSocket = this->sockets[i];
			if (FD_ISSET(currentSocket->getSocketFd(), &readFd))
			{
				cout << "Incoming from : " << currentSocket->getClientAsString() << endl;
				activeClient = currentSocket;
				break;
			}
		}
	} 
	
	// if select return a valid socket return the matching TCPSocket object otherwise return NULL
	return activeClient;
}

int MultipleTCPSocketsListener::findBiggestFd(fd_set* readFd)
{
	int biggest = 0;
	
	for (unsigned int i = 0; i < this->sockets.size(); i++)
	{
		int currentFd = this->sockets[i]->getSocketFd();
		FD_SET(currentFd, readFd);

		if (currentFd > biggest)
		{
			biggest = currentFd;
		}
	}

	return biggest;
}

