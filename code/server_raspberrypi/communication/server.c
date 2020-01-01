#include <time.h>
#include <stdlib.h>
#include <signal.h>

// For unix sockets
#include <unistd.h>
#include <sys/socket.h>
//#include <sys/un.h>
//#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "LoRa.h"

// Define this to have verbose (human-readable)
// Otherwise only the responses are printed TAB separated
//#define VERBOSE_OUTPUT

#define RECEIVE_TIMEOUT		(2)	// Wait maximum of n seconds
#define MAX_RETRIES		(3)	// Maximum amount of transmit retries if no answer is received

#define SOCKET_PORT		(2222)

#define POLL_INTERVAL		(1*60)	// Status poll interval (over RF)

volatile unsigned char tx_done = 0;
volatile unsigned char rx_done = 0;

void tx_f(txData *tx) {
#ifdef VERBOSE_OUTPUT
	printf("tx done \n");
#endif
	tx_done = 1;
}

void rx_f(rxData *rx){
	char time_string[64] = {0};
	time_t time_val = (rx->buf[0]<<24)+(rx->buf[1]<<16)+(rx->buf[2]<<8)+rx->buf[3];
	unsigned int user_data = (rx->buf[11]<<24)+(rx->buf[12]<<16)+(rx->buf[13]<<8)+rx->buf[14];
	struct tm *timeinfo = localtime(&time_val);

	strftime(time_string, 63, "%d.%m.%Y %H:%M:%S", timeinfo);

#ifdef VERBOSE_OUTPUT
	printf("rx done \n");
	printf("  CRC error: %d\n", rx->CRC);
	printf("  Data size: %d\n", rx->size);
	printf("  RSSI: %d dBm\n", rx->RSSI);
	printf("  SNR: %f dB\n", rx->SNR);
	printf("Data:\n");
	printf("  Time: %u (%s)\n", time_val, time_string);
	printf("  Status: 0x%x\n", rx->buf[4]);
	printf("  SNR: 0x%x (%f dB)\n", rx->buf[5], (float)rx->buf[5] * 0.25);
	printf("  RSSI 0x%x (%f dBm)\n", rx->buf[6], (float)rx->buf[6] - 164.0);	// LF port only (~434 MHz)
	printf("  Channel: 0x%x\n", rx->buf[7]);
	printf("  Power: 0x%x\n", rx->buf[8]);
	printf("  Relays: 0x%x\n", rx->buf[9]);
	printf("  Temperature: %d\n", (signed char)rx->buf[10]);
	printf("  PKG: 0x%x\n", rx->buf[15]);
#else
	printf("%u\t%s\t%f\t%d\t%f\t%f\t%02x\t%d\t%#10x\t", time_val, time_string, rx->SNR, rx->RSSI, (float)rx->buf[5] * 0.25,
		(float)rx->buf[6] - 164.0, rx->buf[9], (signed char)rx->buf[10], user_data);
		
	for(int i=0;i<16;i++)
		printf("%02x", rx->buf[i]);
	
	fflush(stdout);	// Probably going to a file...
#endif

	rx_done = 1;
}


struct _rfCmd {
	unsigned char command;
	unsigned char flags;
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned long time1;
	unsigned long time2;
	unsigned char reserved3;
	unsigned char reserved4;
	unsigned char reserved5;
	unsigned char pkg_num;
} rfCmd;

struct _schedEvent {
	unsigned char mode;
	unsigned long time;
} events[255];


#define FIFO_LEN	255

static LoRa_ctl modem;

void cleanup(int sig);


int comm(LoRa_ctl *rf, char *txbuf, char *rxbuf)
{
	static unsigned char pkg_num = 1;

	// Update package number
	txbuf[15] = ((pkg_num & 0x1F) << 3);	// Pkg num
	pkg_num++;
	if(pkg_num > 0x1F) pkg_num = 1;

#ifdef VERBOSE_OUTPUT
	printf("CMD: ");
	for(int i=0;i<16;i++)
		printf("0x%x ", txbuf[i]);
	printf("\n");
#else
	for(int i=0;i<16;i++)
		printf("%02x", txbuf[i]);
	printf("\t");
#endif

	rf->tx.data.buf = txbuf;
	rf->tx.data.size = 16;

	for(int i=0; i<MAX_RETRIES; i++)
	{
		tx_done = 0;
		txbuf[15] &= 0xF8;		// Clear retransmit count
		txbuf[15] |= (i+1) & 0x07;	// Update retransmit counter

		// Transmit (wake up first)
		LoRa_send(&modem);

		//printf("Tsym: %f\n", modem.tx.data.Tsym);
		//printf("Tpkt: %f\n", modem.tx.data.Tpkt);
		//printf("payloadSymbNb: %u\n", modem.tx.data.payloadSymbNb);
		//printf("Send timestamp %u\n", rfCmd.time1);
		while(!tx_done);

		modem.tx.data.size = 0;

		// Receive
		rx_done = 0;
		memset(rxbuf, 0, 255);	// Clear receive buffer
		LoRa_receive(&modem);
#ifdef VERBOSE_OUTPUT
		printf("Receive...\n");
#endif
		// LoRa_receive(&modem);	// Once should be enough

		time_t stop_time = time(NULL) + RECEIVE_TIMEOUT;

		// Wait until timeout or message received
		while(time(NULL) < stop_time && !rx_done);
#ifndef VERBOSE_OUTPUT
		printf("\n");
#endif
		if(rx_done) break;		// Got a reply, no more retries

#ifdef VERBOSE_OUTPUT
		printf("Receive timeout, retrying...\n");
#endif
	}

	// Sleep
	LoRa_stop_receive(&modem);

#ifdef VERBOSE_OUTPUT
	if(rx_done)
	{
		printf("Data: ");
		for(int i=0;i<16;i++)
			printf("0x%x ", rxbuf[i]);
		printf("\n");
	} else {
		printf("ERROR! Receive timeout!\n");
	}

	printf("end\n");
#endif

	return rx_done;		// Return whether we got a reply or not
}

void create_command(char *txbuf, unsigned char command, unsigned char flags, unsigned long time1, unsigned long time2)
{
	memset(txbuf, 0, 16);

	txbuf[0] = command;
	txbuf[1] = flags;
	txbuf[4] = (time1 >> 24) & 0xFF;
	txbuf[5] = (time1 >> 16) & 0xFF;
	txbuf[6] = (time1 >> 8) & 0xFF;
	txbuf[7] = time1 & 0xFF;
	txbuf[8] = (time2 >> 24) & 0xFF;
	txbuf[9] = (time2 >> 16) & 0xFF;
	txbuf[10] = (time2 >> 8) & 0xFF;
	txbuf[11] = time2 & 0xFF;
}


int main(void)
{
	char fifobuf[FIFO_LEN] = {0};

	char txbuf[255] = {0};
	char rxbuf[255] = {0};

	unsigned int event_count = 0;

	// Socket communication
	int listfd;
	int connfd;

	time_t previous_time, next_time, current_time;

	// Clean up and exit after ctrl+c
	if(signal(SIGINT, cleanup) == SIG_ERR)
		printf("\ncan't catch SIGINT\n");

	srand(time(NULL));

	// Create interprocess communication socket
	//listfd = socket(AF_UNIX, SOCK_STREAM, 0);
	//if(listfd == -1)
	//	exit(-1);

	// Create localhost inet socket instead of unix socket
	listfd = socket(AF_INET, SOCK_STREAM, 0);	// Non-blocking
	if(listfd < 0)
		exit(-1);

	// Set the socket as non-blocking
	fcntl(listfd, F_SETFL, fcntl(listfd, F_GETFL, 0) | O_NONBLOCK);

	// Unix socket
	//struct sockaddr_un saddr = {AF_UNIX, "pistoke"};
	//bind(listfd, (struct sockaddr *)&saddr, sizeof(saddr));

	// Inet socket
	struct sockaddr_in saddr, cli_addr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(SOCKET_PORT);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// Only allow local connections
	memset(saddr.sin_zero, '\0', sizeof(saddr.sin_zero));  
	bind(listfd, (struct sockaddr *) &saddr, sizeof(saddr));

	listen(listfd, 10);	// TODO: 10 ? Max 10 connections? Maybe limit to 1?

	// Initialize the LoRa module
	//See for typedefs, enumerations and there values in LoRa.h header file
	modem.spiCS = 0;//Raspberry SPI CE pin number
	modem.rx.callback = rx_f;
	modem.rx.data.buf = rxbuf;
	modem.tx.callback = tx_f;
	modem.tx.data.buf = txbuf;
	modem.tx.data.size = 1;//Payload len
	modem.eth.preambleLen = 6;
	modem.eth.bw = BW62_5;//Bandwidth 62.5KHz
	modem.eth.sf = SF8;//Spreading Factor 8 seems to work
	modem.eth.ecr = CR8;//Error coding rate CR4/8
	modem.eth.CRC = 1;//Turn on CRC checking
	modem.eth.freq = 434000000;// 434.000 MHz
	modem.eth.resetGpioN = 17;//GPIO17 on lora RESET pin
	modem.eth.dio0GpioN = 4;//GPIO4 on lora DIO0 pin to control Rxdone and Txdone interrupts
	modem.eth.outPower = OP14;//Output power 14 dBm = 25 mW
	modem.eth.powerOutPin = PA_BOOST;//Power Amplifire pin
	modem.eth.AGC = 1;//Auto Gain Control
	modem.eth.OCP = 240;// 45 to 240 mA. 0 to turn off protection
	modem.eth.implicitHeader = 0;//Explicit header mode
	modem.eth.syncWord = 0x12;	// 0x12 = default
	//For detail information about SF, Error Coding Rate, Explicit header, Bandwidth, AGC, Over current protection and other features refer to sx127x datasheet https://www.semtech.com/uploads/documents/DS_SX1276-7-8-9_W_APP_V5.pdf

	// Initialize the modem
	LoRa_begin(&modem);

	// Go to sleep
	LoRa_stop_receive(&modem);

	next_time = time(NULL) - 1;

#ifndef VERBOSE_OUTPUT
	printf("TX_CMD\tclientTimestamp\tTime\tserverSNR\tserverRSSI\tclientSNR\tclientRSSI\tRelays\tTemperature\tUserdata\tRX_DATA\n");
#endif

	// Main loop
	while(1)
	{
		current_time = time(NULL);
		if(current_time > next_time)
		{
			// Do a status query
			create_command(txbuf, 100, 0, 0, 0);
                        if(comm(&modem, txbuf, rxbuf))	// Send the status query
                        {
				// Got a result, link is online
				// Check the current time
				time_t remote_time = (rxbuf[0]<<24)+(rxbuf[1]<<16)+(rxbuf[2]<<8)+rxbuf[3];
				if(abs(remote_time - current_time) > 30)
				{
					// If there is > 30 seconds difference, set a new time
					current_time = time(NULL);
					create_command(txbuf, 120, 0, current_time, 0);
					comm(&modem, txbuf, rxbuf);
					// No need to check the reply... will check again in fwe minutes...
				}
                        }

			// Check link again in 5 minutes
			next_time = current_time + POLL_INTERVAL;
		}

		sleep(0.01);

		// Check if socket has connection
		connfd = accept(listfd, NULL, NULL);	// Do not block
		if(connfd < 0)
		{
			// No pending connections => continue
			continue;
		}

		// Read max 80 bytes from the fifo (command is max 16 bytes)
		memset(fifobuf, 0, FIFO_LEN);
		read(connfd, fifobuf, 16);

		// Sending NULL as the first byte equals quit
		if(fifobuf[0] == 0xFF)
		{
			break;
		}
		else if(fifobuf[0] == 250)	// Read scheduler
		{
			event_count = 0;

			// Read the scheduler maximum event count
			create_command(txbuf, 105, 0, 0, 0);	// 105 = Scheduler size
			if(comm(&modem, txbuf, rxbuf))
			{
				event_count = rxbuf[14];	// Custom data contains n of events
			}

#ifdef VERBOSE_OUTPUT
			printf("Scheduler has %d events\n", event_count);
#endif

			// Read status of all events
			for(int i=0; i < event_count; i++)
			{
#ifdef VERBOSE_OUTPUT
				printf("Querying event %d\n", i);
#endif
				create_command(txbuf, 106, i & 0xFF, 0, 0);	// 106 = request event type
				if(comm(&modem, txbuf, rxbuf))
				{
#ifdef VERBOSE_OUTPUT
					printf("Succesfully got mode\n", i);
#endif
					events[i].mode = rxbuf[14];		// custom data is event type
				} else continue;

				create_command(txbuf, 107, i & 0xFF, 0, 0);	// 107 = request event time
				if(comm(&modem, txbuf, rxbuf))
				{
#ifdef VERBOSE_OUTPUT
					printf("Succesfully got time\n", i);
#endif
					events[i].time = (rxbuf[11] << 24) + (rxbuf[12] << 16) + (rxbuf[13] << 8) + rxbuf[14];		// custom data is event time
				}

#ifdef VERBOSE_OUTPUT
				printf("  Event %2d: 0x%x %d\n", i, events[i].mode, events[i].time);
#endif
			}

			// Create a standard reply buffer and send it first
			memset(fifobuf, 0, FIFO_LEN);
			fifobuf[4] = 250;		// Reply with the same command if
			fifobuf[14] = event_count;	// Event count in user data

			// Send through socket
			write(connfd, fifobuf, 16);

			// Package events and pass into FIFO
			memset(fifobuf, 0, FIFO_LEN);
			int fifo_pos = 0;
			for(int i=0; i<event_count;i++)
			{
				fifobuf[fifo_pos++] = events[i].mode;
				fifobuf[fifo_pos++] = (events[i].time >> 24) & 0xFF;
				fifobuf[fifo_pos++] = (events[i].time >> 16) & 0xFF;
				fifobuf[fifo_pos++] = (events[i].time >> 8) & 0xFF;
				fifobuf[fifo_pos++] = events[i].time & 0xFF;
			}

			// Send through socket
			write(connfd, fifobuf, fifo_pos);
			close(connfd);
		}
		else	// All other messages go directly through
		{

			// TODO: Maybe add secret or authentication or encryption??

			// Copy fifo directly to transmit buffer
			memcpy(txbuf, fifobuf, 16);

			// Do radio communication
			comm(&modem, txbuf, rxbuf);

			// Package received data
			memset(fifobuf, 0, FIFO_LEN);
			memcpy(fifobuf, rxbuf, 16);

			// Send through socket
			write(connfd, fifobuf, 16);
			close(connfd);
		}

		// Next automatic update is delayed
		next_time = current_time + POLL_INTERVAL;

		// To prevent too frequent messages, wait for 1 second
		sleep(1);
	}

	cleanup(0);

	return 0;
}

void cleanup(int sig)
{
	printf("Cleaning up...\n");
	LoRa_end(&modem);

	// TODO: Close the socket?
}
