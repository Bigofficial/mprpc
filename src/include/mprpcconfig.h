#pragma once

#include <unordered_map>
#include <string>

//rpcserverip rpcserverport zookeeperip zookeeperport 
// 框架读取配置文件类
class MprpcConfig
{

public:
    //负责解析加载配置文件
    void loadConfigFile(const char *config_file);

    //查询配置项信息
    std::string Load(std::string key);

private:
    
    /* data 只init一次不要考虑线程安全 */
    std::unordered_map<std::string, std::string> m_configMap;


    //去掉字符串前后空格
    void Trim(std::string &src_buf);
};

