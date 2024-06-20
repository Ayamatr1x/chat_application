#include<iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <tchar.h>
#include <thread>
#include <vector>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
//initialise winsock library
//create the socket
//get ip and port 
//bind/port with the socket
//accept
//receieve and send
//cleanup the winsock
bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2,2), &data) == 0;
}
//Initialize

void InteractWithClient(SOCKET clientSOCKET, vector<SOCKET>& clients) {
	//send/recv client
	char buffer[4096];
	while (1) {
		int bytesrecvd = recv(clientSOCKET, buffer, sizeof(buffer), 0);
		if(bytesrecvd <= 0){
			cout << "client Disconnected" << endl;
			break;
		}
		string message(buffer, bytesrecvd);
		cout << "message from client  :  " << message << endl;

		for (auto client : clients) {
			if (client != clientSOCKET) {
				send(client, message.c_str(), message.length(), 0);
			}
		}
	}
	//char buffer[4096];
	auto it = find(clients.begin(), clients.end(), clientSOCKET);
	if (it != clients.end()) {
		clients.erase(it);
	}
	closesocket(clientSOCKET);
}




int main() {
	if (!Initialize()) {
		cout << "Initialization Failed" << endl;
		return 1;
	}







	cout << "server program"<<endl;
	//socket created
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET) {
		cout << "socket Creation failed" << endl;
		return 1;
	}


	//creating address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);


	//convert the ipaddress  (0.0.0.0) put it in sin_family in binary format
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "setting address strucutre failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	};
	//BINDCODE

	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "bind failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}


	//listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "Listen Failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	cout << "SERVER has started listening to port: " << port << endl;
	vector<SOCKET> clients;

	//accept
	while(1){
		SOCKET clientSOCKET = accept(listenSocket, nullptr, nullptr);
		if (clientSOCKET == INVALID_SOCKET) {
			cout << "invalid client socket " << endl;

		}
		

		clients.push_back(clientSOCKET);
		thread t1(InteractWithClient, clientSOCKET, std :: ref(clients));
		t1.detach();
	}
	

	
	closesocket(listenSocket);


	WSACleanup();
	return 0;

}