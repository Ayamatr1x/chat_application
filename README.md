# chat_application

This project implements an end-to-end chat application using C++ with WinSock2 for network communication. It includes both client-side and server-side code for multiple clients to communicate through a central server.

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
This project provides a simple chat application where multiple clients connect to a server and exchange messages in real-time. Each client sends messages to the server, which broadcasts them to all connected clients.

Features
Multiple client connections
Real-time message broadcasting
Command-line interface
Basic error handling
Requirements
Windows OS
C++11 or later
WinSock2 library (ws2_32.lib)
