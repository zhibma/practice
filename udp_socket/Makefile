.PHONY: all clean
all: udp_recv udp_send1 udp_send2

udp_recv: udp_recv.c
	gcc -W -Wall $< -o $@

udp_send1: udp_send.c
	gcc -W -Wall -DREMOTEIP=\"127.0.0.1\" $< -o $@

udp_send2: udp_send.c
	gcc -W -Wall -DREMOTEIP=\"192.168.56.100\" $< -o $@

clean:
	rm -f udp_recv udp_send1 udp_send2
