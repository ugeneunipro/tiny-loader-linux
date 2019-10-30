# Tiny UGENE loader for linux
Simple tiny loader of UGENE installer.
It downloads `big` loader and executes them

# Download curl

download curl sources and unzip them to directory *`curl`*


# Build curl
```bash
PREFIX=`pwd`
cd curl
./configure --prefix=$PREFIX \
	--enable-static \
	--disable-ftp --disable-file --disable-ldap --disable-ldaps \
	--disable-rtsp --disable-proxy --disable-dict --disable-telnet \
	--disable-tftp --disable-pop3 --disable-imap --disable-smb \
	--disable-smtp --disable-gopher --disable-manual --disable-ipv6 \
	--disable-sspi --disable-crypto-auth --disable-ntlm-wb \
	--disable-tls-srp --disable-unix-sockets --disable-soname-bump \
	--without-winssl --without-darwinssl --without-ssl --without-gnutls \
	--without-polarssl --without-mbedtls --without-cyassl --without-nss \
	--without-axtls --without-ca-bundle --without-ca-path --without-ca-fallback \
	--without-libpsl --without-libmetalink --without-libssh2 --without-librtmp \
	--without-winidn --without-libidn --without-nghttp2 --without-zsh-functions-dir --without-zlib
make
make install
cd ..
```
# Build tiny loader for linux
```
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
```

# See build.sh for actual options
