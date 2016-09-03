# EasyGIF
## GIF capture app
### About
EasyGIF is an application that allows the user to capture their screen (or a portion of the screen), and save the captured frames as GIF animations, which are commonly used on the Web.
It is written primarily with GNU/Linux systems in mind, so the code relies heavily on the X window system. It also allows for easy sharing of the saved GIFs by uploading them to Gyazo.
### Dependencies
Currently, EasyGIF uses `xcb`, `xcb-image`, `xcb-util`, `libcrypto++`, `libcurl`, `curlpp`, and `sfml`.
On Debian-based systems (including Ubuntu), assuming you're using `apt` as your package manager, you can get them using `apt-get install libxcb*-dev libcrypto++-dev libcurl-dev libcurlpp-dev libsfml-dev`. Don't forget that your system may require you to have root privileges (highly likely), so you will have to use `su` or `sudo` to use the command as root.

Also big thanks to [Marcel Rodrigues (lecram)](https://github.com/lecram "Marcel's GitHub") for writing [gifenc](https://github.com/lecram/gifenc "gifenc, a GIF encoder written in C99"), which saved us a lot of time.
### Building
The full app can be built using `make all`, which will compile the source into object files and then link everything into a final executable file. As for single targets (such as testing the build environment with test_build), please take a look at `Makefile`.
