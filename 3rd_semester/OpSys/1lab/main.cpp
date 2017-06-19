#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>

int main(void) {
  const int BUFF_SIZE = 256;
  int fileDescriptor;
  char* buff = new char[BUFF_SIZE];
  char* buffTrunc = new char[BUFF_SIZE];
  const char* inBuff = "Hello World!";
  ssize_t rd, wrt;

  if ((fileDescriptor = creat("test", 0)) == -1)
    perror("creat");

  if (fsync(fileDescriptor) == -1)
    perror("fsync");

  wrt = write(fileDescriptor, inBuff, strlen(inBuff));
  if (wrt == -1)
    perror("write");
  if (close(fileDescriptor) == -1)
    perror("close");
  
  fileDescriptor = open("test", O_RDONLY);
  rd = read(fileDescriptor, buff, BUFF_SIZE);

  if (rd == -1) {
    if (errno == EINTR)
      std::cout << "EINTR" << std::endl;
    perror("read");
  }

  std::cout << "Word in file is: " << buff << std::endl;

  if (close(fileDescriptor) == -1)
    perror("close");

  if (truncate("test", 2) == -1)
    perror("truncate");

  fileDescriptor = open("test", O_RDONLY);

  rd = read(fileDescriptor, buffTrunc, BUFF_SIZE);

  if (rd == -1) {
    if (errno == EINTR)
      std::cout << "EINTR" << std::endl;
    perror("read");
  }

  std::cout << "Word after trunc: " << buffTrunc << std::endl;

  if (close(fileDescriptor) == -1)
    perror("close");

  pid_t pid;
  
  pid = fork();
  if (pid == -1)
    perror("fork");

  if (pid == 0) {
    std::cout << "I'm child process! My pid = " << (intmax_t)getpid()
              << " My parent's pid = " << (intmax_t)getppid() << std::endl;

    std::cout << "Now we will see what's in your folder:" << std::endl;
    int ret = execl("/bin/ls", "ls");
    
    if (ret == -1) {
      perror("execv");
      return 1;
    }

    std::cout << std::endl;

    exit(EXIT_SUCCESS);
  }
  if (pid > 0) {
    std::cout << "I'm parent process! My pid = " << (intmax_t)getpid()
              << " My parent's pid = " << (intmax_t)getppid() <<   std::endl;

    wait(NULL);
  }
  
  return 0;
}
