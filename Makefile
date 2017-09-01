
PACKAGE = ezscript
VERSION = 0.0.0

CFLAGS   += -Iinclude -DVERSION=\"$(VERSION)\" -DPACKAGE=\"$(PACKAGE)\"
LDFLAGS  += 
prefix   ?= /usr/local

headers         = $(wildcard include/*.h)
libezscript_src = $(wildcard libezscript/*.c)
ezscript_src    = $(wildcard ezscript/*.c)
test_src        = $(wildcard test/*.c)

ifeq ($(OS),Windows_NT)
  EXEEXT = .exe  
  LIBEXT = .dll
else
  EXEEXT =
  LIBEXT = .so  
endif

.PHONY: all check clean install uninstall dist

all: lib$(PACKAGE)$(LIBEXT)

libezscript.a: libezscript.dll

libezscript$(LIBEXT): $(patsubst %.cpp, %.o, $(libezscript_src))
	$(CC) -shared -fPIC $(CFLAGS) $(LDFLAGS) $^ -Wl,--out-implib=libezscript.a -o $@

check: ezscript-test$(EXEEXT)	
	./ezscript-test$(EXEEXT)
  
ezscript-test$(EXEEXT): $(patsubst %.c, %.o, $(test_src)) libezscript.a 
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean: 
	rm -f */*.o */*.d libezscript.a libezscript.dll ezscript-test$(EXEEXT)	
  
%.o : %.c
	$(CC) $(CFLAGS) -MD -c $< -o $(patsubst %.c, %.o, $<)
  