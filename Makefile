#
#  There exist several targets which are by default empty and which can be 
#  used for execution of your targets. These targets are usually executed 
#  before and after some main targets. They are: 
#
#     .build-pre:              called before 'build' target
#     .build-post:             called after 'build' target
#     .clean-pre:              called before 'clean' target
#     .clean-post:             called after 'clean' target
#     .clobber-pre:            called before 'clobber' target
#     .clobber-post:           called after 'clobber' target
#     .all-pre:                called before 'all' target
#     .all-post:               called after 'all' target
#     .help-pre:               called before 'help' target
#     .help-post:              called after 'help' target
#
#  Targets beginning with '.' are not intended to be called on their own.
#
#  Main targets can be executed directly, and they are:
#  
#     build                    build a specific configuration
#     clean                    remove built files from a configuration
#     clobber                  remove all built files
#     all                      build all configurations
#     help                     print help mesage
#  
#  Targets .build-impl, .clean-impl, .clobber-impl, .all-impl, and
#  .help-impl are implemented in nbproject/makefile-impl.mk.
#
#  Available make variables:
#
#     CND_BASEDIR                base directory for relative paths
#     CND_DISTDIR                default top distribution directory (build artifacts)
#     CND_BUILDDIR               default top build directory (object files, ...)
#     CONF                       name of current configuration
#     CND_PLATFORM_${CONF}       platform name (current configuration)
#     CND_ARTIFACT_DIR_${CONF}   directory of build artifact (current configuration)
#     CND_ARTIFACT_NAME_${CONF}  name of build artifact (current configuration)
#     CND_ARTIFACT_PATH_${CONF}  path to build artifact (current configuration)
#     CND_PACKAGE_DIR_${CONF}    directory of package (current configuration)
#     CND_PACKAGE_NAME_${CONF}   name of package (current configuration)
#     CND_PACKAGE_PATH_${CONF}   path to package (current configuration)
#
# NOCDDL

# Environment 
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin

CC	=	gcc
DOXYGEN	=	doxygen
CFLAGS	=	-I./include/ -Wall -std=c11 -pedantic
LFLAGS	=	-lwiringPi
LIBLED	=	-L./lib/ledbar
SRC	=	./src/*.c
INCLUDE	=	./include/*.h
TEST	=	./tests/
BIN	=	./bin/
DOC	=	./doc/
OBJS	=	main
.PHONY: all
all: makeLedbar
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDE) $(LFLAGS)
	rm ./*.o
build: all
	$(CC) $(CFLAGS) -o Main ./src/main.c $(LIBLED)
.PHONY: makebin
makebin: 
	mkdir bin
#install: build installLedbar
#	mv ./Main ./bin/Main
#makeLedbar: ./include/ledbar.h ./src/ledbar.c
	#$(CC) $(CFLAGS) -fpic -c ./src/ledbar.c ./include/ledbar.h $(LFLAGS)
	#$(CC) -shared -o libledbar.so $^ $(LFLAGS)
#installLedbar: makeLedbar
#	mv ./libledbar.so ./lib/libledbar.so
.PHONY: test	
test:
	$(MAKE) -C $(TEST)
run: install
	./bin/Main
.PHONY: doc	
doc:
	$(DOXYGEN) Doxyfile
.PHONY: clean
clean:
	rm ./src/*.o
	rm ./*.o	
distclean: $(BIN)
	rm -rf ./bin/
	rm -rf ./doc/