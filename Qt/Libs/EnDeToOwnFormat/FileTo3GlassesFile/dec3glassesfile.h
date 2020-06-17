#ifndef DEC3GLASSESFILE_H
#define DEC3GLASSESFILE_H
#include "public.h"
#include <QString>

class Dec3GlassesFile
{
public:
    Dec3GlassesFile();
    Dec3GlassesFile(QString Filename);
    void SetSrcFile(QString FileName);
    void SetOutPutFile(QString Filename);
    void GetHeader(THREEGLASS_HEAD &header);
    void Save2Output();

    // 检查文件是否被修改过
    bool CheckFileIsRight();
    // 获取制造商名称
    QString Getmanufacturer();
    // 获取硬件版本信息
    HADRWARE_VERION GetHardwareVersion();

private:
    QString OutPutFileName_;
    QString FileName_;
};

#endif // DEC3GLASSESFILE_H
