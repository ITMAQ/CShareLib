#include "operlibusb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <QDebug>


bool operlibusb::HaveDevices(const char *vid,const char *pid)
{
    char RcVid[16] = "";
    char RcPid[16] = "";
    memset(RcVid,0,16);
    memset(RcPid,0,16);
    memcpy(RcVid,vid,strlen(vid));
    memcpy(RcPid,pid,strlen(pid));
    libusb_context *ctx;
    if(libusb_init(&ctx) != 0)return false;
    libusb_device **list;
    struct libusb_device_descriptor desc;

    libusb_device_handle *  handle = NULL;

    ssize_t num_devs, i;

    num_devs = libusb_get_device_list(ctx, &list);

    if (num_devs < 0)
        return false;//goto error;

    for (i = 0; i < num_devs; ++i) {
        libusb_device *dev = list[i];
        libusb_open(dev,&handle);

        libusb_get_device_descriptor(dev, &desc);

        str2lower(RcVid);
        str2lower(RcPid);
        char despid[16]="";
        sprintf(despid,"%04x",desc.idProduct);
        char desvid[16] = "";
        sprintf(desvid,"%04x",desc.idVendor);

        qDebug()<<"PID_VID:"<<despid<<"_"<<desvid;

        if((strcmp(RcVid,desvid) == 0) && (strcmp(RcPid,despid) == 0))return true;
    }


    return false;
}

char* operlibusb::str2lower(char *str)
{
    if(str == NULL)
  return NULL;
    char *p = str;
    while(*str){
        *str = tolower(*str);
        str++;
    }
    return p;
}
