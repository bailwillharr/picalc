default: main.c
	gcc -I/usr/local/include -L/usr/local/lib -lwiringPi main.c
