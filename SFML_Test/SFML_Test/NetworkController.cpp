#include "NetworkController.h"



NetworkController::NetworkController()
{

}


NetworkController::~NetworkController()
{
}

void NetworkController::StartServer()
{
	//Initialize some server values
	m_maxPlayerNumber = 2;
	m_currentID = 0;
	m_playerNumber = 0;
	m_isRunning = true;


	listener.listen(45000);

	m_selector.add(listener);
	std::cout << "Server is started. Waiting for clients" << std::endl;

	while (m_isRunning)
	{
		if (m_selector.wait())
		{
			if (m_selector.isReady(listener)) // if server is ready to receive new connections
			{
				std::unique_ptr<sf::TcpSocket> tempSocket = std::make_unique<sf::TcpSocket>();

				if (listener.accept(*tempSocket) == sf::Socket::Done)
				{
					if (m_playerNumber < m_maxPlayerNumber) //if server is not full
					{
						m_playerList.emplace_back(NetworkObject(&tempSocket, sf::Vector2f(0, 0), m_currentID));
						m_selector.add(*m_playerList.back().GetSocket());
						m_playerNumber++;

						std::cout << "A player joined" << std::endl;

						sf::Packet outPacket;
						outPacket << 0;
						outPacket << m_currentID;

						if (m_playerList.back().GetSocket()->send(outPacket) != sf::Socket::Done) //Send client id
							std::cout << "error sending player index" << std::endl;
						m_currentID++;
					}
					else //if server is full
					{
						sf::Packet outPacket;
						outPacket << 2;
						outPacket << 0;

						if (tempSocket->send(outPacket) != sf::Socket::Done)
							std::cout << "Error sending server is full message" << std::endl;

						std::cout << "User tried to connect but the server was full" << std::endl;
					}
				}


			}
			else
			{
				//Receive data
				for (unsigned int i = 0; i < m_playerList.size(); i++)
				{
					if (m_selector.isReady(*m_playerList[i].GetSocket()))
					{
						sf::Packet received;
						if (m_playerList[i].GetSocket()->receive(received) == sf::Socket::Done)
						{
							m_playerList[i].setTimeout(m_clock.getElapsedTime());

							int num, id;
							received >> num;
							received >> id;


							// 0 is sent when player establishes a connection to the server

							if (num == 1) // player disconnected, send message to all players to delete his character and delete him from servers players list
							{

								//sendPacket(received, i);

								for (auto& itr : m_playerList)
								{
									if (itr.getId() == id)
									{

										std::cout << std::endl << "Client disconnected!" << std::endl;
										std::cout << "	ID: " << itr.getId() << " Name: " << itr.GetName() << std::endl;
									}
								}

								std::cout << "Number of players: " << m_playerNumber << std::endl;
								m_selector.remove(*m_playerList[i].GetSocket());
								m_playerList.erase(m_playerList.begin() + i);
								m_playerNumber--;
								break;
							}
							else if (num == 10)
							{
								std::cout << "SendTest" << std::endl;
							}
							else if (num == 7) //send client list with id and names  When player recive this it goes through the list and compares it with its list, if he finds a number that he doesn't have he creates a enemy with that id
							{
								sf::Packet namePacket;
								namePacket << 7;
								namePacket << 0;
								namePacket << m_playerNumber;

								for (unsigned int j = 0; j < m_playerList.size(); ++j)
								{
									namePacket << m_playerList[j].getId();
									namePacket << m_playerList[j].GetName();
								}

								SendPackageToClients(namePacket);
							}
						}
					}
				}
			}
		}
	}

}

void NetworkController::SendPackageToClients(sf::Packet & packet, unsigned int skip)
{
	for (unsigned int i = 0; i < m_playerList.size(); ++i)
	{
		//Skip id of 0
		if (skip == i)
			continue;

		if (m_playerList[i].GetSocket()->send(packet) != sf::Socket::Done)
		{
			std::cout << "Error sending packet in sendPacket func" << std::endl;
		}
	}
}




