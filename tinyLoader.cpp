#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <thread>

#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/utsname.h>

extern void drawSplashScreen(int *isDownloaded); //isDownloaded == 1, when package was downloaded

int numBitsSystem()
{

    long ret = -1;
    struct utsname u;
    if (ret == -1)
        ret = uname(&u);

    if (ret != -1) {
        if (strlen(u.machine) == 4 && u.machine[0] == 'i'
                && u.machine[2] == '8' && u.machine[3] == '6'){
                return 32;
            }
        if (strcmp(u.machine, "amd64") == 0          // Solaris
                || strcmp(u.machine, "x86_64") == 0){
                return 64;
            }
    }else{
        printf("ret==-1\n");
        return -1;
    }
    return -1;
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

bool downloadInstaller(const char *link, const char *outFileName){
    CURL *curl_handle;
    FILE *outFile;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init(); //init the curl session
    curl_easy_setopt(curl_handle, CURLOPT_URL, link); //set URL to get here
    //curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);  //Switch on full protocol/debug output while testing. Only for debug purpose.
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L); //disable progress meter, set to 0L to enable and disable debug output
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data); //send all data to this function
    outFile = fopen(outFileName, "wb"); //open the file
    if(outFile) {
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, outFile); //write the page body to this file handle
        curl_easy_perform(curl_handle); //get it!
        fclose(outFile); //close the header file
    }
    curl_easy_cleanup(curl_handle); //cleanup curl stuff
}

bool chmodFile(const char *outFileName){
  if (chmod (outFileName, 511) < 0)
    {
        fprintf(stderr, "error in chmod(%s, %s)\n", outFileName, "777");
        exit(1);
    }
}

bool executeInstaller(const char *outFileName){
    system(outFileName);
}

int main(int argc, char *argv[]){
    static const char *outFileName = "/tmp/ugeneInstaller";
    const char *link;
    int isDownloaded = 0;
    if (numBitsSystem() == 32){
        static const char *linkP = "http://ugene.net/downloads/installer_linux_x32";
        link = linkP;
    }else{
        static const char *linkP = "http://ugene.net/downloads/installer_linux_x64";
        link = linkP;
    }

    std::thread first (drawSplashScreen, &isDownloaded);

    downloadInstaller(link, outFileName);
    chmodFile(outFileName);
    isDownloaded = 1;
    first.join();
    system(outFileName);
    //remove temporary file
    unlink(outFileName);
    return 0;
}