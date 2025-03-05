# minitalk
minitalk is a project from the 42 School curriculum that involves creating a simple data exchange program using UNIX signals in C. The objective is to develop a client-server system where the client sends messages to the server, and the server displays them. This project serves as an introduction to inter-process communication and UNIX signal handling.

## Description
The minitalk project requires the implementation of two separate executables:

Server: Listens for incoming messages and displays them upon receipt.  
Client: Sends a string message to the server, identified by its process ID.  
Communication between the client and server is achieved using UNIX signals, specifically SIGUSR1 and SIGUSR2. Each character in the message is transmitted as a sequence of these signals, representing its binary ASCII value.  

## Installation
To compile and use the minitalk programs:

1. Clone the Repository:
    ```bash
    git clone https://github.com/Pradene/minitalk.git
    ```
    
2. Build the project:
    ```bash
    make
    ```

This will generate the server and client executables.

## Usage
Starting the Server:

Run the server program in one terminal window. It will display its process ID (PID), which is required for the client to send messages.

```bash
./server
```

Sending a Message with the Client:

In another terminal window, use the client program to send a message to the server.  
Replace SERVER_PID with the actual PID displayed by the server.

```bash
./client SERVER_PID "Your message here"
```
    
For example:
```bash
./client 12345 "Hello, Server!"
```

The server should display:
```bash
Hello, Server!
```
