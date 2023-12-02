#include <algorithm>
#include <atomic>
#include <boost/property_tree/ptree_fwd.hpp>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <sys/socket.h>
#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>
#include <unistd.h>
#include <vector>
#include "file_util.h"
#include "tcp_helper.h"

namespace pt = boost :: property_tree;

struct XMLParser{
    XMLParser(std::string file):file_name_{file}{}
    void ReadAll(){
        std::string path{"applications"};
        std::string value;
        pt::read_xml(file_name_,tree);
        for (const auto& nodes : tree.get_child(path)) {
            //std::cout << "node:" << nodes.first << "\n";
            for(const auto& child : nodes.second){
                //std::cout << "Tag:" << child.first << " value:" << child.second.data() << " cnt:" << cnt << "\n";
            }
        }
    }
    std::string ReadNode(const std::string& node){
        return node;
    }

 std::string file_name_;
 pt::ptree tree;
};

struct ConfigData{
    std::string application_name;
    std::uint8_t use_case;
    std::vector<uint8_t>channels;
    friend std::ostream& operator<< ( std::ostream &stream, ConfigData &sorter ) {
        stream << "\n";
        stream << "App:" << sorter.application_name << " use_case:" << static_cast<int>(sorter.use_case);
        stream << " channels: ";
        std::copy( sorter.channels.begin( ),sorter.channels.end( ), std::ostream_iterator<int>( stream,"," ) );
        stream << "\n";
        return stream;
    }
};


static const char* kChannelString[] = {"CAN1","CAN2","CAN3"};

class ConfigFileParser{
public:
    ConfigFileParser() = default; 
    bool Initialize(const char* path){
        bool result{false};
        try {
            pt::json_parser::read_json(path,pt_);
            result = true;
        } catch (boost::property_tree::json_parser_error& error) {
            std::cout << "file:" << error.filename() << " " << error.message() << std::endl;
        }
        return result;
    }
    void Parse() {
        for (auto node : pt_.get_child("Applications")) {
            assert(node.first.empty()); // array elements have no names
            for (auto sub_node : node.second) {
                ConfigData data;
                data.application_name = sub_node.first;
                //std::cout << "application_name:" << data.application_name << std::endl;
                for (auto app_node : sub_node.second) {
                    if(app_node.first == "UseCase"){
                        data.use_case = app_node.second.get_value<uint8_t>();
                        //std::cout << "use_case:" << static_cast<int>(data.use_case) << std::endl;
                    }
                    else if(app_node.first == "Channels"){
                        for(auto channels : app_node.second){
                            auto val = GetChannelValue(channels.second.get_value<std::string>());
                            if(val){
                                //std::cout << "Channel:" << static_cast<int>(val.value()) << std::endl;
                                data.channels.push_back(val.value());
                            }
                        }
                        std::cout << data;
                    }
                }
            }
        }
    }

private:
    boost::optional<uint8_t> GetChannelValue(const std::string& ch){
        boost::optional<uint8_t> return_value;
        size_t length = sizeof(kChannelString) / sizeof(kChannelString[0]);
        for(size_t idx=0 ; idx < length; idx++){
            if(!strcmp(kChannelString[idx], ch.c_str())){
                return_value = idx;
            }
        }
        return return_value;
    }
    std::vector<ConfigData>config_data_vector;
    pt::ptree pt_;
};

class Client{
public:
    Client(std::shared_ptr<std::vector<int>>client_socket_fd) : client_socket_fd_{client_socket_fd}{};
    void Run(){
        while(!stopped_.load()){
            if(client_socket_fd_->empty()){
                continue;
            }
            int client_fd = client_socket_fd_->front();
            client_socket_fd_->erase(client_socket_fd_->begin());
            if(send(client_fd, buff, 24, 0) < 0){
                perror("Sending Error");
            }
            close(client_fd);
        }
    }
    void Stop(){
        stopped_= true;
    }
private:
char buff[24]{"Hello from server !\n"};
std::shared_ptr<std::vector<int>>client_socket_fd_;
std::atomic_bool stopped_{false};
};

int main()
{
    std::shared_ptr<std::vector<int>>client_socket_fd{new std::vector<int>{}};
    Client client{client_socket_fd};
    TcpHelper tcp_helper{client_socket_fd};
    if(!tcp_helper.CreateServer()){
        perror("ERROR:");
        return -1;
    }
    std::thread t = std::thread{&Client::Run,&client};

    std::this_thread::sleep_for(std::chrono::seconds(60));
    client.Stop();
    t.join();
    // std::string file_ = "/home/mert/Projects/CmakeRepo/App/test.txt";
    // std::string direct = "/home/mert/Projects/CmakeRepo/App/demo/";
    // std::string new_direct = "/home/mert/Projects/CmakeRepo/App/include/demo/";
    // std::string new_file_ = "/home/mert/Projects/CmakeRepo/App/test/test.txt";
    // // std::string file_name {"/home/mert/Projects/CmakeRepo/App/log_level.xml"};
    // // XMLParser parser{file_name};
    // // parser.ReadAll();
    // // ConfigFileParser json_parser;
    // // if(!json_parser.Initialize("/home/mert/Projects/CmakeRepo/App/channel.json")){
    // //     return -1;
    // // }
    // // json_parser.Parse();
    // FileUtil file_util;
    // if(file_util.CreateFile(file_)){
    //     std::cout << "File creation succeed!\n";
    //     file_util.PrintFileAllInformation(file_);
    //     sync();
    // }
    // else{
    //     std::cout << "File creation failed!\n";
    // }

    // if(file_util.FileExists(file_)){
    //     std::cout << "File exists!\n";
    // }
    // else{
    //     std::cout << "File is exists!\n";
    // }


    // if(file_util.CreateDirectory(direct)){
    //     std::cout << "Directory creation succeed!\n";
    // }
    // else{
    //     std::cout << "Directory creation failed!\n";
    // }

    // if(file_util.MoveFile(new_file_,file_)){
    //     std::cout << "Moving file succeed!\n";
    // }
    // else{
    //     std::cout << "Moving file failed!\n";
    // }

    // if(file_util.MoveFolder(new_direct, direct)){
    //     std::cout << "Moving folder succeed!\n";
    // }
    // else{
    //     std::cout << "Moving folder failed!\n";
    // }

    // if(file_util.DeleteFile(new_direct+"test.txt")){
    //     std::cout << "File deleted succeed!\n";
    // }
    // else{
    //     std::cout << "File deleted succeed!\n";
    // }

    // if(file_util.DeleteDirectory(new_direct)){
    //     std::cout << "DeleteDirectory succeed!\n";
    // }
    // else{
    //     std::cout << "DeleteDirectory failed!\n";
    // }

    // if(file_util.CreateDirectory(direct)){
    //     std::cout << "Directory creation succeed!\n";
    // }
    // else{
    //     std::cout << "Directory creation failed!\n";
    // }

    // if(file_util.DeleteDirectory(direct)){
    //     std::cout << "DeleteDirectory succeed!\n";
    // }
    // else{
    //     std::cout << "DeleteDirectory failed!\n";
    // }

    return 0;
    
}