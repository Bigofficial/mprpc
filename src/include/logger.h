#pragma once
#include "logqueue.h"
#include <string>
enum LogLevel{
    INFO, //普通信息
    ERROR,//错误信息
};

//mprpc框架日志系统
class Logger{
    public:
    //获取日志单例
    static Logger& GetInstance();
    void SetLogLevel(LogLevel level);//设置日志级别
    void Log(std::string msg);//记录日志
    private:
    int m_loglevel; //日志级别
    LockQueue<std::string> m_lckQue;//日志缓冲队列


    Logger();
    //失效拷贝构造(防止拷贝构造偷偷产生对象)
    Logger(const Logger&) = delete;
    Logger(Logger&) = delete;

};

// 定义宏 LOG_INFO("xxx %d %s", 20, "xxxx") 就可以直接宏就用了
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

#define LOG_ERR(logmsgformat, ...) \
    do \
    {  \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    } while(0) \

//VA_ARGS可变参数列表