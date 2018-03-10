#include "pakiet.h"

void pakiet::main_server()
{
	//--------------------------------------------------------------------------
	//winsok
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int ws0k = WSAStartup(ver, &wsData);
	if (ws0k != 0)
	{
		std::cerr << "Can't Initialize winsok! Quitting" << std::endl;
		return;
	}

	//------------------------------------------------------------------------
	//soket

	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Can't create a socket! Quitting" << std::endl;
		return;
	}


	//---------------------------------------------------------------------------
	//ip i port do soketu

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//--------------------------------------------------------
	//nas³uch

	listen(listening, SOMAXCONN);


	//------------------------------------------------------------
	//czekanie na po³¹czenie
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);


	char host[NI_MAXHOST];	//client's remote name
	char service[NI_MAXSERV];	//service (i.e. port) the client is connected on

	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client),
		host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " <<
			ntohs(client.sin_port) << std::endl;
	}
	//----------------------------------------------------------------------
	//

	closesocket(listening);

	//------------------------------------------------------------------------
	//
	czyszczenie_pakietu();
	std::cout << "Serwer czysci pakiet" << std::endl;
	id = 37;
	pakowanie_pakietu();
	std::cout << "Serwer pakuje pakiet" << std::endl;
	send(clientSocket, _pakiet, rozmiar_pakietu, 0);
	std::cout << "Serwer wyslal pakiet" << std::endl;
	std::string pom;
	int _liczba1;
	int _liczba2;
	while (true)
	{
		ZeroMemory(_pakiet, rozmiar_pakietu);
		int bytesReceived = recv(clientSocket, _pakiet, rozmiar_pakietu, 0);
		std::cout << "Serwer odebral pakiet" << std::endl;
		
		odpakowanie_pakietu();
		if (status == 1111)
		{
			std::cout << "Zakonczono polaczenie na porcie " << ntohs(client.sin_port) << " o identyfikatorze " << id << std::endl;
			break;
		}
		else
		{

		}
		if (bytesReceived > 0)
		{
			pom = liczba1.to_string();
			_liczba1 = bit_to_int(pom);
			pom = liczba2.to_string();
			_liczba2 = bit_to_int(pom);
			std::cout << "Liczba1 = " << _liczba1 << std::endl;
			std::cout << "Liczba2 = " << _liczba2 << std::endl;
			if (znak == 00) _liczba1 = _liczba1 - _liczba2;
			if (znak == 01) _liczba1 = _liczba1 / _liczba2;
			if (znak == 10) _liczba1 = _liczba1 * _liczba2;
			if (znak == 11) _liczba1 = _liczba1 + _liczba2;

			liczba1 = _liczba1;
			std::cout << "Bitowa liczba1 = " << liczba1 << std::endl;

			pakowanie_pakietu();
			send(clientSocket, _pakiet, rozmiar_pakietu, 0);

		}

	}

	WSACleanup();
}
