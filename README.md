# chat_application

End-to-End Chat Encryption using C++
This project implements an end-to-end chat application using C++ with WinSock2 for network communication. It includes both client-side and server-side code to enable multiple clients to communicate with each other through a central server.

Table of Contents
Overview
Features
Requirements
Installation
Usage
Starting the Server
Starting the Client
Code Structure
Contributing
License
Overview
This project provides a simple chat application where multiple clients can connect to a server and exchange messages in real-time. Each client can send messages to the server, which will then broadcast these messages to all connected clients.

Features
Multiple client connections
Real-time message broadcasting
Simple and intuitive user interface for command-line interaction
Basic error handling for network operations
Requirements
Windows operating system
C++11 or later
WinSock2 library (ws2_32.lib)
Installation
Clone the Repository

bash
Copy code
git clone https://github.com/yourusername/end-to-end-chat-encryption.git
cd end-to-end-chat-encryption
Compile the Server Code

bash
Copy code
g++ -o server server.cpp -lws2_32
Compile the Client Code

bash
Copy code
g++ -o client client.cpp -lws2_32
Usage
Starting the Server
Open a command prompt or terminal.
Navigate to the directory where the server executable is located.
Run the server:
bash
Copy code
./server
The server will start and listen for incoming client connections on port 12345.
Starting the Client
Open a command prompt or terminal.
Navigate to the directory where the client executable is located.
Run the client:
bash
Copy code
./client
Enter your chat name when prompted.
Start sending messages. To quit, type quit and press Enter.
Code Structure
server.cpp: Contains the code for the server, including initialization, binding, listening for clients, and broadcasting messages to connected clients.
client.cpp: Contains the code for the client, including connecting to the server, sending messages, and receiving messages from the server.
Server Code Overview
Initialize WinSock

cpp
Copy code
bool Initialize() { /* ... */ }
Create and Bind Socket

cpp
Copy code
SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr));
Listen for Clients and Handle Connections

cpp
Copy code
listen(listenSocket, SOMAXCONN);
SOCKET clientSOCKET = accept(listenSocket, nullptr, nullptr);
thread t1(InteractWithClient, clientSOCKET, std::ref(clients));
Client Code Overview
Initialize WinSock

cpp
Copy code
bool Initialize() { /* ... */ }
Create and Connect Socket

cpp
Copy code
SOCKET S = socket(AF_INET, SOCK_STREAM, 0);
connect(S, reinterpret_cast<SOCKADDR*>(&serveraddr), sizeof(serveraddr));
Send and Receive Messages

cpp
Copy code
thread senderthread(SendMsg, S);
thread receiverthread(ReceiveMsg, S);
Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your improvements.
