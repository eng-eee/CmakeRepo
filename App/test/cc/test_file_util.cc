#include "gtest/gtest.h"
#include <iostream>
#include "file_util.h"

TEST(FileUtil, CreateFile) {
    std::string file_ = "/home/mert/Projects/CmakeRepo/App/test.txt";
    std::cout << "TEST!1 RUNN !\n";
    FileUtil file_util;

    EXPECT_TRUE(file_util.CreateFile(file_));
}

TEST(FileUtil, FileExists) {
    std::string file_ = "/home/mert/Projects/CmakeRepo/App/test.txt";
    std::cout << "TEST!1 RUNN !\n";
    FileUtil file_util;

    EXPECT_TRUE(file_util.FileExists(file_));
}