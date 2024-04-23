#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    // 1、打开两张图片
    int fd1 = open("image1.bmp", O_RDWR);
    if (-1 == fd1) {
        perror("Failed on open image1.bmp");
        return -1;
    }

    int fd2 = open("image2.bmp", O_RDWR);
    if (-1 == fd2) {
        perror("Failed on open image2.bmp");
        close(fd1);
        return -1;
    }

    // 2、获取图片数据
    char header[54] = { 0 };
    if (read(fd1, header, sizeof(header)) != sizeof(header)) {
        perror("read image1.bmp header failed!");
        close(fd1);
        close(fd2);
        return -1;
    }

    unsigned char buf1[799 * 460 * 4] = { 0 };
    int ret1 = read(fd1, buf1, sizeof(buf1));
    if (-1 == ret1) {
        perror("read image1.bmp failed!");
        close(fd1);
        close(fd2);
        return -1;
    }

    lseek(fd2, 54, SEEK_SET);
    unsigned char buf2[799 * 460 * 4] = { 0 };
    int ret2 = read(fd2, buf2, sizeof(buf2));
    if (-1 == ret2) {
        perror("read image2.bmp failed");
        close(fd1);
        close(fd2);
        return -1;
    }

    // 3、阿尔法合成数据,将两张照片进行合成
    for (int i = 0; i < sizeof(buf1); ++i) {
        buf1[i] = buf1[i] * 0.3 + buf2[i] * 0.7;
    }

    // 4、将header和合成结果写入新图片
    int fd_out = open("combined_image.bmp", O_CREAT | O_WRONLY, 0666);
    if (-1 == fd_out) {
        perror("open combined_image.bmp failed!");
        close(fd1);
        close(fd2);
        return -1;
    }
    // header
    if (write(fd_out, header, sizeof(header)) != sizeof(header)) {
        perror("write combined_image.bmp header failed!");
        close(fd1);
        close(fd2);
        close(fd_out);
        return -1;
    }
    // body
    if (write(fd_out, buf1, sizeof(buf1)) != sizeof(buf1)) {
        perror("write combined_image.bmp pixel data");
        close(fd1);
        close(fd2);
        close(fd_out);
        return -1;
    }

    // 4、关闭资源 
    close(fd1);
    close(fd2);
    close(fd_out);
}
