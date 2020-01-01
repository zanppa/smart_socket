# LoRa communication code
This directory contains code for communication between Raspberry PI server and the smart socket.

## Server
Server is the main program that handles the communication. It initializes the LoRa radio module and does periodic status updates even when there is no commands to be run.

The server also listens locally on TCP port 2222 for commands. The command structure is same that the socket expects (16 bytes, see the socket documentation), except some new commands:
 - 255 (dec) as the command bytes causes the server program to exit
 - 250 (dec) as the command byte makes the server automatically query information of all timed events. In this mode the server replies first with reply which has status byte as 250 (dec) and event count in user data byte 0. Then the server follows with 5 bytes for each event: mode, time byte 3 (MSB), time byte 2, time byte 1 and time byte 0 (LSB).
 
For all other commands, the server directly forwards the socket's reply to the client, see the socket documentation for reply structure.
 
## Client
The client is very simple command line tool to communicate with the smart socket via the server. It connects to localhost port 2222 and sends the requested message, and prints out the reply that is received.

The command line is:
```
client [command]
```

The supported commands are:
 - `quit`: cleanly stop the server process (send command 255)
 - `on`: turn relay 1 on immediately
 - `off`: turn relay 1 off immediately
 - `stat`: query status
 - `time`: set the socket time to match the client computer's time
 - `events`: query scheduled timing events and print them out
