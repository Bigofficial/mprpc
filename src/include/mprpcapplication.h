#pragma once
// 防止头文件被重复包含
#include "mprpcconfig.h"
#include "mprprcontroller.h"
#include "mprpcchannel.h"
// mprpc框架初始化类,基础类，设计为单例
class MprpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication &GetInstance();

    static MprpcConfig& GetConfig();
private:
    static MprpcConfig m_config;
    MprpcApplication(){}
    // 把和拷贝相关的都去掉 移动构造函数和拷贝构造函数的删除声明。
    MprpcApplication(const MprpcApplication &) = delete;
    MprpcApplication(MprpcApplication &&) = delete;
};