#include <fcntl.h>
#include <stdio.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <unistd.h>
/* For simplicity, all error checking has been left out */

int main(int argc, char ** argv) {
  int fd,fd2;
  char buf[1024];
  int i;
  struct pollfd pfds[3];               // 1 2 3
  fd = open("text1", O_RDONLY);
  fd2 = open("text2", O_RDONLY);

  while (1) {
    pfds[0].fd = 0;
    pfds[0].events = POLLIN;

    pfds[1].fd = fd;
    pfds[1].events = POLLIN;

    pfds[2].fd = fd2;
    pfds[2].events = POLLIN;

    poll(pfds, 3, -1);
    if (pfds[0].revents & POLLIN) {
      i = read(0, buf, 1024);
      if (!i) {
        // printf("stdin closed\n");
        //  return 0;
      }
      write(1, buf, i);
    }

    if (pfds[1].revents & POLLIN) {
      i = read(fd, buf, 1024);
      if (!i) {
        // printf("file 1 closed\n");
        //  return 0;
      }
      write(1, buf, i);
    }

    if (pfds[2].revents & POLLIN) {
      i = read(fd2, buf, 1024);
      if (!i) {
        // printf("file 2 closed\n");
        //  return 0;
      }
      write(1, buf, i);
    }
  }
}
