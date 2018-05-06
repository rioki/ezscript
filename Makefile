
PACKAGE = ezscript
VERSION = 0.0.0

CFLAGS   += -g -Iinclude -I.tmp/libezscript -DVERSION=\"$(VERSION)\" -DPACKAGE=\"$(PACKAGE)\" -Wpedantic -Wall
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local

headers         = $(wildcard include/*.h)
libezscript_src = $(wildcard libezscript/*.c)
test_src        = $(wildcard test/*.c)

ifeq ($(OS),Windows_NT)
  EXEEXT = .exe  
  LIBEXT = .dll
else
  EXEEXT =
  LIBEXT = .so  
  CFLAGS += -fPIC 
endif

.PHONY: all check clean install uninstall dist

all: bin/libezscript$(LIBEXT)

lib/libezscript.a: bin/libezscript$(LIBEXT)

bin/libezscript$(LIBEXT): $(patsubst %.c, .tmp/%.o, $(libezscript_src)) .tmp/libezscript/ezparser.o .tmp/libezscript/ezlexer.o
	mkdir -p bin
	mkdir -p lib
	$(CC) -shared $(CFLAGS) $(LDFLAGS) $^ -Wl,--out-implib=lib/libezscript.a -o $@

check: bin/eztest$(EXEEXT)	
	./bin/eztest$(EXEEXT)
  
bin/eztest$(EXEEXT): $(patsubst %.c, .tmp/%.o, $(test_src)) lib/libezscript.a
	mkdir -p bin
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean: 
	rm -rf .tmp lib bin

distclean: clean
	rm libezscript/ezparser.c libezscript/ezlexer.c libezscript/ezparser.h libezscript/ezlexer.h
  
.tmp/%.o : %.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -MD -c $< -o $@
  
%.c: %.l
	$(FLEX) -o $@ --header-file=$(patsubst %.c,%.h,$@) $^  
    
%.c: %.y
	$(BISON) -o $@  $^

    
ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.c, .tmp/%.d, $(libezscript_src))
-include .tmp/libezscript/ezlexer.d
-include .tmp/libezscript/ezparser.d
-include $(patsubst %.c, .tmp/%.d, $(test_src))
endif    
