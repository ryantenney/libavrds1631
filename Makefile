OBJECTS = DS1631.o

CC = avr-gcc
CFLAGS = -Wall -pedantic
COPT = -Os

all : $(OBJECTS)
	@echo Build succeeded

clean :
	rm -f *.o *.a

DS1631.o : Wire.h

.cpp.o :
	$(CC) -c $(CFLAGS) $(COPT) $<
