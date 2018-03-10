#pragma once

#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <vector>
#include <bitset>
#pragma comment(lib, "Ws2_32.lib")



class pakiet
{
private:
	const int rozmiar_pakietu = 10;
	char _pakiet[10];

	// program

	std::bitset<2> znak; //dzia³anie
	std::bitset<32> liczba1;
	std::bitset<32> liczba2;
	std::bitset<4> status;
	std::bitset<6> id;
	std::bitset<4> uzupelnienie;
	int bit_to_int(const std::string &s)
	{
		int liczba = 0;
		for (int i = s.size() - 1, p = 1; i >= 0; i--, p *= 2)
		{
			if (s[i] == '1')
				liczba += p;
		}
		return liczba;
	};
	void czyszczenie_pakietu()
	{
		znak = 0;
		liczba1 = 0;
		liczba2 = 0;
		status = 0;
		id = 0;
		uzupelnienie = 0;
	}
	
	void odpakowanie_pakietu()
	{
		std::string pom;


		std::bitset<8> bajt;
		for (int i = 0; i < rozmiar_pakietu; i++)
		{
			bajt = _pakiet[i];
			pom += bajt.to_string();
		}
		//std::string aa;
		//aa = pom;
		//for (int i = 0, k = 1; i < 2; i++, k--) {
		//	pom[i] = aa[k];
		//}
		//for (int i = 2, k = 33; i < 34; i++, k--) {
		//	pom[i] = aa[k];
		//}
		//for (int i = 34, k = 65; i < 66; i++, k--) {
		//	pom[i] = aa[k];
		//}
		//for (int i = 66, k = 69; i < 70; i++, k--) {
		//	pom[i] = aa[k];
		//}
		//for (int i = 70, k = 75; i < 76; i++, k--) {
		//	pom[i] = aa[k];
		//}

		znak = bit_to_int(pom.substr(0, 2));
		
		liczba1 = bit_to_int(pom.substr(2, 32));
		
		liczba2 = bit_to_int(pom.substr(34, 32));
		status = bit_to_int(pom.substr(66, 4));
		
		id = bit_to_int(pom.substr(70, 6));
	}
	void pakowanie_pakietu()
	{
		{
			std::string pom;
			std::string pom1;
			//znak operacji
			pom = znak.to_string();
			
			//liczba1
			pom += liczba1.to_string();
			
			//liczba2
			pom += liczba2.to_string();
			
			
			//status
			pom += status.to_string();
			
		
			//id
			pom += id.to_string();
		
		
			//uzupe³nienie
			pom += uzupelnienie.to_string();
			
			//std::string aa;
			//aa = pom;
			//for (int i = 0,k=1; i < 2; i++,k--) {
			//	pom[i] = aa[k];
			//}
			//for (int i = 2, k = 33; i < 34; i++, k--) {
			//	pom[i] = aa[k];
			//}
			//for (int i = 34, k = 65; i < 66; i++, k--) {
			//	pom[i] = aa[k];
			//}
			//for (int i = 66, k = 69; i < 70; i++, k--) {
			//	pom[i] = aa[k];
			//}
			//for (int i = 70, k = 75; i < 76; i++, k--) {
			//	pom[i] = aa[k];
			//}

			std::string bajt_1 = pom.substr(0, 8);
			std::string bajt_2 = pom.substr(8, 8);
			std::string bajt_3 = pom.substr(16, 8);
			std::string bajt_4 = pom.substr(24, 8);
			std::string bajt_5 = pom.substr(32, 8);
			std::string bajt_6 = pom.substr(40, 8);
			std::string bajt_7 = pom.substr(48, 8);
			std::string bajt_8 = pom.substr(56, 8);
			std::string bajt_9 = pom.substr(64, 8);
			std::string bajt_10 = pom.substr(72, 8);

			_pakiet[0] = bit_to_int(bajt_1);
			_pakiet[1] = bit_to_int(bajt_2);
			_pakiet[2] = bit_to_int(bajt_3);
			_pakiet[3] = bit_to_int(bajt_4);
			_pakiet[4] = bit_to_int(bajt_5);
			_pakiet[5] = bit_to_int(bajt_6);
			_pakiet[6] = bit_to_int(bajt_7);
			_pakiet[7] = bit_to_int(bajt_8);
			_pakiet[8] = bit_to_int(bajt_9);
			_pakiet[9] = bit_to_int(bajt_10);

		}

	}

	void wypisz(); //wypisanie danych pakietu konsoli


public:
	void main_klient();
	void main_server();
};