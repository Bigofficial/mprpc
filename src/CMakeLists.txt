
#aux_source_directory(. SRC_LIST)
set(SRC_LIST mprpcapplication.cc mprpcconfig.cc rpcheader.pb.cc rpcprovider.cc mprpcchannel.cc mprpccontroller.cc logger.cc zookeeperutil.cc)
#编译为静态库 这里使用的是muduo的静态库，假如编译为动态库有问题
#add_library(mprpc SHARED ${SRC_LIST}) #编译动态库
add_library(mprpc  ${SRC_LIST})

target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)