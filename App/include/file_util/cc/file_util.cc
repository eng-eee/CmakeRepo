
#include <iostream>

#include "file_util.h"

bool FileUtil::CreateFile(const std::string& path){
    int neg_special_ret{-1}; 
    int fd2 = open(path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
    return !(neg_special_ret == fd2);
}

bool FileUtil::FileExists(const std::string& path){
    struct stat stat_;
    
    return stat(path.c_str(),&stat_) == 0 ? true : false;
}

bool FileUtil::DeleteFile(const std::string& path){
    return remove(path.c_str()) == 0 ? true : false;
}

bool FileUtil::CreateDirectory(const std::string& path){
    if(!FileExists(path)){
        return mkdir(path.c_str(), 0777)==0 ? true:false;
    }
    return false;
}
bool FileUtil::DeleteDirectory(const std::string& path){
    return remove(path.c_str()) == 0 ? true: false;
}
bool FileUtil::MoveFile(const std::string& target, const std::string& source){
    if(target.back()=='/' || source.back()=='/'){
        std::cout << "1false\n";
        return false;
    }
    
    if(FileExists(source.c_str())){
        return rename(source.c_str(), target.c_str()) == 0 ? true:false;
    }
        std::cout << "2false\n";

    return false;
}
bool FileUtil::MoveFolder(const std::string& target, const std::string& source){
    if(target.back()!='/' || source.back()!='/'){
        return false;
    }
    
    if(FileExists(source.c_str())){
        return rename(source.c_str(), target.c_str()) == 0 ? true:false;
    }
    return false;
}
std::vector<std::string> FileUtil::GetSubFolders(const std::string& target, const std::string& source){
    return std::vector<std::string>{};
}   