mysql_c: mysql_c.o
	gcc -lmysqlclient -L/usr/lib64/mysql $^ -o $@

%.o: %.c
	gcc -W -Wall -c $<

clean:
	rm -f mysql_c mysql_c.o
