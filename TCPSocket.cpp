// Small test TCP Socket

#include "stdafx.h"
#define _WINSOCKAPI_

#include <iostream>
#include<winsock2.h>
#include <Windows.h>
#include<stdlib.h>
#include <WS2tcpip.h>


using namespace std;
#pragma comment(lib,"ws2_32.lib")	 //Winsock Library
#pragma comment (lib, "dinput8.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

DWORD dwRecvTimeout = 1000, // Milliseconds
dwSendTimeout = 1000; // Milliseconds

#define PORT "5555"
#define IP_LOCAL "52.16.41.91" 	

int main() {
	while (1) {
		WSADATA wsa;
		SOCKET s;
		WSAStartup(MAKEWORD(2, 2), &wsa);

		SOCKET ConnectSocket = INVALID_SOCKET;
		struct addrinfo *result = NULL,
			*ptr = NULL,
			hints;

		int iResult;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		iResult = getaddrinfo(IP_LOCAL, PORT, &hints, &result);

		ConnectSocket = socket(result->ai_family, result->ai_socktype, 0);
		iResult = connect(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);

		setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&dwRecvTimeout, sizeof(dwRecvTimeout));

		//////////////// RECEIVE // UNPACK //////
		char server_reply[64];
		for (int i = 0; i < 1; i++) {
			int recibir = recv(ConnectSocket, server_reply, 64, 0);			
			cout << "Rec: " << recibir << " / " << endl;		

			for (int ii = 0; ii < recibir; ++ii) {
				cout << server_reply[ii];
			}
			cout << endl;
		}
		closesocket(ConnectSocket);
		Sleep(1000);
	}
	WSACleanup();
	
}
