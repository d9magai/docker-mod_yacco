##
##  Makefile -- Build procedure for fast3lpoad Apache module
##
##  This is a C++ module so things have to be handled a little differently.

#   the used tools
APXS=apxs
APACHECTL=apachectl

# Get all of apxs's internal values.
APXS_CC=`$(APXS) -q CC`
APXS_TARGET=`$(APXS) -q TARGET`
APXS_CFLAGS=`$(APXS) -q CFLAGS`
APXS_SBINDIR=`$(APXS) -q SBINDIR`
APXS_CFLAGS_SHLIB=`$(APXS) -q CFLAGS_SHLIB`
APXS_INCLUDEDIR=`$(APXS) -q INCLUDEDIR`
APXS_LD_SHLIB=`$(APXS) -q LD_SHLIB`
APXS_LIBEXECDIR=`$(APXS) -q LIBEXECDIR`
APXS_LDFLAGS_SHLIB=`$(APXS) -q LDFLAGS_SHLIB`
APXS_SYSCONFDIR=`$(APXS) -q SYSCONFDIR`
APXS_LIBS_SHLIB=`$(APXS) -q LIBS_SHLIB`

OBJ = mod_yacko.o getobject.o stringutils.o
TEST_OBJ = test.o  stringutils.o

#   the default target
all: mod_yacko.so

# compile the shared object file. use g++ instead of letting apxs call
# ld so we end up with the right c++ stuff. We do this in two steps,
# compile and link.

# compile
mod_yacko.o: mod_yacko.cpp
	g++ -c -fPIC -std=c++11 -I/usr/include/apr-1.0/ -I/usr/include/apr-1/ -I$(APXS_INCLUDEDIR) $(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB) -I/opt/awssdkcpp/include/ -DAWS_CUSTOM_MEMORY_MANAGEMENT -I. -Wall -o $@ $<
getobject.o: yacko/s3/getobject.cpp
	g++ -c -fPIC -std=c++11 -I/usr/include/apr-1.0/ -I/usr/include/apr-1/ -I$(APXS_INCLUDEDIR) $(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB) -I/opt/awssdkcpp/include/ -DAWS_CUSTOM_MEMORY_MANAGEMENT -I. -Wall -o $@ $< 
stringutils.o: yacko/utils/stringutils.cpp
	g++ -c -fPIC -std=c++11 -I/usr/include/apr-1.0/ -I/usr/include/apr-1/ -I$(APXS_INCLUDEDIR) $(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB) -I/opt/awssdkcpp/include/ -DAWS_CUSTOM_MEMORY_MANAGEMENT -I. -Wall -o $@ $< 
test.o: test/test.cpp
	g++ -c -std=c++11 -I/usr/include/apr-1.0/ -I/usr/include/apr-1/ -I$(APXS_INCLUDEDIR) $(APXS_CFLAGS) $(APXS_CFLAGS_SHLIB) -I/opt/awssdkcpp/include/ -DAWS_CUSTOM_MEMORY_MANAGEMENT -I. -Wall -o $@ $< 

# link
mod_yacko.so: $(OBJ)
	g++ -fPIC -shared -o $@ $(OBJ) $(APXS_LIBS_SHLIB) -L/opt/awssdkcpp/lib/ -laws-cpp-sdk-core -laws-cpp-sdk-s3

# install the shared object file into Apache 
install: all
	$(APXS) -i -a -n 'yacko' mod_yacko.so

testscript : $(TEST_OBJ)
	g++ -o $@ $(TEST_OBJ) $(APXS_LIBS_SHLIB) -L/opt/awssdkcpp/lib/ -lcrypto -laws-cpp-sdk-core
test: testscript 
	./testscript

# display the apxs variables
check_apxs_vars:
	@echo APXS_CC $(APXS_CC);\
	echo APXS_TARGET $(APXS_TARGET);\
	echo APXS_CFLAGS $(APXS_CFLAGS);\
	echo APXS_SBINDIR $(APXS_SBINDIR);\
	echo APXS_CFLAGS_SHLIB $(APXS_CFLAGS_SHLIB);\
	echo APXS_INCLUDEDIR $(APXS_INCLUDEDIR);\
	echo APXS_LD_SHLIB $(APXS_LD_SHLIB);\
	echo APXS_LIBEXECDIR $(APXS_LIBEXECDIR);\
	echo APXS_LDFLAGS_SHLIB $(APXS_LDFLAGS_SHLIB);\
	echo APXS_SYSCONFDIR $(APXS_SYSCONFDIR);\
	echo APXS_LIBS_SHLIB $(APXS_LIBS_SHLIB)

#   cleanup
clean:
	-rm -f *.so *.o *~ ./testscript

#   install and activate shared object by reloading Apache to
#   force a reload of the shared object file
reload: install restart

#   the general Apache start/restart/stop
#   procedures
start:
	$(APACHECTL) start
restart:
	$(APACHECTL) restart
stop:
	$(APACHECTL) stop
