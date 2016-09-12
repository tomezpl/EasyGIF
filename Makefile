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

# BUILD FLAGS
## DEBUG FLAG
DEBUG_FLAG = -D EZGIF_DEBUG

clean: rmdirs

all: mkdirs all_targets

debug:
	$(eval CC += $(DEBUG_FLAG))

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


virtual_desktop.o: src/ui/virtual_desktop.cpp
	$(CC) -c -o./build/obj/virtual_desktop.o ./src/ui/virtual_desktop.cpp $(XCB_DEV)

test_vdesktop: image_grabber.o virtual_desktop.o src/test_vdesktop.cpp
	$(CC) ./build/obj/image_grabber.o ./build/obj/virtual_desktop.o ./src/test_vdesktop.cpp -o./build/bin/test_vdesktop $(XCB_LIB)

#NETWORKING AND SECURITY TEST BUILDS

test_b64: b64.o src/test/test_b64.cpp
	$(CC) -o./build/bin/test_b64 ./build/obj/b64.o ./src/test/test_b64.cpp

test_conn: conncheck.o b64.o md5.o image_upload.o src/test/test_conn.cpp
	$(CC) -o./build/bin/test_conn ./build/obj/conncheck.o ./build/obj/b64.o ./build/obj/md5.o ./build/obj/image_upload.o ./src/test/test_conn.cpp $(CURL_LIB) $(CRYP_LIB)

test_uploaders: stringmod.o filestuff.o create_header.o conncheck.o b64.o image_upload.o md5.o gyazo.o
	$(CC) -o./build/bin/test_uploaders ./build/obj/stringmod.o ./build/obj/filestuff.o ./build/obj/create_header.o ./build/obj/conncheck.o ./build/obj/b64.o ./build/obj/image_upload.o ./build/obj/md5.o ./build/obj/gyazo.o ./src/test/test_uploaders.cpp $(CURL_LIB) $(CRYP_LIB)

stringmod.o: src/sec/stringmod.cpp
	$(CC) -c -o./build/obj/stringmod.o ./src/sec/stringmod.cpp
filestuff.o: src/net/filestuff.cpp
	$(CC) -c -o./build/obj/filestuff.o ./src/net/filestuff.cpp
create_header.o: src/net/create_header.cpp
	$(CC) -c -o./build/obj/create_header.o ./src/net/create_header.cpp $(CURL_DEV)
conncheck.o: src/net/conncheck.cpp
	$(CC) -c -o./build/obj/conncheck.o ./src/net/conncheck.cpp $(CURL_DEV)
b64.o: src/sec/b64.cpp
	$(CC) -c -o./build/obj/b64.o ./src/sec/b64.cpp
image_upload.o: src/net/image_upload.cpp
	$(CC) -c -o./build/obj/image_upload.o ./src/net/image_upload.cpp $(CURL_DEV)
md5.o: src/sec/md5.cpp
	$(CC) -c -o./build/obj/md5.o ./src/sec/md5.cpp $(CRYP_DEV)
gyazo.o: src/net/gyazo.cpp
	$(CC) -c -o./build/obj/gyazo.o ./src/net/gyazo.cpp $(CURL_DEV)

rmdirs:
	rm ./build --recursive

mkdirs:
	mkdir -p ./build/bin
	mkdir -p ./build/obj
