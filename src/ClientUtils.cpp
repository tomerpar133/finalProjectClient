/*
 * ClientUtils.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: tomer
 */

#include "ClientUtils.h"

ClientUtils::ClientUtils() {
	// TODO Auto-generated constructor stub

}

ClientUtils::~ClientUtils() {
	// TODO Auto-generated destructor stub
}

int ClientUtils::readCommand(TCPSocket* peer){
	//TODO: read a command from socket
	int command = 0;
	peer->recv((char*)&command, sizeof(int));
	return ntohl(command);
}

string ClientUtils::readData(TCPSocket* peer){
	//TODO: read a string from socket
	char msg[MAX_MSG_SIZE];
	int msgLength;
	peer->recv((char*)&msgLength, sizeof(int));
	peer->recv(msg, ntohl(msgLength));
	return msg;
}

void ClientUtils::sendCommand(TCPSocket* peer, int command){
	//TODO: send command to socket
	command = htonl(command);
	peer->send((char*)&command, sizeof(int));
}

void ClientUtils::sendData(TCPSocket* peer, string msg){
	//TODO: send string to socket
	int msgLength = htonl(msg.length() + 1);
	peer->send((char*)&msgLength, sizeof(int));
	peer->send(msg.c_str(), msg.length() + 1);
}

string ClientUtils::readData(UDPSocket* peer){
	//TODO: read a string from socket
	char msg[MAX_MSG_SIZE];
	int msgLength;
	peer->recv((char*)&msgLength, sizeof(int));
	peer->recv(msg, ntohl(msgLength));
	return msg;
}

void ClientUtils::sendData(UDPSocket* peer, string msg){
	//TODO: send string to socket
	int msgLength = htonl(msg.length());
//	peer->sendTo((char*)&msgLength, peer->, sizeof(int));
//	peer->sendTo(msg.c_str(), peer->, msg.length());
	// todo: check with the cornflex
}
