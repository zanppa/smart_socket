# LoRa communication code
This directory contains code for communication between Raspberry PI server and the smart socket.

## Server
Server is the main program that handles the communication. It initializes the LoRa radio module and does periodic status updates even when there is no commands to be run.

The server also listens locally on TCP port 2222 for commands. The command structure is same that the socket expects (16 bytes, see the socket documentation), except some new commands:
 - 255 (dec) as the command bytes causes the server program to exit
 - 250 (dec) as the command byte makes the server automatically query information of all timed events. In this mode the server replies first with reply which has status byte as 250 (dec) and event count in user data byte 0. Then the server follows with 5 bytes for each event: mode, time byte 3 (MSB), time byte 2, time byte 1 and time byte 0 (LSB).
 
For all other commands, the server directly forwards the socket's reply to the client, see the socket documentation for reply structure.

The server prints out status reports of each message as well as the replies for periodic status queries. The example log can be seen [here](https://raw.githubusercontent.com/zanppa/smart_socket/master/docs/example_log.txt). The output is tab separated list of values:
```
TX_CMD  clientTimestamp Time    serverSNR       serverRSSI      clientSNR       clientRSSI      Relays  Temperature     Userdata        RX_DATA
``` 
 - TX_CMD is the 16 command bytes that were sent, hex formatted
 - clientTimestamp is the socket's current time
 - Time is the timestamp converted to human readable time (localtime, which timezone, I don't know)
 - serverSNR is the SNR of the reply message received by the server
 - serverRSSI is the RSSI of the reply message received by the server
 - clientSNR is the SNR of the command message received by the socket
 - clientRSSI is the RSSI of the command message received by the socket
 - Relays is the status of the socket's relays (bit 0=relay 1 on, bit 1=relay 2 on, bit 4=relay 1 turn-on pending, bit 5=relay 2 turn-on pending)
 - Temperature is the processor's temperature in degrees
 - Userdata is the reply's custom data as hex
 
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

## LoRa driver
The LoRa driver I use is by [YandievRuslan](https://github.com/YandievRuslan/sx1278-LoRa-RaspberryPi) except I added a few debug byte prints at the beginning and modified the LoRa module configuration to match what the socket expects.
