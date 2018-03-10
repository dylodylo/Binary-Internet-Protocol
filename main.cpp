#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>

#include "pakiet.h"
#pragma comment(lib, "Ws2_32.lib")

int main()
{

	std::cout << "Podaj\nczy chcesz byc serwerem (1)\nczy chcesz byc klientem(2)\n";

	int INPUT;
	do
	{
		std::cin >> INPUT;
		if (INPUT == 1)
		{
			pakiet s;
			s.main_server();
		}
		if (INPUT == 2)
		{
			pakiet c;
			c.main_klient();
			break;
		}
	} while (INPUT != 1 || INPUT != 2);
}