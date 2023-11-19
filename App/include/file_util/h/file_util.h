#include <dirent.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>

 class FileUtil{
  public:
    bool CreateFile(const std::string& path);
    bool FileExists(const std::string& path);
    bool DeleteFile(const std::string& path);
    bool CreateDirectory(const std::string& path);
    bool DeleteDirectory(const std::string& path);
    bool MoveFile(const std::string& target, const std::string& source);
    bool MoveFolder(const std::string& target, const std::string& source);
    std::vector<std::string> GetSubFolders(const std::string& target, const std::string& source);
  private:
 };