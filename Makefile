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

## XLIB
X11_DEV=`pkg-config --cflags x11 xcomposite xfixes`
X11_LIB=`pkg-config --libs x11 xcomposite xfixes`

## CAIRO
CAIRO_DEV=`pkg-config --cflags cairo cairo-xlib`
CAIRO_LIB=`pkg-config --libs cairo cairo-xlib`

## GTK+
GTK_DEV=`pkg-config --cflags gtk+-3.0 gmodule-2.0`
GTK_LIB=`pkg-config --libs gtk+-3.0 gmodule-2.0`

# BUILD FLAGS
## DEBUG FLAG
DEBUG_FLAG = -g
EZDEBUG_FLAG = -D EZGIF_DEBUG

## INSTALL FLAG
INSTALL_FLAG = -D EZGIF_APP_INSTALLED

# SHORTCUTS/ALIASES
## OBJECT FILE DIRECTORY
OBJ_DIR=./build/obj

## BINARY FILE DIRECTORY
BIN_DIR=./build/bin

#Test DIRECTORY
TEST_DIR=./src/test
#src directories
NET_DIR=./src/net
UPL_DIR=./src/net/uploaders
SEC_DIR=./src/sec

## OBJECT FILE PATHS
### UTILITY OBJECTS
UT_OBJ=$(OBJ_DIR)/converter.o $(OBJ_DIR)/xhelper.o $(OBJ_DIR)/file_system.o

### IMAGE OBJECTS
IMG_OBJ=$(OBJ_DIR)/image_container.o $(OBJ_DIR)/image_frame.o $(OBJ_DIR)/image_grabber.o $(OBJ_DIR)/image_saver.o
IMG_GIF_OBJ=$(IMG_OBJ) $(OBJ_DIR)/image_gif.o $(OBJ_DIR)/gif_enc.o

### UI OBJECTS
UI_OBJ=$(OBJ_DIR)/region_picker.o $(OBJ_DIR)/overlay.o $(OBJ_DIR)/rect_overlay.o

### APP OBJECTS
APP_OBJ=$(OBJ_DIR)/screenshot.o $(OBJ_DIR)/screenshot_static.o $(OBJ_DIR)/screenshot_gif.o

clean: rmdirs

all: mkdirs all_targets

set_install_flag:
	$(eval CC += $(INSTALL_FLAG))

install: set_install_flag mkdirs app
	cp ./build/bin/easygif /usr/bin/
	mkdir -p /usr/lib/easygif
	cp ./ui /usr/lib/easygif/ --recursive

debug:
	$(eval CC += $(DEBUG_FLAG))

all_targets: image_container.o image_frame.o image_gif.o image_grabber.o image_saver.o gif_enc.o overlay.o rect_overlay.o region_picker.o screenshot.o xhelper.o converter.o file_system.o

app: all_targets src/app/main.cpp
	$(CC) -o$(BIN_DIR)/easygif ./src/app/main.cpp $(APP_OBJ) $(IMG_GIF_OBJ) $(UI_OBJ) $(UT_OBJ) $(XCB_LIB) $(SFML_LIB) $(GTK_DEV) $(GTK_LIB) $(X11_LIB) $(CAIRO_LIB)

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

file_system.o: src/util/file_system.cpp
	$(CC) -c -o$(OBJ_DIR)/file_system.o ./src/util/file_system.cpp

virtual_desktop.o: src/ui/virtual_desktop.cpp
	$(CC) -c -o$(OBJ_DIR)/virtual_desktop.o ./src/ui/virtual_desktop.cpp $(XCB_DEV)

region_picker.o: src/ui/region_picker.cpp
	$(CC) -c -o$(OBJ_DIR)/region_picker.o ./src/ui/region_picker.cpp $(XCB_DEV) $(SFML_DEV) $(X11_DEV) $(CAIRO_DEV)

overlay.o: src/ui/overlay.cpp
	$(CC) -c -o$(OBJ_DIR)/overlay.o ./src/ui/overlay.cpp $(X11_DEV) $(CAIRO_DEV)

rect_overlay.o: src/ui/rect_overlay.cpp
	$(CC) -c -o$(OBJ_DIR)/rect_overlay.o ./src/ui/rect_overlay.cpp $(X11_DEV) $(CAIRO_DEV)

screenshot.o: src/app/screenshot/screenshot.cpp src/app/screenshot/screenshot_static.cpp src/app/screenshot/screenshot_gif.cpp
	$(CC) -c -o$(OBJ_DIR)/screenshot.o ./src/app/screenshot/screenshot.cpp $(XCB_DEV) $(SFML_DEV)
	$(CC) -c -o$(OBJ_DIR)/screenshot_static.o ./src/app/screenshot/screenshot_static.cpp $(XCB_DEV) $(SFML_DEV)
	$(CC) -c -o$(OBJ_DIR)/screenshot_gif.o ./src/app/screenshot/screenshot_gif.cpp $(XCB_DEV) $(SFML_DEV)

test_vdesktop: converter.o image_container.o image_frame.o image_grabber.o image_saver.o xhelper.o virtual_desktop.o src/test/test_vdesktop.cpp
	$(CC) $(UT_OBJ) $(OBJ_DIR)/image_container.o ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./build/obj/virtual_desktop.o ./src/test/test_vdesktop.cpp -o$(BIN_DIR)/test_vdesktop $(XCB_LIB) $(SFML_LIB)

test_picker: converter.o image_container.o image_frame.o image_grabber.o image_saver.o xhelper.o region_picker.o src/test/test_picker.cpp
	$(CC) $(UT_OBJ) $(OBJ_DIR)/image_container.o ./build/obj/image_frame.o ./build/obj/image_grabber.o ./build/obj/image_saver.o ./build/obj/region_picker.o ./src/test/test_picker.cpp -o$(BIN_DIR)/test_picker $(XCB_LIB) $(SFML_LIB)

#IMAGE UPLOADER TESTING
uploader_all: sec_all.o net_all.o upl_all.o
test_gyazo: $(TEST_DIR)/uploaders/test_gyazo.cpp sec_stringmod.o sec_md5.o net_conncheck.o upl_image_upload.o net_create_header.o
	$(CC) -o $(BIN_DIR)/test_gyazo $(GYAZO_OBJS) $(TEST_DIR)/uploaders/test_gyazo.cpp $(CURL_LIB) $(CRYP_LIB)
test_imgur_anon: $(TEST_DIR)/uploaders/test_imgur.cpp sec_stringmod.o upl_image_upload.o net_create_header.o net_filestuff.o upl_imgur_anon.o
	$(CC) -o $(BIN_DIR)/test_imgur_anon $(IMGUR_ANON_OBJS) $(TEST_DIR)/uploaders/test_imgur.cpp $(CURL_LIB)

#net/uploaders
IMAGE_UPLOAD_INP=$(UPL_DIR)/image_upload.cpp
IMAGE_UPLOAD_OBJ=$(OBJ_DIR)/upl_image_upload.o
IMGUR_ANON_INP=$(UPL_DIR)/imgur_anon.cpp
IMGUR_ANON_OBJ=$(OBJ_DIR)/upl_imgur_anon.o
IMGUR_ANON_OBJS=$(STRINGMOD_OBJ) $(IMAGE_UPLOAD_OBJ) $(CREATE_HEADER_OBJ) $(FILESTUFF_OBJ) $(IMGUR_ANON_OBJ)
GYAZO_INP=$(UPL_DIR)/gyazo.cpp
GYAZO_OBJ=$(OBJ_DIR)/upl_gyazo.o
GYAZO_OBJS=$(STRINGMOD_OBJ) $(MD5_OBJ) $(CONNCHECK_OBJ) $(IMAGE_UPLOAD_OBJ) $(CREATE_HEADER_OBJ) $(GYAZO_OBJ)

upl_all.o: upl_image_upload.o upl_imgur_anon.o upl_gyazo.o
#sec_md5.o sec_b64.o net_conncheck.o
upl_image_upload.o: $(IMAGE_UPLOAD_INP)
	$(CC) -c -o$(IMAGE_UPLOAD_OBJ) $(IMAGE_UPLOAD_INP) $(CURL_DEV)
#sec_stringmod.o net_conncheck.o upl_image_upload.o net_create_header.o ./src/json.hpp net_filestuff.o
upl_imgur_anon.o: $(IMGUR_ANON_INP)
	$(CC) -c -o$(IMGUR_ANON_OBJ) $(IMGUR_ANON_INP)
#sec_stringmod.o sec_md5.o net_conncheck.o upl_image_upload.o net_create_header.o
upl_gyazo.o: $(GYAZO_INP)
	$(CC) -c -o$(GYAZO_OBJ) $(GYAZO_INP) $(CURL_DEV)
#net
FILESTUFF_INP=$(NET_DIR)/filestuff.cpp
FILESTUFF_OBJ=$(OBJ_DIR)/net_filestuff.o
CREATE_HEADER_INP=$(NET_DIR)/create_header.cpp
CREATE_HEADER_OBJ=$(OBJ_DIR)/net_create_header.o
CONNCHECK_INP=$(NET_DIR)/conncheck.cpp
CONNCHECK_OBJ=$(OBJ_DIR)/net_conncheck.o

net_all.o: net_filestuff.o net_create_header.o net_conncheck.o
net_filestuff.o: $(FILESTUFF_INP)
	$(CC) -c -o$(FILESTUFF_OBJ) $(FILESTUFF_INP)
#sec_stringmod.o
net_create_header.o: $(CREATE_HEADER_INP)
	$(CC) -c -o$(CREATE_HEADER_OBJ) $(CREATE_HEADER_INP) $(CURL_DEV)
net_conncheck.o: $(CONNCHECK_INP)
	$(CC) -c -o$(CONNCHECK_OBJ) $(CONNCHECK_INP) $(CURL_DEV)

#sec
B64_INP=$(SEC_DIR)/b64.cpp
B64_OBJ=$(OBJ_DIR)/sec_b64.o
MD5_INP=$(SEC_DIR)/md5.cpp
MD5_OBJ=$(OBJ_DIR)/sec_md5.o
STRINGMOD_INP=$(SEC_DIR)/stringmod.cpp
STRINGMOD_OBJ=$(OBJ_DIR)/sec_stringmod.o

sec_all.o: sec_stringmod.o sec_b64.o sec_md5.o
sec_b64.o: $(B64_INP)
	$(CC) -c -o$(B64_OBJ) $(B64_INP)
#sec_stringmod.o
sec_md5.o: $(MD5_INP)
	$(CC) -c -o$(MD5_OBJ) $(MD5_INP) $(CRYP_DEV)
sec_stringmod.o: $(STRINGMOD_INP)
	$(CC) -c -o$(STRINGMOD_OBJ) $(STRINGMOD_INP)

rmdirs:
	rm ./build --recursive

mkdirs:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
