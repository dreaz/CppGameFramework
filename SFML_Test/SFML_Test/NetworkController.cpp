#include "NetworkController.h"



NetworkController::NetworkController()
{
	isHosting = false;
	isClient = false;
	quit = false;
	port = 14630;
}


NetworkController::~NetworkController()
{
}

void NetworkController::Update()
{

}

void NetworkController::DoStuff()
{
	static std::string oldMsg;
	while (!quit)
	{

		// Wait for a message
		char in[128];
		std::size_t received;
		sf::IpAddress sender;
		unsigned short senderPort;
		if (socket->receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
			return;
		std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;

		// Send an answer to the client
		const char out[] = "Hi, I'm the server";
		if (socket->send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
			return;
		std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;
	}
}

void NetworkController::DoServerStuff()
{
	// Create a socket to receive a message from anyone
	sf::UdpSocket socket;

	// Listen to messages on the specified port
	if (socket.bind(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;

	// Wait for a message
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;

	// Send an answer to the client
	const char out[] = "Hi, I'm the server";
	if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

	while (!quit)
	{

		std::string s;
		std::cout << "\nEnter \"exit\" to quit or message to send: ";
		std::cin >> s;
		if (s == "exit")
			quit = true;		
		
		// Group the variables to send into a packet
		sf::Packet packet;
		packet << s;
		if (socket.send(packet, sender, senderPort) != sf::Socket::Done)
			return;
		std::cout << "Message sent to the client: \"" << s << "\"" << std::endl;
	}
}

void NetworkController::DoClientStuff()
{
	sf::IpAddress server = "127.0.0.1";
	// Create a socket for communicating with the server
	sf::UdpSocket socket;
	

	// Send a message to the server
	const char out[] = "Hi, I'm a client";
	if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;

	while (!quit)
	{
		// create a packet to receive
		sf::Packet packet;
		sf::IpAddress sender;
		unsigned short senderPort;
		if (socket.receive(packet, sender, senderPort) != sf::Socket::Done)
			return;

		//extract package
		std::string s;
		//Deserialize it
		if (packet >> s)
		{
			// Data extracted successfully...
			std::cout << "Message received from " << sender << ": \"" << s << "\"" << std::endl;
		}
	}
	
}

void NetworkController::Host()
{
	isHosting = true;
	// Create a socket to receive a message from anyone
	socket = new sf::UdpSocket;
	//socket = new sf::UdpSocket();

	// Listen to messages on the specified port
	if (socket->bind(sf::Socket::AnyPort) != sf::Socket::Done)
		return;
	std::cout << "Server started!";

	//hostThread = new sf::Thread(&NetworkController::DoStuff, this);
	//hostThread->launch();

	hostThread = new sf::Thread(&NetworkController::DoServerStuff, this);
	hostThread->launch();
}

void NetworkController::JoinLocalhost()
{
	isClient = true;

	// Ask for the server address
	/*sf::IpAddress server;
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> server;
	} while (server == sf::IpAddress::None);*/

	socket = new sf::UdpSocket;

	//clientThread = new sf::Thread(&NetworkController::DoStuff, this);
	//clientThread->launch();

	clientThread = new sf::Thread(&NetworkController::DoClientStuff, this);
	clientThread->launch();

}
