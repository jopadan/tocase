GCC:= gcc
INSTALL:= install
RM:= rm
PREFIX:=/usr/local

all: tolower

tolower: tolower.o
	$(GCC) -o tolower tolower.o
tolower.o: tolower.c
	$(GCC) -c tolower.c
clean:
	$(RM) -rf hello.o hello

install: tolower
	$(INSTALL) -d $(DESTDIR)$(PREFIX)/bin
	$(INSTALL) -m 755 tolower $(DESTDIR)$(PREFIX)/bin
