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

## BINARY FILE DIRECTORY
BIN_DIR=./build/bin/

#Test DIRECTORY
TEST_DIR=./src/test

## OBJECT FILE PATHS
### UTILITY OBJECTS
UT_OBJ=$(OBJ_DIR)/converter.o $(OBJ_DIR)/xhelper.o

### IMAGE OBJECTS
IMG_OBJ=$(OBJ_DIR)/image_container.o $(OBJ_DIR)/image_frame.o $(OBJ_DIR)/image_grabber.o $(OBJ_DIR)/image_saver.o
IMG_GIF_OBJ=$(IMG_OBJ) $(OBJ_DIR)/image_gif.o $(OBJ_DIR)/gif_enc.o

### UI OBJECTS
UI_OBJ=$(OBJ_DIR)/region_picker.o

### APP OBJECTS
APP_OBJ=$(OBJ_DIR)/screenshot.o $(OBJ_DIR)/screenshot_static.o $(OBJ_DIR)/screenshot_gif.o

clean: rmdirs

all: mkdirs all_targets

debug:
	$(eval CC += $(DEBUG_FLAG))

all_targets: image_container.o image_frame.o image_gif.o image_grabber.o image_saver.o gif_enc.o region_picker.o screenshot.o xhelper.o converter.o

app: all_targets src/app/main.cpp
	$(CC) -o$(BIN_DIR)/easygif ./src/app/main.cpp $(APP_OBJ) $(IMG_GIF_OBJ) $(UI_OBJ) $(UT_OBJ) $(XCB_LIB) $(SFML_LIB)

test_build: mkdirs
	$(CC) -o$(BIN_DIR)/test_build ./src/test/test_build.cpp \
	$(XCB_DEV) $(XCB_LIB) \
	$(SFML_DEV) $(SFML_LIB) \
	$(CURL_DEV) $(CURL_LIB)

test_save: converter.o xhelper.o image_container.o image_frame.o image_grabber.o image_saver.o src/test/test_save.cpp
	$(CC) -o$(BIN_DIR)/test_save $(UT_OBJ) $(IMG_OBJ) ./src/test/test_save.cpp $(XCB_LIB) $(SFML_LIB)

test_gif: gif_enc.o image_frame.o image_gif.o image_grabber.o src/test/test_gif.cpp
	$(CC) -o$(BIN_DIR)/test_gif $(OBJ_DIR)/gif_enc.o ./build/obj/image_frame.o ./build/obj/image_gif.o ./build/obj/image_grabber.o ./src/test/test_gif.cpp $(XCB_LIB) $(SFML_LIB)

image_saver.o: src/img/image_saver.cpp
	$(CC) -c -o$(OBJ_DIR)/image_saver.o ./src/img/image_saver.cpp $(SFML_DEV)

image_grabber.o: src/img/image_grabber.cpp
	$(CC) -c -o$(OBJ_DIR)/image_grabber.o ./src/img/image_grabber.cpp $(XCB_DEV)

image_gif.o: src/img/image_gif.cpp
	$(CC) -c -o$(OBJ_DIR)/image_gif.o ./src/img/image_gif.cpp

image_container.o: src/img/image_container.cpp
	$(CC) -c -o$(OBJ_DIR)/image_container.o ./src/img/image_container.cpp $(SFML_DEV)

image_frame.o: src/img/image_frame.cpp
	$(CC) -c -o$(OBJ_DIR)/image_frame.o ./src/img/image_frame.cpp $(SFML_DEV)

gif_enc.o: src/gifenc/gif.cpp
	$(CC) -c -o$(OBJ_DIR)/gif_enc.o ./src/gifenc/gif.cpp

xhelper.o: src/util/xhelper.cpp
	$(CC) -c -o$(OBJ_DIR)/xhelper.o ./src/util/xhelper.cpp $(XCB_DEV)

converter.o: src/util/converter.cpp
	$(CC) -c -o$(OBJ_DIR)/converter.o ./src/util/converter.cpp $(SFML_DEV)

virtual_desktop.o: src/ui/virtual_desktop.cpp
	$(CC) -c -o$(OBJ_DIR)/virtual_desktop.o ./src/ui/virtual_desktop.cpp $(XCB_DEV)

region_picker.o: src/ui/region_picker.cpp
	$(CC) -c -o$(OBJ_DIR)/region_picker.o ./src/ui/region_picker.cpp $(XCB_DEV) $(SFML_DEV)

screenshot.o: src/app/screenshot/screenshot.cpp src/app/screenshot/screenshot_static.cpp src/app/screenshot/screenshot_gif.cpp
	$(CC) -c -o$(OBJ_DIR)/screenshot.o ./src/app/screenshot/screenshot.cpp $(XCB_DEV) $(SFML_DEV)
	$(CC) -c -o$(OBJ_DIR)/screenshot_static.o ./src/app/screenshot/screenshot_static.cpp $(XCB_DEV) $(SFML_DEV)
	$(CC) -c -o$(OBJ_DIR)/screenshot_gif.o ./src/app/screenshot/screenshot_gif.cpp $(XCB_DEV) $(SFML_DEV)

test_vdesktop: converter.o image_container.o image_frame.o image_grabber.o image_saver.o xhelper.o virtual_desktop.o src/test/test_vdesktop.cpp
	$(CC) $(UT_OBJ) $(OBJ_DIR)/image_container.o ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./build/obj/virtual_desktop.o ./src/test/test_vdesktop.cpp -o$(BIN_DIR)/test_vdesktop $(XCB_LIB) $(SFML_LIB)

test_picker: converter.o image_container.o image_frame.o image_grabber.o image_saver.o xhelper.o region_picker.o src/test/test_picker.cpp
	$(CC) $(UT_OBJ) $(OBJ_DIR)/image_container.o ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./build/obj/region_picker.o ./src/test/test_picker.cpp -o$(BIN_DIR)/test_picker $(XCB_LIB) $(SFML_LIB)

#NETWORKING AND SECURITY TEST BUILDS

test_b64: b64.o src/test/test_b64.cpp
	$(CC) -o$(BIN_DIR)/test_b64 $(OBJ_DIR)/b64.o ./src/test/test_b64.cpp

test_conn: conncheck.o b64.o md5.o image_upload.o src/test/test_conn.cpp
	$(CC) -o$(BIN_DIR)/test_conn $(OBJ_DIR)/conncheck.o ./build/obj/b64.o ./build/obj/md5.o ./build/obj/image_upload.o ./src/test/test_conn.cpp $(CURL_LIB) $(CRYP_LIB)

test_uploaders: stringmod.o filestuff.o create_header.o conncheck.o b64.o image_upload.o md5.o gyazo.o
	$(CC) -o$(BIN_DIR)/test_uploaders $(OBJ_DIR)/stringmod.o ./build/obj/filestuff.o ./build/obj/create_header.o ./build/obj/conncheck.o ./build/obj/b64.o ./build/obj/image_upload.o ./build/obj/md5.o ./build/obj/gyazo.o ./src/test/test_uploaders.cpp $(CURL_LIB) $(CRYP_LIB)

test_headers: stringmod.o create_header.o
	$(CC) -o$(BIN_DIR)/test_headers $(OBJ_DIR)/stringmod.o $(OBJ_DIR)/create_header.o $(TEST_DIR)/test_headers.cpp $(CURL_LIB)

#IMAGE UPLOADER TESTING
test_gyazo: stringmod.o filestuff.o create_header.o conncheck.o b64.o image_upload.o md5.o gyazo.o
	$(CC) -o$(BIN_DIR)/test_gyazo $(OBJ_DIR)/stringmod.o ./build/obj/filestuff.o ./build/obj/create_header.o ./build/obj/conncheck.o ./build/obj/b64.o ./build/obj/image_upload.o ./build/obj/md5.o ./build/obj/gyazo.o ./src/test/test_gyazo.cpp $(CURL_LIB) $(CRYP_LIB)

stringmod.o: src/sec/stringmod.cpp
	$(CC) -c -o$(OBJ_DIR)/stringmod.o ./src/sec/stringmod.cpp
filestuff.o: src/net/filestuff.cpp
	$(CC) -c -o$(OBJ_DIR)/filestuff.o ./src/net/filestuff.cpp
create_header.o: src/net/create_header.cpp
	$(CC) -c -o$(OBJ_DIR)/create_header.o ./src/net/create_header.cpp $(CURL_DEV)
conncheck.o: src/net/conncheck.cpp
	$(CC) -c -o$(OBJ_DIR)/conncheck.o ./src/net/conncheck.cpp $(CURL_DEV)
b64.o: src/sec/b64.cpp
	$(CC) -c -o$(OBJ_DIR)/b64.o ./src/sec/b64.cpp
image_upload.o: src/net/uploaders/image_upload.cpp
	$(CC) -c -o$(OBJ_DIR)/image_upload.o ./src/net/uploaders/image_upload.cpp $(CURL_DEV)
md5.o: src/sec/md5.cpp
	$(CC) -c -o$(OBJ_DIR)/md5.o ./src/sec/md5.cpp $(CRYP_DEV)
gyazo.o: src/net/uploaders/gyazo.cpp
	$(CC) -c -o$(OBJ_DIR)/gyazo.o ./src/net/uploaders/gyazo.cpp $(CURL_DEV)

rmdirs:
	rm ./build --recursive

mkdirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
