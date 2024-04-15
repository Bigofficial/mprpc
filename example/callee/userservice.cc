#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
using namespace fixbug;

/*

userservice原来是本地服务，提供了两个进程内的本地方法
login和getfriendlist
*/

// 使用在RPC服务发布端（rpc服务提供端）
class UserService : public UserServiceRpc
{

public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "login" << std::endl;
        std::cout << "name" << name
                  << "pwd" << pwd << std::endl;
        return true;
    }

    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "register" << std::endl;
        std::cout << "id" << id << "name" << name
                  << "pwd" << pwd << std::endl;
        return true;
    }

    // 重写基类UserServiceRpc的虚函数 这里加上了google::protobuf
    // 这些方法都是框架直接调用的
    /*
    1.callee ===> Login(LoginRequest) => muduo => callee
    2. callee ===> Login(LoginRequest) =>交到下面这个Login方法上

    closure也是抽象类，框架实现run方法
    */
    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {

        // 框架给业务上报了请求参数LoginRequest，业务获取相应数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();
        // 做本地业务
        bool login_result = Login(name, pwd);

        // 把响应写入
        response->set_success(login_result);
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errmsg(""); // 没有错误
        code->set_errcode(0);
        response->set_success(login_result);

        // 执行回调操作  执行相应对象序列化和忘了发送（都是框架完成
        done->Run();
    }

    void Register(google::protobuf::RpcController *controller,
                  const ::fixbug::RegisterRequest *request,
                  ::fixbug::RegisterResponse *response,
                  ::google::protobuf::Closure *done)
    {
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();
        bool ret = Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 框架初始化操作  读配置文件
    MprpcApplication::Init(argc, argv);
    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点上
    // 作为一个服务应该很多人调用，要做到高并发
    RpcProvider provider;
    // 把UserService对象发布到rpc节点上
    provider.NotifyService(new UserService());

    // 启动一个rpc服务发布节点，run以后进程进入阻塞状态，等待远程rpc调用请求
    provider.Run();
    return 0;
}