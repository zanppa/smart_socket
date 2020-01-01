all: server client

LoRa.o: LoRa.c
	gcc -c LoRa.c -o LoRa.o -lpigpio -lrt -pthread -lm

server.o: server.c
	gcc -c server.c -o server.o -lpigpio -lrt -pthread -lm

client.o: client.c
	gcc -c client.c -o client.o -lpigpio -lrt -pthread -lm

server: LoRa.o server.o
	gcc -o server server.o LoRa.o -lpigpio -lrt -pthread -lm

client: LoRa.o client.o
	gcc -o client client.o LoRa.o -lpigpio -lrt -pthread -lm
