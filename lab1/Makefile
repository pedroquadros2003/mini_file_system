CC          := gcc
#CFLAGS      := -Wall -Wextra -pedantic -g $(shell pkg-config fuse3 --cflags)
CFLAGS      := -Wall `pkg-config fuse3 --cflags --libs` -o minifs_ro

minifs_ro:	minifs_ro.c Makefile
	$(CC) minifs_ro.c -o minifs_ro $(CFLAGS)

mount:		minifs_ro
	mkdir mnt/
	./minifs_ro -f mnt/
