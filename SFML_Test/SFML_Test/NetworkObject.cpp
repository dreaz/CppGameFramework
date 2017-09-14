#include "NetworkObject.h"




NetworkObject::NetworkObject(std::unique_ptr<sf::TcpSocket>* socket, sf::Vector2f position, int id)
{
	m_position = position;
	m_name = "Default Name";
	m_id = id;
	m_socket = std::move(*socket);
	m_velocity = sf::Vector2f(0, 0);
	m_timeout = sf::seconds(0);
}



sf::TcpSocket* NetworkObject::GetSocket()
{
	return m_socket.get();
}

void NetworkObject::SetName(const std::string name)
{
	m_name = name;
}

std::string NetworkObject::GetName()
{
	return m_name;
}

void NetworkObject::setTimeout(sf::Time time)
{
	m_timeout = time;
}

sf::Time NetworkObject::getTimeout()
{
	return m_timeout;
}

int NetworkObject::getId()
{
	return m_id;
}

NetworkObject::~NetworkObject()
{
}