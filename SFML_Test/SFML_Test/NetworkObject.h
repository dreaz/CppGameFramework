#ifndef NETWORKOBJECT_H
#define NETWORKOBJECT_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>
#include <string>

class NetworkObject
{
public:
	NetworkObject(std::unique_ptr<sf::TcpSocket>* socket, sf::Vector2f position, int id);
	~NetworkObject();

	sf::TcpSocket* GetSocket();
	int getId();

	void SetName(const std::string name);
	std::string GetName();

	void setTimeout(sf::Time time);
	sf::Time getTimeout();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	std::string m_name;
	int m_id;
	std::shared_ptr<sf::TcpSocket> m_socket = nullptr;
	sf::Time m_timeout;
};

#endif