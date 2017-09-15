#ifndef PACKETIDENTIFIER_H
#define PACKETIDENTIFIER_H
enum PacketType
{
	InitialConnection = 0,
	Disconnection = 1,
	ServerFull = 2,
	SyncPlayers = 3,
	SavePlayerName = 4,
	SyncPosition = 5


};


#endif