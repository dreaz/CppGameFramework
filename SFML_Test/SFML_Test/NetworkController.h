#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <SFML\Network.hpp>
#include <SFML\Network\Packet.hpp>
#include <iostream>

class NetworkController
{
public:
	NetworkController();
	~NetworkController();

public:
	void Update();
	void Host();
	void JoinLocalhost();
	bool isHosting;
	bool isClient;
private:
	void DoStuff();
	bool quit;
	sf::Mutex globalMutex;
	std::string msgSend;
	sf::UdpSocket *socket;

	sf::Thread* hostThread;
	sf::Thread* clientThread;

	void DoServerStuff();
	void DoClientStuff();

	unsigned short port;
		
};
#endif

