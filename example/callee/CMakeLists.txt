

set(SRC_LIST  friendservice.cc ../friend.pb.cc)
#userservice.cc ../user.pb.cc
add_executable(provider ${SRC_LIST})

#连接框架代码
target_link_libraries(provider mprpc protobuf)