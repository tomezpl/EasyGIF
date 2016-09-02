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

## XCB
XCB_DEV=`pkg-config --cflags xcb xcb-image xcb-util`
XCB_LIB=`pkg-config --libs xcb xcb-image xcb-util`

clean: rmdirs

all: mkdirs all_targets

test_build: mkdirs 
	$(CC) -o./build/bin/test_build ./src/test_build.cpp \
	$(XCB_DEV) $(XCB_LIB) \
	$(SFML_DEV) $(SFML_LIB) \
	$(CURL_DEV) $(CURL_LIB)

test_save: image_grabber.o image_saver.o src/test_save.cpp
	$(CC) -o./build/bin/test_save ./build/obj/image_grabber.o ./build/obj/image_saver.o ./src/test_save.cpp $(XCB_LIB) $(SFML_LIB)

image_saver.o: src/ImageSaver.cpp
	$(CC) -c -o./build/obj/image_saver.o ./src/ImageSaver.cpp $(SFML_DEV)

image_grabber.o: src/ImageGrabber.cpp
	$(CC) -c -o./build/obj/image_grabber.o ./src/ImageGrabber.cpp $(XCB_DEV)

rmdirs:
	rm ./build --recursive

mkdirs:
	mkdir -p ./build/bin
	mkdir -p ./build/obj
