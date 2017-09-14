#include "NetworkedPlayer.h"



NetworkedPlayer::NetworkedPlayer(std::shared_ptr<GameObject> go) : Component(go, "NetworkedPlayerCmp")
{
	setID(-1);
	setName("NF Mynster");
}


NetworkedPlayer::~NetworkedPlayer()
{
	Disconnect();
}

void NetworkedPlayer::Update(sf::Time deltatime)
{
	if (!m_connected)
	{
		return;
	}
	//receive updates
	sf::Packet receivePacket;
	int type, id;
	if (connection.receive(receivePacket) == sf::Socket::Done)
	{
		receivePacket >> type;
		receivePacket >> id;

		if (type == 0) // you connected to server, get your ID
		{
			if (getID() == -1)
			{
				setID(id);
				std::cout << "I connected to server, my ID: " << getID() << std::endl;
				this->SendMyName();
				sf::sleep(sf::milliseconds(50));
				RequestPlayerList();
			}
			//m_connected = true;
		}
		else if (type == 1) // disconnected
		{
			std::cout << "Player disconnected" << std::endl;
			/*for (unsigned int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i]->getID() == id)
				{
					m_textMessage = "Player " + enemies[i]->getName() + " disconnected.";
					std::cout << "Enemy: " << enemies[i]->getID() << " deleted " << std::endl;
					enemies.erase(enemies.begin() + i);
				}
			}*/
		}
		else if (type == 2)
		{
			std::cout << "Server is full" << std::endl;
		}
		else if (type == 7) //Create new players
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


			for (unsigned int i = 0; i < playersId.size(); ++i) //loop through id-s we got
			{
				bool haveThatEnemy = false;
				for (unsigned int v = 0; v < players.size(); v++) //check if we already have enemy with that id
				{
					std::shared_ptr<NetworkedPlayer> networkCmp = std::dynamic_pointer_cast<NetworkedPlayer>(players[v]->GetComponent("NetworkedPlayerCmp"));
					if (networkCmp->getID() == playersId[i])
					{
						haveThatEnemy = true;
					}

				}
				if (playersId[i] != getID() && !haveThatEnemy) //if it is not our id and if we dont have that enemy, create a new enemy with that id
				{
					players.push_back(std::make_shared<GameObject>(sf::Vector2f(100, 100)));
					//m_textMessage = "New player connected: " + playersName[i];
					std::cout << "Created a new player with id: " << playersId[i] << std::endl;

				}
			}

			playersName.clear();
			playersId.clear();

		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		SendTest();
	}
}


void NetworkedPlayer::SendMyName()
{
	sf::Packet temp;
	temp << 6;
	temp << getID();
	temp << getName();

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending my name" << std::endl;
	}

}

void NetworkedPlayer::SendTest()
{
	sf::Packet temp;
	temp << 10;
	temp << "HEJ";

	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending disconnect command to server" << std::endl;
	}
	else
	{
		std::cout << "Disconnected" << std::endl;
	}
}

void NetworkedPlayer::RequestPlayerList()
{
	sf::Packet temp;
	temp << 7;
	temp << getID();
	
	if (connection.send(temp) != sf::Socket::Done)
	{
		std::cout << "Error sending getPlayerList to server" << std::endl;
	}
}

void NetworkedPlayer::JoinServer()
{
	sf::IpAddress ip = "localhost";
	if (connection.connect(ip, 45000, sf::seconds(5)) != sf::Socket::Done)
	{
		std::cout << "Error connecting to server" << std::endl;
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
	sf::Packet temp;
	temp << 1;
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

