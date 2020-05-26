#ifndef OPERLIBUSB_H
#define OPERLIBUSB_H
#include<stdio.h>
#include<libusb-1.0/libusb.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

class operlibusb
{
public:
    operlibusb(){};

    static bool HaveDevices(const char *vid,const char *pid);

private:
    static char* str2lower(char *str);

};

#endif // OPERLIBUSB_H
