#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>

MprpcConfig MprpcApplication::m_config;

void ShowArgsHelp()
{
    std::cout << "format: command -i <configfile>" << std::endl;
}
void MprpcApplication::Init(int argc, char **argv)
{

    std::cout << "init " << std::endl;
    if (argc < 2)
    {
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }
    int c = 0;
    std::string config_file;
    // while ((c = getopt(argc, argv, "i:")) != -1) {...}: 使用 getopt 函数解析命令行参数。getopt 函数会逐个解析命令行参数，并返回每个参数的简称（如 -i），如果没有参数或解析完毕，则返回 -1。在这里，函数会解析以 i: 为格式的参数，表示选项 i 后面需要接一个参数值。

    // i: 表示选项 -i。这个字符表示程序支持一个选项 -i。
    //  这个符号告诉 getopt 函数，选项 -i 后面需要接一个参数值。
    while ((c = getopt(argc, argv, "i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
        case '?':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            //./my_program -i
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }
    std::cout << "before load " << std::endl;
    // 开始加载配置文件
    m_config.loadConfigFile(config_file.c_str());
    std::cout << "after load " << std::endl;
    std::cout << "rpc server ip: " << m_config.Load("rpcserverip") << std::endl;
    std::cout << "rpc server port: " << m_config.Load("rpcserverport") << std::endl;
    std::cout << "zk server ip: " << m_config.Load("zookeeperip") << std::endl;
    std::cout << "zk server port: " << m_config.Load("zookeeperport") << std::endl;
}
MprpcApplication &MprpcApplication::GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig &MprpcApplication::GetConfig()
{
    return m_config;
}