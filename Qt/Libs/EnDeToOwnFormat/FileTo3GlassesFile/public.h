#ifndef PUBLIC_H
#define PUBLIC_H
#pragma pack(push)
#pragma pack(1)//单字节对齐(Qt似乎是默认4字节对齐)
struct THREEGLASS_HEAD
{
    char manufacturer[8];
    short firmware_type;
    short bootloader_version;
    short application_version;
    short hardware_version;
    int firmware_size;
    char firmware_time[6];
    char user;
    char reserved[97];
    int crc;
};
#pragma pack(pop)

enum HADRWARE_VERION{
    D2C_D3C = 0x0000,
    D3 = 0x0001,
    D4 = 0x0002,
    DK1 = 0x0003,
    DKC4 = 0x0004,
    X1S = 0x0005,
    X1 = 0x100
};
#endif // PUBLIC_H
