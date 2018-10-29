#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int gen_rand() {
  int fd = open("/dev/urandom", O_RDONLY);
  int randint;
  read(fd, &randint, sizeof(int));
  if (errno) {
    printf("errno: %d Message: %s\n", errno, strerror(errno));
  }
  close(fd);
  return randint;
}

int main() {

  int intarray[10];

  printf("Generating random numbers:\n");
  for (int i = 0; i < 10; i++) {
    intarray[i] = gen_rand();
    printf("\trandom %d: %d\n", i, intarray[i]);
  }
  printf("\nWriting numbers to file...\n");

  char * file_2 = "random_num.txt";
  int file_id_c = open(file_2, O_RDWR|O_CREAT, 0666);
  write(file_id_c, intarray, sizeof(intarray));
  close(file_id_c);

  if (errno) {
    printf("Errno number: %d\n", errno);
    printf("Message: %s\n", strerror(errno));
  }

  printf("\nReading numbers from file...\n");
  int new_nums[10];
  int file_id_d = open(file_2, O_RDONLY);
  read(file_id_d, &new_nums, sizeof(new_nums));
  close(file_id_d);

  if (errno) {
    printf("Errno number: %d\n", errno);
    printf("Message: %s\n", strerror(errno));
  }

  printf("\nVerification that written values were the same:\n");
  for(int i = 0; i < 10; i++){
    printf("random %d: %d\n", i, new_nums[i]);
  }

  return 0;
}
