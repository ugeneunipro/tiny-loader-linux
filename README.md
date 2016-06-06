# tiny-loader-linux
Simple tiny loader of UGENE installer.

# Build
g++ -L . -lX11 -lcurlMY -lrt -pthread -std=gnu++11 -I ./include/ tinyLoader.cpp tinyLoaderSplashScreen.cpp libcurlMY.a -o tinyLoader