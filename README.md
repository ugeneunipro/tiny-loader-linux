# tiny-loader-linux
Simple tiny loader of UGENE installer.

# Download curl
```
download curl sources and unzip them to directory curl
``

### Build curl
```bash
./configure --enable-static --disable-ftp --disable-file --disable-ldap --disable-ldaps --disable-rtsp --disable-proxy --disable-dict --disable-telnet --disable-tftp --disable-pop3 --disable-imap --disable-smb --disable-smtp --disable-gopher --disable-manual --disable-ipv6 --disable-sspi --disable-crypto-auth --disable-ntlm-wb --disable-tls-srp --disable-unix-sockets --disable-soname-bump --without-winssl --without-darwinssl --without-ssl --without-gnutls --without-polarssl --without-mbedtls --without-cyassl --without-nss --without-axtls --without-ca-bundle --without-ca-path --without-ca-fallback --without-libpsl --without-libmetalink --without-libssh2 --without-librtmp --without-winidn --without-libidn --without-nghttp2 --without-zsh-functions-dir --without-zlib
make
```
### Build loader
```bash
g++ -L . -lX11 -lcurlMY -lrt -pthread -std=gnu++11 -I ./include/ tinyLoader.cpp tinyLoaderSplashScreen.cpp libcurlMY.a -o tinyLoader
```

# build.sh
```
see build.sh for actual options
```
