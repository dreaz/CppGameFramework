#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <SFML\Network.hpp>
#include <SFML\Network\Packet.hpp>
#include <iostream>
#include "GameObject.h"
#include "NetworkObject.h"
#include "NetworkedPlayer.h"
#include "PacketIdentifier.h"

class NetworkController
{
public:
	NetworkController();
	~NetworkController();

	/// <summary>
	/// Server code start
	/// </summary>
	void StartServer();
private:
	//void sendPacket(sf::Packet& packet, unsigned int skip = -1);
	bool m_isRunning;

	sf::IpAddress m_ipAdress;
	unsigned short m_port;

	sf::TcpListener listener;
	sf::SocketSelector m_selector;

	int m_maxPlayerNumber;
	int m_currentID;
	int m_playerNumber;

	std::vector<NetworkObject> m_playerList;
	char m_tmp[1400];

	sf::Clock m_clock;

	void SendPackageToClients(sf::Packet & packet, unsigned int skip = -1);

	/// <summary>
	/// Servercode end
	/// </summary>

};
#endif

