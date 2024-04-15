#include "logger.h"
#include <time.h>
#include <iostream>
// 类外实现静态成员函数不要加static
// 这里还有个bug，多线程你这里printf的时候，可能loglevel被改了
Logger &Logger::GetInstance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    // 启动专门写日志线程
    std::thread writeLogTask([&]()
                             {
        for(;;){
            //获取当前日志，然后获取日志信息，写入相应日志文件中
            time_t now = time(nullptr);
            tm *nowtm = localtime(&now);

            char file_name[128];
            sprintf(file_name, "%d-%d-%d-log.txt", nowtm->tm_year+1900, nowtm->tm_mon+1, nowtm->tm_mday);
            FILE *pf = fopen(file_name, "a+");
            if (pf == nullptr)
            {
                std::cout << "logger file : " << file_name << " open error!" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::string msg = m_lckQue.Pop();

            char time_buf[128] = {0};
            //这里还有个问题，你这里拿的loglevel是之后的，你push时的logLEVEL和取的时候的LOGLEVEL不一样 把level和信息都放入队列
            //队列改为pair的
            sprintf(time_buf, "%d:%d:%d =>[%s] ", 
                    nowtm->tm_hour, 
                    nowtm->tm_min, 
                    nowtm->tm_sec,
                    (m_loglevel == INFO ? "info" : "error"));
            msg.insert(0, time_buf);
            msg.append("\n");


            //每次写完信息就关文件，可以优化为（队列未空再关）
            fputs(msg.c_str(), pf);
            fclose(pf);

        } });
    // 设置分离线程
    writeLogTask.detach();
}
void Logger::SetLogLevel(LogLevel level) // 设置日志级别
{
    m_loglevel = level;
}

void Logger::Log(std::string msg) // 记录日志
{
    m_lckQue.Push(msg);
}