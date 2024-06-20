#include<iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#include <string>

#pragma comment(lib, "ws2_32.lib")


using namespace std;

//initialize winsoc
//create socket
//connect to server
//send/recv
//close the socket

bool Initialize() {
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2) , &data)==0;
}


void SendMsg(SOCKET S) {
	cout << "enter your chat name : " << endl;
	string name,message;
	getline(cin, name);
	while (1) {
		getline(cin, message);
		string msg = name + " : " + message;
		int bytesent = send(S, msg.c_str(), msg.length(), 0);
		if (bytesent == SOCKET_ERROR) {
			cout << "Error Sending message" << endl;
			break;
		}

		if(message == "quit"){
			cout << "Stopping the application" << endl;
		
		}
	}

	closesocket(S);
	WSACleanup();

}

void ReceiveMsg(SOCKET S) {
	char buffer[4096];
	int recvlength;
	string msg = " ";
	while (1) {
		recvlength = recv(S, buffer, sizeof(buffer), 0);
		if (recvlength <= 0) {
			cout << "Disconnected from server"<< endl	;	
			break;
		}
		else {
			msg = string(buffer, recvlength);
			cout << msg << endl;
		}
	}


	closesocket(S);
	WSACleanup();
}

int main() {
	if (!Initialize()){
		cout << "Initialization Winsock failed";
		return 1;
	}


		//socket creation
	SOCKET S;
	S = socket(AF_INET, SOCK_STREAM, 0);
	if (S == INVALID_SOCKET) {
		cout << "invalid socket created" << endl;
		return 1;
	}
	int port = 12345;	 
	string serveraddress = "127.0.0.1";
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

	if (connect(S, reinterpret_cast<SOCKADDR*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "not able to connect to server";
		closesocket(S);
		WSACleanup();
		return 1;

	}

	cout << "successfully connected to server" << endl;

	thread senderthread(SendMsg, S);
	thread receiverthread(ReceiveMsg, S);

		//send/recv
	senderthread.join();
	receiverthread.join();



	




	

	return 0;
}