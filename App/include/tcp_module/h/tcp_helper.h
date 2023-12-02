#include <arpa/inet.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <thread>
#include <unistd.h>
#include <vector>
inline constexpr int kProtocol = 0;
inline constexpr int kPort = 8080;
inline constexpr int kNumberOfListener = 3;

extern int errno;

class TcpHelper {
public:
  TcpHelper(std::shared_ptr<std::vector<int>> client_socket_fd)
      : client_socket_fd_{client_socket_fd} {}
  ~TcpHelper() {
    stopped_ = true;
    if (listener_thread_.joinable()) {
      listener_thread_.join();
    }
  }
  bool CreateServer() {
    int sockfd = socket(AF_INET, SOCK_STREAM, kProtocol);
    if (sockfd < 0) {
      perror("Creation");
      return false;
    }
    server_fd_ = sockfd;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(kPort);
    if (bind(server_fd_, (struct sockaddr *)&address,
             (socklen_t)sizeof(address)) < 0) {
      perror("Binding");
      return false;
    } else if (listen(server_fd_, kNumberOfListener) < 0) {
      perror("Listening");
      return false;
    }

    listener_thread_ = std::thread{&TcpHelper::Run, this};
    std::cout << "Socket was created succeed!\n";
    return true;
  }

private:
  void Run() {
    char buf[1024]{};
    socklen_t len = sizeof(address);
    while (!stopped_.load()) {
      std::cout << "Server is running !\n";
      int new_socket{0};
      if ((new_socket = accept(server_fd_, (struct sockaddr *)&address, &len)) <
          0) {
        perror("Invalid client socket");
        exit(EXIT_FAILURE);
      }
      client_socket_fd_->push_back(new_socket);
    }
    std::cout << "Stop signal! Shutdown server !\n";
    close(server_fd_);
  }
  void Sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
  }
  std::shared_ptr<std::vector<int>> client_socket_fd_;
  int server_fd_;
  struct sockaddr_in address {};
  std::thread listener_thread_;
  std::atomic_bool stopped_{false};
};