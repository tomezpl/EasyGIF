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
SFML_DEV=`pkg-config --cflags sfml-audio sfml-graphics sfml-network sfml-system sfml-window`
SFML_LIB=`pkg-config --libs sfml-audio sfml-graphics sfml-network sfml-system sfml-window`

## XCB
XCB_DEV=`pkg-config --cflags xcb xcb-image xcb-util`
XCB_LIB=`pkg-config --libs xcb xcb-image xcb-util`

# BUILD FLAGS
## DEBUG FLAG
DEBUG_FLAG = -D EZGIF_DEBUG

# SHORTCUTS/ALIASES
## OBJECT FILE DIRECTORY
OBJ_DIR=./build/obj/

## OBJECT FILE PATHS
### UTILITY OBJECTS
UT_OBJ=./build/obj/converter.o ./build/obj/xhelper.o

### IMAGE OBJECTS
IMG_OBJ=$(OBJ_DIR)/image_container.o $(OBJ_DIR)/image_frame.o $(OBJ_DIR)/image_grabber.o $(OBJ_DIR)/image_saver.o
IMG_GIF_OBJ=$(IMG_OBJ) $(OBJ_DIR)/image_gif.o

clean: rmdirs

all: mkdirs all_targets

debug:
	$(eval CC += $(DEBUG_FLAG))

test_build: mkdirs
	$(CC) -o./build/bin/test_build ./src/test_build.cpp \
	$(XCB_DEV) $(XCB_LIB) \
	$(SFML_DEV) $(SFML_LIB) \
	$(CURL_DEV) $(CURL_LIB)

test_save: converter.o xhelper.o image_container.o image_frame.o image_grabber.o image_saver.o src/test_save.cpp
	$(CC) -o./build/bin/test_save $(UT_OBJ) $(IMG_OBJ) ./src/test_save.cpp $(XCB_LIB) $(SFML_LIB)

test_gif: gif_enc.o image_frame.o image_gif.o image_grabber.o src/test_gif.cpp
	$(CC) -o./build/bin/test_gif ./build/obj/gif_enc.o ./build/obj/image_frame.o ./build/obj/image_gif.o ./build/obj/image_grabber.o ./src/test_gif.cpp $(XCB_LIB) $(SFML_LIB)

image_saver.o: src/img/image_saver.cpp
	$(CC) -c -o./build/obj/image_saver.o ./src/img/image_saver.cpp $(SFML_DEV)

image_grabber.o: src/img/image_grabber.cpp
	$(CC) -c -o./build/obj/image_grabber.o ./src/img/image_grabber.cpp $(XCB_DEV)

image_gif.o: src/img/image_gif.cpp
	$(CC) -c -o./build/obj/image_gif.o ./src/img/image_gif.cpp

image_container.o: src/img/image_container.cpp
	$(CC) -c -o./build/obj/image_container.o ./src/img/image_container.cpp $(SFML_DEV)

image_frame.o: src/img/image_frame.cpp
	$(CC) -c -o./build/obj/image_frame.o ./src/img/image_frame.cpp $(SFML_DEV)

gif_enc.o: src/gifenc/gif.cpp
	$(CC) -c -o./build/obj/gif_enc.o ./src/gifenc/gif.cpp

xhelper.o: src/util/xhelper.cpp
	$(CC) -c -o./build/obj/xhelper.o ./src/util/xhelper.cpp $(XCB_DEV)

converter.o: src/util/converter.cpp
	$(CC) -c -o./build/obj/converter.o ./src/util/converter.cpp $(SFML_DEV)

virtual_desktop.o: src/ui/virtual_desktop.cpp
	$(CC) -c -o./build/obj/virtual_desktop.o ./src/ui/virtual_desktop.cpp $(XCB_DEV)

region_picker.o: src/ui/region_picker.cpp
	$(CC) -c -o./build/obj/region_picker.o ./src/ui/region_picker.cpp $(XCB_DEV) $(SFML_DEV)

test_vdesktop: converter.o image_container.o image_frame.o image_grabber.o image_saver.o xhelper.o virtual_desktop.o src/test_vdesktop.cpp
	$(CC) $(UT_OBJ) ./build/obj/image_container.o ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./build/obj/virtual_desktop.o ./src/test_vdesktop.cpp -o./build/bin/test_vdesktop $(XCB_LIB) $(SFML_LIB)

test_picker: converter.o image_container.o image_frame.o image_grabber.o image_saver.o xhelper.o region_picker.o src/test_picker.cpp
	$(CC) $(UT_OBJ) ./build/obj/image_container.o ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./build/obj/region_picker.o ./src/test_picker.cpp -o./build/bin/test_picker $(XCB_LIB) $(SFML_LIB)

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
