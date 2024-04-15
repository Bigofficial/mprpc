
#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"
int main(int argc, char **argv)
{

    // 整个框架启动后，想使用mprpc框架来享受rpc服务调用，一定要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc, argv);

    // 掩饰调用远程发布的rpc方法login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法请求参数 LoginRequest继承了Message
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    // rpc方法响应
    fixbug::LoginResponse response;

    // 发起rpc
    stub.Login(nullptr, &request, &response, nullptr); // RpcChannel->RpcChannel::callMethod来集中做所有rpc方法调用参数序列化和网络发送

    // 一次rpc调用完成，读调用结果
    if (0 == response.result().errcode())
    {
        std::cout << "rpc login response success:" << response.success() << std::endl;
    }
    else
    {
        std::cout << "rpc login response error: " << response.result().errmsg() << std::endl;
    }

    // 演示调用远程发布的rpc方法register
    fixbug::RegisterRequest req;
    req.set_id(1123);
    req.set_name("rrrr");
    req.set_pwd("12345");
    fixbug::RegisterResponse rsp;

    stub.Register(nullptr, &req, &rsp, nullptr);

    if (0 == rsp.result().errcode())
    {
        std::cout << "rpc register response success:" << rsp.success() << std::endl;
    }
    else
    {
        std::cout << "rpc register response error: " << rsp.result().errmsg() << std::endl;
    }
    
    return 0;
}