#ifndef LOGGER_H_
#define LOGGER_H_
#include <Windows.h>
#include <stdio.h>
#include "CommandDefine.h"
/*
    * 类名：Logger
    * 作用：提供写日志功能，支持多线程，支持可变形参数操作，支持写日志级别的设置
    * 接口：SetLogLevel：设置写日志级别
            TraceKeyInfo：忽略日志级别，写关键信息
            TraceError：写错误信息
            TraceWarning：写警告信息
            TraceInfo：写一般信息
*/
class Logger
{
public:
    //默认构造函数
    Logger();
    //构造函数
    Logger(const char * strLogPath, EnumLogLevel nLogLevel = EnumLogLevel::LogLevelNormal);
    //析构函数
    virtual ~Logger();
public:
    //写关键信息
    void TraceKeyInfo(const char * strInfo, ...);
    //写错误信息
    void TraceError(const char* strInfo, ...);
    //写警告信息
    void TraceWarning(const char * strInfo, ...);
    //写一般信息
    void TraceInfo(const char * strInfo, ...);
    //设置写日志级别
    void SetLogLevel(EnumLogLevel nLevel);
private:
    //写文件操作
    void Trace(const char * strInfo);
    //获取当前系统时间
    char * GetCurrentTime();
    //创建日志文件名称
    void GenerateLogName();
    //创建日志路径
    void CreateLogPath();
private:
    //写日志文件流
    FILE * m_pFileStream;
    //写日志级别
    EnumLogLevel m_nLogLevel;
    //日志的路径
    char m_strLogPath[MAX_STR_LEN];
    //日志的名称
    char m_strCurLogName[MAX_STR_LEN];
    //线程同步的临界区变量
    CRITICAL_SECTION m_cs;
};
 
#endif