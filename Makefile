# EasyGIF, easy Makefile
# No, really. This is really basic.

# COMPILER
CC=g++ -std=c++11

# DEPENDENCIES
## CURLPP
CURL_DEV=`pkg-config --cflags curlpp`
CURL_LIB=`pkg-config --libs curlpp`

## SFML
SFML_DEV=`pkg-config --cflags sfml-all`
SFML_LIB=`pkg-config --libs sfml-all`

## XLIB
XLIB_DEV=`pkg-config --cflags x11`
XLIB_LIB=`pkg-config --libs x11`

clean: rmdirs

all: mkdirs all_targets

test_build: mkdirs 
	$(CC) -o./build/bin/test_build ./src/test_build.cpp \
	$(XLIB_DEV) $(XLIB_LIB) \
	$(SFML_DEV) $(SFML_LIB) \
	$(CURL_DEV) $(CURL_LIB)

test_save: image_grabber.o image_saver.o src/test_save.cpp
	$(CC) -o./build/bin/test_save ./build/obj/image_grabber.o ./build/obj/image_saver.o ./src/test_save.cpp $(XLIB_LIB) $(SFML_LIB)

image_saver.o: src/ImageSaver.cpp
	$(CC) -c -o./build/obj/image_saver.o ./src/ImageSaver.cpp $(SFML_DEV)

image_grabber.o: src/ImageGrabber.cpp
	$(CC) -c -o./build/obj/image_grabber.o ./src/ImageGrabber.cpp $(XLIB_DEV)

rmdirs:
	rm ./build --recursive

mkdirs:
	mkdir -p ./build/bin
	mkdir -p ./build/obj
