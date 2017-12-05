#!/bin/makefile

SRC=$(wildcard *.c)
OFILES=$(SRC:.c=.o)
LDFLAGS=-shared -fPIC
CFLAGS=-Wall -Wextra -pedantic -fPIC
EXEC=libPAIC.so
CC=gcc
IPATH=PAIC


all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $(LDFLAGS) $^ -o $(EXEC)
	mv $(EXEC) $(IPATH)/usr/lib
	cp *.h $(IPATH)/usr/include

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clear:
	rm *.o

package:
	dpkg-deb --build $(IPATH)

clean: clear

cleaner:
	rm *.o $(EXEC)

install:
	dpkg -i $(IPATH).deb

uninstall:
	dpkg --purge $(IPATH)
