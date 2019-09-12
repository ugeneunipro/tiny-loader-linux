# tiny-loader-linux
#Simple tiny loader of UGENE installer.

#export PATH=/usr/local/cuda/bin:/home/ichebyki/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/usr/lib/jvm/java-8-oracle/bin:/usr/lib/jvm/java-8-oracle/db/bin:/usr/lib/jvm/java-8-oracle/jre/bin:/usr/lib/jvm/java-8-oracle/bin:/usr/lib/jvm/java-8-oracle/db/bin:/usr/lib/jvm/java-8-oracle/jre/bin

PREFIX=`pwd`

### Build curl
if [ "_$1" = "_-build-curl" ]; then
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
