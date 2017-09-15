#ifndef NETWORKOBJECT_H
#define NETWORKOBJECT_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>
#include <string>

class NetworkObject
{
public:
	NetworkObject(std::unique_ptr<sf::TcpSocket>* socket, int id);
	~NetworkObject();

	sf::TcpSocket* GetSocket();
	int GetID();

	void SetName(const std::string name);
	std::string GetName();

	void setTimeout(sf::Time time);
	sf::Time GetTimeout();

private:

	int id;
	std::shared_ptr<sf::TcpSocket> socket = nullptr;
	sf::Time timeout;
	std::string name;
};

#endif