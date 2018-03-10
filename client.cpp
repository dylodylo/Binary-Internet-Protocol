#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include "pakiet.h"

#pragma comment(lib,"ws2_32.lib")

void pakiet::main_klient()
{
	std::bitset<6> identyfikator;
	std::string ipAddress = "127.0.0.1";
	int port = 54000;

	WSADATA data;
	WORD ver MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock" << wsResult << std::endl;
		return;
	}

	//socket

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);


	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	else
	{
		while (recv(sock, _pakiet, rozmiar_pakietu, 0) < 0)
			recv(sock, _pakiet, rozmiar_pakietu, 0);
		std::cout << "Klient odebral pakiet" << std::endl;
		odpakowanie_pakietu();
		std::cout << "Klient odpakowal pakiet" << std::endl;
		identyfikator = id;
	}


	//

	int _liczba1 = 0;
	int _liczba2 = 0;
	std::string dzialanie;
	std::string pom;
	while (true)
	{
		std::cout << "> Podaj pierwsza liczbe" << std::endl;
		std::cin >> _liczba1;
		std::cout << "> Podaj druga liczbe:" << std::endl;
		std::cin >> _liczba2;
		std::cout << "> Wpisz znak dzia³ania";
		std::cin >> dzialanie;
		if (dzialanie == "+") znak = 11;
		if (dzialanie == "-") znak = 00;
		if (dzialanie == "/") znak = 01;
		if (dzialanie == "*") znak = 10;

		//zamiana liczb string na binarne
		liczba1 = _liczba1;
		liczba2 = _liczba2;
		id = identyfikator;
		pakowanie_pakietu();
		std::cout << "Klient spakowal pakiet" << std::endl;
		int sendResult = send(sock, _pakiet, rozmiar_pakietu, 0);
		std::cout << "Klient wyslal pakiet" << std::endl;
		

		if (sendResult != SOCKET_ERROR)
		{
			ZeroMemory(_pakiet, rozmiar_pakietu);
			int bytesReceived = recv(sock, _pakiet, rozmiar_pakietu, 0);
			if (bytesReceived > 0)
			{
				odpakowanie_pakietu();
				pom = liczba1.to_string();
				std::cout << "Wynik to: " << bit_to_int(pom) << std::endl;

			}
		}
		std::cout << "Czy chcesz zakonczyc sesje? (t/n)" << std::endl;
		std::cin >> pom;
		if (pom == "t")
		{
			czyszczenie_pakietu();
			id = identyfikator;
			status = 1111;
			pakowanie_pakietu();
			send(sock, _pakiet, rozmiar_pakietu, 0);
			break;
		}
		
	}
	closesocket(sock);
	WSACleanup();
}