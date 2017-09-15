/// <summary>
/// The networking class for the client.
/// </summary>

#include "NetworkedPlayer.h"
//I should feel bad
#include "GameManager.h"


NetworkedPlayer::NetworkedPlayer(std::shared_ptr<GameObject> go) : Component(go, "NetworkedPlayerCmp")
{
	//Defaults
	setID(-1);
	setName("NF Mynster");
}


NetworkedPlayer::~NetworkedPlayer()
{
	Disconnect();
}

void NetworkedPlayer::Update(sf::Time deltatime)
{
	//Don't do anything if we are not connected
	if (!m_connected)
	{
		return;
	}

	//receive data
	ReceiveData();
	//Send data
	SendData();
}

/// <summary>
/// Send the name package to the server
/// </summary>
void NetworkedPlayer::SendMyName()
{
	sf::Packet temp;
	temp << (int)PacketType::SavePlayerName;
	temp << getID();
	temp << getName();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending my name" << std::endl;
	}

}

/// <summary>
/// Send a request for the player count to the server
/// </summary>
void NetworkedPlayer::RequestPlayerList()
{
	sf::Packet temp;
	temp << (int)PacketType::SyncPlayers;
	temp << getID();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending getPlayerList to server" << std::endl;
	}
}

/// <summary>
/// The method that handles and receives all data. Each packet has a type number, which defines what action each packet does
/// </summary>
void NetworkedPlayer::ReceiveData()
{
	//Create the receiver packet
	sf::Packet receivePacket;
	//All packets are sent with a type(packetType) and a sender ID
	int type, id;
	if (connection.receive(receivePacket) == sf::Socket::Done)
	{
		receivePacket >> type;
		receivePacket >> id;

		if (type == (int)PacketType::InitialConnection) // you connected to server, get your ID
		{
			//If no ID has been assigned to this
			if (getID() == -1)
			{
				//set the id to the received
				setID(id);
				std::cout << "I connected to server, my ID: " << getID() << std::endl;
				//send the name packet for the server
				this->SendMyName();
				sf::sleep(sf::milliseconds(50));
				//Request to figure out who else is connected
				RequestPlayerList();
			}			
		}
		else if (type == (int)PacketType::Disconnection) // disconnected
		{
			std::cout << "Player disconnected" << std::endl;
			//Find the player by id and remove him
			for (unsigned int i = 0; i < players.size(); i++)
			{
				if (players[i]->getID() == id)
				{
					std::cout << "Player  " << players[i]->getName() << " disconnected!" << std::endl;
					players.erase(players.begin() + i);
				}
			}
		}
		else if (type == (int)PacketType::ServerFull)
		{
			std::cout << "Server is full" << std::endl;
		}
		//Sync player amount to clients
		else if (type == (int)PacketType::SyncPlayers)
		{
			int playerNumber;
			std::vector<std::string> playersName;
			std::vector<int> playersId;

			receivePacket >> playerNumber;
			std::cout << "Num of players on server: " << playerNumber << std::endl;

			for (int i = 0; i < playerNumber; ++i)
			{
				std::string tempName;
				int tempId;
				receivePacket >> tempId;
				receivePacket >> tempName;
				playersName.push_back(tempName);
				playersId.push_back(tempId);
			}
			//loop through id-s we got
			for (unsigned int i = 0; i < playersId.size(); ++i)
			{
				bool haveThatPlayer = false;
				//check if we already have enemy with that id (contains)
				for (unsigned int v = 0; v < players.size(); v++)
				{
					if (players[v]->getID() == playersId[i])
					{
						haveThatPlayer = true;
					}
				}
				//if it's not our own id, and we don't have the player registered, create him and give him an ID
				if (playersId[i] != getID() && !haveThatPlayer)
				{
					std::shared_ptr<GameObject> remoteClient = std::make_shared<GameObject>(sf::Vector2f(100, 100));
					std::shared_ptr<NetworkedPlayer> cmp = std::make_shared<NetworkedPlayer>(remoteClient);
					remoteClient->AddComponent(cmp);
					//set the id
					cmp->setID(playersId[i]);
					GameManager::GetInstance()->AddObject(remoteClient);
					players.push_back(cmp);
					std::cout << "New player joined:  " << playersName[i] << std::endl;
					std::cout << "Created a new player with id: " << playersId[i] << std::endl;

				}
			}

			playersName.clear();
			playersId.clear();

		}
		else if (type == (int)PacketType::SyncPosition)
		{
			for (unsigned int i = 0; i < players.size(); i++)
			{
				if (players[i]->getID() == id)
				{
					sf::Vector2f pos;
					receivePacket >> pos.x;
					receivePacket >> pos.y;

					players[i]->GetGameObject()->setPosition(pos);
					break;
				}

			}
		}
	}
}

void NetworkedPlayer::SendData()
{
	//Only send data once pr second
	sendDataTimer += m_clock.restart();
	if (sendDataTimer >= sf::seconds(1))
	{
		sendDataTimer = sf::Time::Zero;
		if (m_connected)
		{
			sf::Packet temp;
			temp << PacketType::SyncPosition;
			temp << getID();
			temp << GetGameObject()->getPosition().x;
			temp << GetGameObject()->getPosition().y;

			if (GetGameObject()->getPosition() != lastPosSent)
			{
				if (connection.send(temp) != sf::Socket::Done)
				{
					std::cout << "Error sending pos data to server" << std::endl;
					return;
				}
			}

			//std::cout << "Sent position update" << std::endl;
			lastPosSent = GetGameObject()->getPosition();

		}
	}

}


void NetworkedPlayer::JoinServer()
{
	sf::IpAddress ip = "localhost";
	std::cout << "Connecting to local host" << std::endl;
	if (connection.connect(ip, 45000, sf::seconds(5)) != sf::Socket::Done)
	{
		std::cout << "Error connecting to server" << std::endl;
		m_connected = false;
	}
	else
	{
		m_connected = true;
		connection.setBlocking(false);
		std::cout << "Connected" << std::endl;
	}

}


void NetworkedPlayer::Disconnect()
{
	if (!m_connected)
	{
		return;
	}
	sf::Packet temp;
	temp << (int)PacketType::Disconnection;
	temp << getID();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending disconnect command to server" << std::endl;
	}
	else
	{
		std::cout << "Disconnected" << std::endl;
	}

}

