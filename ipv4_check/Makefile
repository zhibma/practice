.PHONY: all clean

all: ipv4_check

ipv4_check: main.o tool_fun.o ipv4_check.o
	gcc $^ -o $@

main.o: main.c ipv4_check.h tool_fun.h
	gcc -W -Wall -c $<

%.o: %.c
	gcc -W -Wall -c $<

clean:
	rm -f ipv4_check main.o tool_fun.o ipv4_check.o 
