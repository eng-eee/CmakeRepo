
#include <iostream>

#include "file_util.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>


bool FileUtil::CreateFile(const std::string &path) {
  int neg_special_ret{-1};
  int fd2 = open(path.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH);
  return !(neg_special_ret == fd2);
}

bool FileUtil::FileExists(const std::string &path) {
  struct stat stat_;

  return stat(path.c_str(), &stat_) == 0 ? true : false;
}

bool FileUtil::DeleteFile(const std::string &path) {
  return remove(path.c_str()) == 0 ? true : false;
}

bool FileUtil::CreateDirectory(const std::string &path) {
  if (!FileExists(path)) {
    return mkdir(path.c_str(), 0777) == 0 ? true : false;
  }
  return false;
}
bool FileUtil::DeleteDirectory(const std::string &path) {
  return remove(path.c_str()) == 0 ? true : false;
}
bool FileUtil::MoveFile(const std::string &target, const std::string &source) {
  if (target.back() == '/' || source.back() == '/') {
    std::cout << "1false\n";
    return false;
  }

  if (FileExists(source.c_str())) {
    return rename(source.c_str(), target.c_str()) == 0 ? true : false;
  }
  std::cout << "2false\n";

  return false;
}
bool FileUtil::MoveFolder(const std::string &target,
                          const std::string &source) {
  if (target.back() != '/' || source.back() != '/') {
    return false;
  }

  if (FileExists(source.c_str())) {
    return rename(source.c_str(), target.c_str()) == 0 ? true : false;
  }
  return false;
}

void FileUtil::PrintFileAllInformation(const std::string& path){
  const char* c_str = path.c_str();
  struct stat sb;
   if (stat(c_str, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

   printf("File type:                ");

   switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
            (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
            (long) sb.st_blksize);
    printf("File size:                %lld bytes\n",
            (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) sb.st_blocks);

   printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));
}
std::vector<std::string> FileUtil::GetSubFolders(const std::string &target,
                                                 const std::string &source) {
  return std::vector<std::string>{};
}