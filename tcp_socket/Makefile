all: ServerEnd ClientEnd

ServerEnd: ServerEnd.o

ClientEnd: ClientEnd.o

%.o: %.c
	$(CC) -W -Wall -c $<

clean:
	rm -f ServerEnd ClientEnd ServerEnd.o ClientEnd.o
