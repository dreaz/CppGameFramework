#ifndef NETWORKEDPLAYER_H
#define NETWORKEDPLAYER_H

#include "Component.h"
#include <SFML\Graphics.hpp> 
#include <SFML\Network.hpp>
#include <iostream>
#include "NetworkObject.h"

class NetworkedPlayer : public Component
{
public:
	NetworkedPlayer(std::shared_ptr<GameObject> go);
	~NetworkedPlayer();

	void setID(int id) { m_id = id; m_isReady = true; }
	int getID() { return m_id; }

	bool isReady() { return m_isReady; }

	void setName(std::string name) { m_name = name; }
	std::string getName() { return m_name; }

	void Update(sf::Time deltatime);


	void JoinServer();

	void SendMyName();

	void SendTest();

	void RequestPlayerList();
	std::vector<std::shared_ptr<GameObject>> players;


private:


	int m_id;
	bool m_isReady;
	std::string m_name;

	sf::TcpSocket connection;
	bool m_connected;
	void Disconnect();

};

#endif

