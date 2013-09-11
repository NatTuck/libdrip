PREFIX := /usr/local
BASE   := $(shell readlink -f .)

CFLAGS  := -g -fPIC -std=gnu99 -I$(BASE)/include
LDFLAGS := -shared -fPIC
LDLIBS  := -lbsd -lgc

HDRS := $(wildcard include/drip/*.h)
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

LIB := libdrip.so

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(OBJS): $(SRCS) $(HDRS)

install:
	@bash -c 'if [ ! -e $(LIB) ]; then echo; echo "Error: Need to build first"; echo; exit 1; fi'
	mkdir -p $(PREFIX)/include/drip
	cp $(BASE)/include/drip/*.h $(PREFIX)/include/drip
	cp $(LIB) $(PREFIX)/lib

clean:
	rm -f $(LIB) $(OBJS)
	find examples -name Makefile -exec bash -c '(cd `dirname {}` && make clean)' \;

.PHONY: all clean install
