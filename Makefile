
PACKAGE = ezscript
VERSION = 0.0.0

CFLAGS   += -Iinclude -DVERSION=\"$(VERSION)\" -DPACKAGE=\"$(PACKAGE)\"
LDFLAGS  += 
FLEX     ?= flex
BISON    ?= bison
prefix   ?= /usr/local

headers         = $(wildcard include/*.h)
libezscript_src = $(wildcard libezscript/*.c) libezscript/ezlexer.c libezscript/ezparser.c
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

.PHONY: all check clean install uninstall dist

all: lib$(PACKAGE)$(LIBEXT)

libezscript.a: libezscript.dll

libezscript$(LIBEXT): $(patsubst %.c, %.o, $(libezscript_src))
	$(CC) -shared $(CFLAGS) $(LDFLAGS) $^ -Wl,--out-implib=libezscript.a -o $@

check: ezscript-test$(EXEEXT)	
	./ezscript-test$(EXEEXT)
  
ezscript-test$(EXEEXT): $(patsubst %.c, %.o, $(test_src)) libezscript.a 
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean: 
	rm -f */*.o */*.d libezscript.a libezscript.dll ezscript-test$(EXEEXT)	
  
%.o : %.c
	$(CC) $(CFLAGS) -MD -c $< -o $(patsubst %.c, %.o, $<)
  
  
%.c: %.l
	$(FLEX) -o $@ --header-file=$(patsubst %.l,%.h,$^) $^  
    
%.c: %.y
	$(BISON) -o $@  $^

