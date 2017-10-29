
PACKAGE = ezscript
VERSION = 0.0.0

CFLAGS   += -Iinclude -DVERSION=\"$(VERSION)\" -DPACKAGE=\"$(PACKAGE)\"
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local

headers         = $(wildcard include/*.h)
libezscript_src = libezscript/ezparser.c libezscript/ezlexer.c $(wildcard libezscript/*.c) 
ezscript_src    = $(wildcard ezscript/*.c) 
test_src        = $(wildcard test/*.c)

ifeq ($(OS),Windows_NT)
  EXEEXT = .exe  
  LIBEXT = .dll
else
  EXEEXT =
  LIBEXT = .so  
  CFLAGS += -fPIC 
endif

.PHONY: all check clean devclean install uninstall dist

all: bin/libezscript$(LIBEXT) bin/ezscript$(EXEEXT)

lib/libezscript.a: bin/libezscript$(LIBEXT)

bin/libezscript$(LIBEXT): $(patsubst %.c, .obj/%.o, $(libezscript_src))
	mkdir -p bin 
	mkdir -p lib
	$(CC) -shared $(CFLAGS) $(LDFLAGS) $^ -Wl,--out-implib=lib/libezscript.a -o $@

bin/ezscript$(EXEEXT): $(patsubst %.c, .obj/%.o, $(ezscript_src)) lib/libezscript.a 
	mkdir -p bin 
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

repl: bin/ezscript$(EXEEXT)
	./bin/ezscript$(EXEEXT)

check: bin/ezscript-test$(EXEEXT)	
	./bin/ezscript-test$(EXEEXT)
  
bin/ezscript-test$(EXEEXT): $(patsubst %.c, .obj/%.o, $(test_src)) lib/libezscript.a 
	mkdir -p bin 
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean: 
	rm -rf .obj bin lib	

devclean: clean
	rm -f libezscript/ezparser.c libezscript/ezparser.h libezscript/ezlexer.c libezscript/ezlexer.h

.obj/%.o : %.c
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -MD -c $< -o $@	
  
%.c %.h: %.l
	$(FLEX) -o $@ --header-file=$(patsubst %.l,%.h,$^) $^  
    
%.c %.h: %.y
	$(BISON) -o $@  $^

ifneq "$(MAKECMDGOALS)" "clean"
-include $(patsubst %.c, .obj/%.d, $(libezscript_src))
-include $(patsubst %.c, .obj/%.d, $(ezscript_src))
-include $(patsubst %.c, .obj/%.d, $(test_src))
endif
