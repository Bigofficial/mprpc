#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <vector>
#include "logger.h"

class FriendService : public fixbug::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid)
    {
        std::cout << "do GetFriendsList service! userid:" << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("gao yang");
        vec.push_back("liu hong");
        vec.push_back("wang shuo");
        return vec;
    }

    // 重写基类方法
    void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendsListRequest* request,
                       ::fixbug::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t userid = request->userid();
        std::vector<std::string> friendsList = GetFriendsList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for (std::string &name : friendsList)
        {
            std::string *p = response->add_friends();
            *p = name;
        }
        done->Run();
    }
};

int main(int argc, char **argv)
{
    LOG_INFO("first log message!");

    // 框架初始化操作  读配置文件
    MprpcApplication::Init(argc, argv);
    // provider是一个rpc网络服务对象，把UserService对象发布到rpc节点上
    // 作为一个服务应该很多人调用，要做到高并发
    RpcProvider provider;
    // 把UserService对象发布到rpc节点上
    provider.NotifyService(new FriendService());
    LOG_ERR("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);
    // 启动一个rpc服务发布节点，run以后进程进入阻塞状态，等待远程rpc调用请求
    provider.Run();
    
    return 0;
}