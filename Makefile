# EasyGIF, easy Makefile
# No, really. This is really basic.

# COMPILER
CC=g++ -std=c++11

# DEPENDENCIES
## CURLPP
CURL_DEV=`pkg-config --cflags curlpp`
CURL_LIB=`pkg-config --libs curlpp`

## CRYPTO++
CRYP_DEV=`pkg-config --cflags libcrypto++`
CRYP_LIB=`pkg-config --libs libcrypto++`

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

test_save: image_frame.o image_grabber.o image_saver.o src/test_save.cpp
	$(CC) -o./build/bin/test_save ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./src/test_save.cpp $(XCB_LIB) $(SFML_LIB)

test_gif: gif_enc.o image_frame.o image_gif.o image_grabber.o src/test_gif.cpp
	$(CC) -o./build/bin/test_gif ./build/obj/gif_enc.o ./build/obj/image_frame.o ./build/obj/image_gif.o ./build/obj/image_grabber.o ./src/test_gif.cpp $(XCB_LIB) $(SFML_LIB)

image_saver.o: src/img/image_saver.cpp
	$(CC) -c -o./build/obj/image_saver.o ./src/img/image_saver.cpp $(SFML_DEV)

image_grabber.o: src/img/image_grabber.cpp
	$(CC) -c -o./build/obj/image_grabber.o ./src/img/image_grabber.cpp $(XCB_DEV)

image_gif.o: src/img/image_gif.cpp
	$(CC) -c -o./build/obj/image_gif.o ./src/img/image_gif.cpp

image_frame.o: src/img/image_frame.cpp
	$(CC) -c -o./build/obj/image_frame.o ./src/img/image_frame.cpp $(SFML_DEV)

gif_enc.o: src/gifenc/gif.cpp
	$(CC) -c -o./build/obj/gif_enc.o ./src/gifenc/gif.cpp

test_b64: b64.o src/test/test_b64.cpp
	$(CC) -o./build/bin/test_b64 ./build/obj/b64.o ./src/test/test_b64.cpp
b64.o: src/sec/b64.cpp
	$(CC) -c -o./build/obj/b64.o ./src/sec/b64.cpp

test_imgur:
	$(CC) -o./build/bin/test_imgur ./src/test/upload_imgur.cpp $(CURL_DEV) $(CURL_LIB)

test_upload: md5.o gyazo.o src/test_upload.cpp
	$(CC) -o./build/bin/test_upload ./build/obj/md5.o ./build/obj/gyazo.o ./src/test_upload.cpp $(CRYP_LIB) $(CURL_LIB)
md5.o: src/sec/md5.cpp
	$(CC) -c -o./build/obj/md5.o ./src/sec/md5.cpp $(CRYP_DEV)
gyazo.o: src/net/gyazo.cpp
	$(CC) -c -o./build/obj/gyazo.o ./src/net/gyazo.cpp $(CURL_DEV)

rmdirs:
	rm ./build --recursive

mkdirs:
	mkdir -p ./build/bin
	mkdir -p ./build/obj
