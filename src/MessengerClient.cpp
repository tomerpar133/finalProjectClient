/*
 * MessengerClient.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: tomer
 */

#include "MessengerClient.h"

MessengerClient::MessengerClient() {
	// TODO Auto-generated constructor stub

}

MessengerClient::~MessengerClient() {
	// TODO Auto-generated destructor stub
}

int MessengerClient::readCommandFromPeer(TCPSocket* peer){
	//TODO: read a command from socket
	int command = 0;
	peer->recv((char*)&command, sizeof(int));
	return ntohl(command);
}

string MessengerClient::readDataFromPeer(TCPSocket* peer){
	//TODO: read a string from socket
	char msg[MAX_MSG_SIZE];
	int msgLength;
	peer->recv((char*)&msgLength, sizeof(int));
	peer->recv(msg, ntohl(msgLength));
	return msg;
}

void MessengerClient::sendCommandToPeer(TCPSocket* peer, int command){
	//TODO: send command to socket
	command = htonl(command);
	peer->send((char*)&command, sizeof(int));
}

void MessengerClient::sendDataToPeer(TCPSocket* peer, string msg){
	//TODO: send string to socket
	int msgLength = htonl(msg.length());
	peer->send((char*)&msgLength, sizeof(int));
	peer->send(msg.c_str(), msg.length());
}

string MessengerClient::readDataFromPeer(UDPSocket* peer){
	//TODO: read a string from socket
	char msg[MAX_MSG_SIZE];
	int msgLength;
	peer->recv((char*)&msgLength, sizeof(int));
	peer->recv(msg, ntohl(msgLength));
	return msg;
}

void MessengerClient::sendDataToPeer(UDPSocket* peer, string msg){
	//TODO: send string to socket
	int msgLength = htonl(msg.length());
//	peer->sendTo((char*)&msgLength, peer->, sizeof(int));
//	peer->sendTo(msg.c_str(), peer->, msg.length());
	// todo: check with the cornflex
}
