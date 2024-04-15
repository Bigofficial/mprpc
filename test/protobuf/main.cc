
#include "test.pb.h"
#include <iostream>
#include <string>

using namespace fixbug;

int main1(){

    //封装了login请求对象数据
    LoginRequest req;
    req.set_name("zhangsan");
    req.set_pwd("123456");

    //对象数据序列化成 转成string发送 可以.c_str()转成char*
    std::string send_str;
    if(req.SerializeToString(&send_str)){
        std::cout << send_str << std::endl;
    }


    //反序列化一个login请求对象
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str)){
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }
    return 0;
}

int main(){
    // LoginResponse rsp;
    // ResultCode *rc = rsp.mutable_result(); //假如在定义了一个message1用的就是mutable
    // rc->set_errcode(1);
    // rc->set_errmsg("登录处理失败");

    GetFriendListsResponse rsp;
    ResultCode *rc = rsp.mutable_result();

    User *user1 = rsp.add_friend_list();
    user1->set_name("zs");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    std::cout << rsp.friend_list_size() << std::endl; //获得好友个数

}