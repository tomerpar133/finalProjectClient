/*
 * ClientUtils.cpp
 *
 *  Created on: Jan 31, 2016
 *      Author: tomer
 */

#include "ClientUtils.h"

ClientUtils::ClientUtils() {

}

ClientUtils::~ClientUtils() {
}

int ClientUtils::readCommand(TCPSocket* peer){
	// read a command from socket
	int command = 0;
	peer->recv((char*)&command, sizeof(int));
	return ntohl(command);
}

string ClientUtils::readData(TCPSocket* peer){
	// read a string from socket
	char msg[MAX_MSG_SIZE];
	int msgLength;
	peer->recv((char*)&msgLength, sizeof(int));
	peer->recv(msg, ntohl(msgLength));
	return msg;
}

void ClientUtils::sendCommand(TCPSocket* peer, int command){
	// send command to socket
	command = htonl(command);
	peer->send((char*)&command, sizeof(int));
}

void ClientUtils::sendData(TCPSocket* peer, string msg){
	// send string to socket
	int msgLength = htonl(msg.length() + 1);
	peer->send((char*)&msgLength, sizeof(int));
	peer->send(msg.c_str(), msg.length() + 1);
}

string ClientUtils::readData(UDPSocket* peer){
	// read a string from socket
	char msg[MAX_MSG_SIZE];
	int msgLength;
	peer->recv((char*)&msgLength, sizeof(int));
	peer->recv(msg, ntohl(msgLength));
	return msg;
}

void ClientUtils::sendData(UDPSocket* sender, string peerIp, string msg){
	// send string to socket
	int msgLength = htonl(msg.length());
	sender->sendTo((char*)&msgLength, peerIp, PEER_PORT);
	sender->sendTo(msg.c_str(), peerIp, PEER_PORT);
}

bool ClientUtils::repliedSuccess(TCPSocket* socket)
{
	return ClientUtils::readData(socket) == SUCCESS;
}
