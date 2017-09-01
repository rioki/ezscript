
PACKAGE = ezscript
VERSION = 0.0.0

CFLAGS   += -Iinclude -DVERSION=\"$(VERSION)\"
LDFLAGS  += 
prefix   ?= /usr/local

headers         = $(wildcard include/*.h)
libezscript_src = $(wildcard libezscript/*.c)
ezscript_src    = $(wildcard ezscript/*.c)
test_src        = $(wildcard test/*.c)

ifeq ($(MSYSTEM), MINGW32)
  EXEEXT = .exe  
  LIBEXT = .dll
else
  EXEEXT =
  LIBEXT = .so  
endif

check: test-$(PACKAGE)$(EXEEXT)	
	./test-$(PACKAGE)$(EXEEXT)
  
test-$(PACKAGE)$(EXEEXT): $(patsubst %.c, %.o, $(test_src))
	$(CC) $(CXXFLAGS) $(LDFLAGS) $^ $(test_libs) -o $@

clean: 
	rm -f */*.o */*.d test-$(PACKAGE)$(EXEEXT)	
  
%.o : %.c
	$(CC) $(CFLAGS) -MD -c $< -o $(patsubst %.c, %.o, $<)
  