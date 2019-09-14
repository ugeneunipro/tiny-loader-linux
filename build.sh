# tiny-loader-linux
#Simple tiny loader of UGENE installer.

#export PATH=/usr/local/cuda/bin:/home/ichebyki/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/lib/jvm/java-8-oracle/bin:/usr/lib/jvm/java-8-oracle/db/bin:/usr/lib/jvm/java-8-oracle/jre/bin:/usr/lib/jvm/java-8-oracle/bin:/usr/lib/jvm/java-8-oracle/db/bin:/usr/lib/jvm/java-8-oracle/jre/bin

PREFIX=`pwd`

### Build curl
if [ "_$1" = "_-build-curl" ]; then
    ./build-curl.sh
fi

### Build curl
if [ "_$1" = "_-build-jpeglib" ]; then
    ./build-jpeglib.sh
fi

### Build loader
g++ \
    -L/usr/X11R6/lib \
    -L/usr/lib/x86_64-linux-gnu \
    -L. \
    -L./lib \
    -lX11 -lcurl -lrt \
    -pthread \
    -std=gnu++11 \
    -I ./include/ \
    -I /usr/include \
    tinyLoader.cpp \
    tinyLoaderSplashScreen.cpp \
    lib/libcurl.a \
    -lX11 \
    -o tinyLoader
