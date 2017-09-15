/// <summary>
/// Class only on server to keep track of players and their connections, id and name
/// </summary>

#include "NetworkObject.h"



/// <summary>
/// Each network object is creating from listening to connections on the server. Store the socket that the listener picked up, ie the client
/// </summary>
/// <param name="socket"></param>
/// <param name="id"></param>
NetworkObject::NetworkObject(std::unique_ptr<sf::TcpSocket>* initSocket, int id)
{
	this->id = id;
	//Std move for handling shared_ptr's correctly
	socket = std::move(*initSocket);
	timeout = sf::seconds(0);
}


/// <summary>
/// Get the socket
/// </summary>
/// <returns></returns>
sf::TcpSocket* NetworkObject::GetSocket()
{
	return socket.get();
}

/// <summary>
/// Set the timeout variable
/// </summary>
/// <param name="time"></param>
void NetworkObject::setTimeout(sf::Time time)
{
	timeout = time;
}

/// <summary>
/// Get the timeout variable
/// </summary>
/// <returns></returns>
sf::Time NetworkObject::GetTimeout()
{
	return timeout;
}

/// <summary>
/// Get the ID
/// </summary>
/// <returns></returns>
int NetworkObject::GetID()
{
	return id;
}

/// <summary>
/// Set the name of this networked objects
/// </summary>
/// <param name="name"></param>
void NetworkObject::SetName(const std::string name)
{
	this->name = name;
}

/// <summary>
/// Get the name of this networked object
/// </summary>
/// <returns></returns>
std::string NetworkObject::GetName()
{
	return name;
}

/// <summary>
/// Deconstructor
/// </summary>
NetworkObject::~NetworkObject()
{
}