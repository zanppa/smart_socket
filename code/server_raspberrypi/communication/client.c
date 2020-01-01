#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <unistd.h>
#include <sys/socket.h>
//#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SOCKET_PORT	(2222)

int main(int argc, char *argv[])
{
        //FILE *fp;
	char txbuf[255] = {0};
	unsigned long time1 = time(NULL);

	int sock, conn;

	srand(time(NULL));

	if(argc < 2) {
		printf("No arguments, quit\n");
		return 0;
	}

	printf("Opening socket...\n");
/*	struct sockaddr_un saddr = {AF_UNIX, "socket/pistoke"};
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if(sock < 0) {
		perror("socket");
		exit(1);
	}
	conn = connect(sock, (struct sockaddr *)&saddr, sizeof(saddr));
	if(conn < 0) {
		perror("connect");
		exit(1);
	}*/
	struct sockaddr_in saddr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SOCKET_PORT);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(saddr.sin_zero, '\0', sizeof(saddr.sin_zero));

	conn =connect(sock, (struct sockaddr *) &saddr, sizeof(saddr));
	if(conn < 0) {
		perror("connect");
		exit(1);
	}

	// Package data
	if(strcmp(argv[1], "quit") == 0)
		txbuf[0] = 0xFF;	// Quit the server process
	else if(strcmp(argv[1], "on") == 0)
		txbuf[0] = 1;	// Relay ON
	else if(strcmp(argv[1], "off") == 0)
		txbuf[0] = 2;	// Relay OFF
	else if(strcmp(argv[1], "stat") == 0)
		txbuf[0] = 100;	// Status query
	else if(strcmp(argv[1], "time") == 0)
		txbuf[0] = 120;	// Set the RTC to current time
	else if(strcmp(argv[1], "events") == 0)
		txbuf[0] = 250;	// Query events


	txbuf[3] = 0;
	txbuf[4] = (time1 >> 24) & 0xFF;
	txbuf[5] = (time1 >> 16) & 0xFF;
	txbuf[6] = (time1 >> 8) & 0xFF;
	txbuf[7] = time1 & 0xFF;
	txbuf[8] = (0 >> 24) & 0xFF;
	txbuf[9] = (0 >> 16) & 0xFF;
	txbuf[10] = (0 >> 8) & 0xFF;
	txbuf[11] = 0 & 0xFF;
	txbuf[15] = ((rand() & 0x1F) << 3) | 0x01;
	txbuf[16] = 0x00;	// End of message

	printf("Mess: ");
	for(int i=0;i<16;i++)
		printf("0x%x ", txbuf[i]);
	printf("\n");

	printf("Sending command...\n");

	if(write(sock, txbuf, 16) != 16)
		printf("Write did not write all bytes!\n");

	// Quit also the client if this was quit command
	if(txbuf[0] == 0xFF)
		return 0;

	memset(txbuf, 0, 80);
	printf("Reading...\n");

	if(read(sock, txbuf, 16) != 16)
		printf("Did not read 16 bytes!\n");

	char time_string[64] = {0};
	time_t time_val = (txbuf[0]<<24)+(txbuf[1]<<16)+(txbuf[2]<<8)+txbuf[3];
	struct tm *timeinfo = localtime(&time_val);
	strftime(time_string, 63, "%d.%m.%Y %H:%M:%S", timeinfo);

	printf("Data:\n");
	printf("  Time: %u (%s)\n", time_val, time_string);
	printf("  Status: 0x%x\n", txbuf[4]);
	printf("  SNR: 0x%x (%f dB)\n", txbuf[5], (float)txbuf[5] * 0.25);
	printf("  RSSI 0x%x (%f dBm)\n", txbuf[6], (float)txbuf[6] - 164.0);        // LF port only (~434 MHz)
	printf("  Channel: 0x%x\n", txbuf[7]);
	printf("  Power: 0x%x\n", txbuf[8]);
	printf("  Relays: 0x%x\n", txbuf[9]);
	printf("  Temperature: %d\n", (signed char)txbuf[10]);
	printf("  PKG: 0x%x\n", txbuf[15]);

	// Also events are incoming
	if(txbuf[4] == 250 && txbuf[14] != 0)
	{
		unsigned char n_events = txbuf[14];
		if(n_events > 51) n_events = 50;	// Make sure we dont exceed buffer size of 255

		memset(txbuf, 0, 255);
		printf("Reading %d events...\n", n_events);

		read(sock, txbuf, n_events * 5);

		int pointer = 0;
		for(int i=0;i<n_events;i++)
		{
			unsigned char mode = txbuf[pointer++];
			unsigned long time = txbuf[pointer++] << 24;
			time += txbuf[pointer++] << 16;
			time += txbuf[pointer++] << 8;
			time += txbuf[pointer++];
			printf("  Event %d: Mode %d, time %d\n", i+1, mode, time);
		}
	}

	close(sock);

	return(0);
}
