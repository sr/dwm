rm -f ./config.h && make clean && make && $(Xephyr :1 -screen 1024x768 2> /dev/null & sleep 1); HOME=./test-home-folder DISPLAY=:1.0 ./dwm
