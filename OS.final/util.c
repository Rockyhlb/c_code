#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "util.h"

void color(const char *color_code)
{
    printf("%s", color_code);
}

void kongge(int sum)
{
    while (sum--)
        printf(" ");
}

void chars(int sum)
{
    while (sum--)
        printf("#");
}

void print_logo_head()
{
    printf("\033[34mWelcome To Bit OS!!! \033[m\n");
    unsigned char B[] = {0x00, 0x00, 0x00, 0xF8, 0x44, 0x44, 0x44, 0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0xF8, 0x00, 0x00};
    unsigned char I[] = {0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7C, 0x00, 0x00};
    unsigned char T[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x12, 0x0C, 0x00, 0x00};
    unsigned char O[] = {0x00, 0x00, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00};
    unsigned char S[] = {0x00, 0x00, 0x00, 0x3E, 0x42, 0x42, 0x40, 0x20, 0x18, 0x04, 0x02, 0x42, 0x42, 0x7C, 0x00, 0x00};
    int row = 0;
    int bit = 0;
    for (row = 0; row < 16; row++)
    {

        for (bit = 0; bit < 16; bit++)
        {
            unsigned char currentChar = (row < sizeof(B) / sizeof(B[0]) ? B[row] : 0x00);
            printf("%c", (currentChar & (1 << (15 - bit))) ? '#' : ' ');
        }

        for (bit = 0; bit < 16; bit++)
        {
            unsigned char currentChar = (row < sizeof(I) / sizeof(I[0]) ? I[row] : 0x00);
            printf("%c", (currentChar & (1 << (15 - bit))) ? '#' : ' ');
        }

        for (bit = 0; bit < 16; bit++)
        {
            unsigned char currentChar = (row < sizeof(T) / sizeof(T[0]) ? T[row] : 0x00);
            printf("%c", (currentChar & (1 << (15 - bit))) ? '#' : ' ');
        }

        for (bit = 0; bit < 16; bit++)
        {
            unsigned char currentChar = (row < sizeof(O) / sizeof(O[0]) ? O[row] : 0x00);
            printf("%c", (currentChar & (1 << (15 - bit))) ? '#' : ' ');
        }

        for (bit = 0; bit < 16; bit++)
        {
            unsigned char currentChar = (row < sizeof(S) / sizeof(S[0]) ? S[row] : 0x00);
            printf("%c", (currentChar & (1 << (15 - bit))) ? '#' : ' ');
        }

        printf("\n");
    }
    return;
}

void print_logo_head1()
{
    kongge(15);
    chars(6);
    printf("\n");

    kongge(13);
    color("\033[0;32m");
    chars(11);
    printf("\n");

    kongge(12);
    color("\033[0;32m");
    chars(13);
    printf("\n");

    kongge(12);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(3);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(3);
    color("\033[0;32m");
    chars(3);
    printf("\n");

    kongge(12);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(1);
    color("\033[0;32m");
    chars(1);
    color("\033[0;37m");
    chars(1);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(1);
    color("\033[0;32m");
    chars(1);
    color("\033[0;37m");
    chars(1);
    color("\033[0;32m");
    chars(3);
    printf("\n");

    kongge(12);
    color("\033[0;32m");
    chars(4);
    color("\033[0;33m");
    chars(4);
    color("\033[0;32m");
    chars(5);
    printf("\n");

    kongge(12);
    color("\033[0;32m");
    chars(2);
    color("\033[0;33m");
    chars(8);
    color("\033[0;32m");
    chars(3);
    printf("\n");

    kongge(11);
    color("\033[0;32m");
    chars(3);
    color("\033[0;37m");
    chars(2);
    color("\033[0;33m");
    chars(4);
    color("\033[0;37m");
    chars(2);
    color("\033[0;32m");
    chars(4);
    printf("\n");

    kongge(10);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(11);
    color("\033[0;32m");
    chars(4);
    printf("\n");

    kongge(9);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(13);
    color("\033[0;32m");
    chars(4);
    printf("\n");

    kongge(8);
    color("\033[0;32m");
    chars(3);
    color("\033[0;37m");
    chars(13);
    color("\033[0;32m");
    chars(5);
    printf("\n");

    kongge(7);
    color("\033[0;32m");
    chars(3);
    color("\033[0;37m");
    chars(15);
    color("\033[0;32m");
    chars(5);
    printf("\n");

    kongge(6);
    color("\033[0;32m");
    chars(3);
    color("\033[0;37m");
    chars(16);
    color("\033[0;32m");
    chars(5);
    printf("\n");

    kongge(5);
    color("\033[0;32m");
    chars(4);
    color("\033[0;37m");
    chars(16);
    color("\033[0;32m");
    chars(5);
    printf("\n");

    kongge(5);
    color("\033[0;32m");
    chars(1);
    color("\033[0;33m");
    chars(2);
    color("\033[0;32m");
    chars(1);
    color("\033[0;37m");
    chars(14);
    color("\033[0;33m");
    chars(2);
    color("\033[0;32m");
    chars(4);
    color("\033[0;33m");
    chars(1);
    printf("\n");

    kongge(5);
    color("\033[0;33m");
    chars(4);
    color("\033[0;32m");
    chars(1);
    color("\033[0;37m");
    chars(13);
    color("\033[0;33m");
    chars(3);
    color("\033[0;32m");
    color("\033[0;32m");
    chars(2);
    color("\033[0;33m");
    chars(2);
    printf("\n");

    kongge(4);
    color("\033[0;33m");
    chars(5);
    color("\033[0;32m");
    chars(2);
    color("\033[0;37m");
    chars(10);
    color("\033[0;32m");
    chars(1);
    color("\033[0;33m");
    chars(9);
    printf("\n");

    kongge(1);
    color("\033[0;33m");
    chars(9);
    color("\033[0;37m");
    chars(10);
    color("\033[0;32m");
    chars(2);
    color("\033[0;33m");
    chars(11);
    printf("\n");

    kongge(3);
    color("\033[0;33m");
    chars(8);
    color("\033[0;32m");
    chars(1);
    color("\033[0;37m");
    chars(6);
    color("\033[0;32m");
    chars(3);
    color("\033[0;33m");
    chars(10);
    printf("\n");

    kongge(1);
    color("\033[0;33m");
    chars(11);
    color("\033[0;32m");
    chars(9);
    color("\033[0;33m");
    chars(6);
    printf("\n");

    kongge(7);
    color("\033[0;33m");
    chars(4);
    color("\033[0;37m");
    chars(11);
    color("\033[0;33m");
    chars(3);
    printf("\n");
    color("\033[0;33m\033[0m");
}

void print_logo_tail()
{
    int c, p, i, j, n, F = 40, k, m;
    float a, x, y, S = 0, V = 0;

    for (; F--; usleep(50000), F ? puts("\x1b[25A") : 0)
    {
        for (S += V += (1 - S) / 10 - V / 4, j = 0; j < 72; j += 3, putchar(10))
        {
            for (i = 0; x = S * (i - 27), i++ < 73; putchar(c[" ''\".$u$"]))
            {
                for (c = 0, n = 3; n--;)
                {
                    for (y = S * (j + n - 36), k = 0, c ^= (136 * x * x + 84 * y * y < 92033) << n, p = 6, m = 0; m<8;
                                                                                                                          k++ ["<[\\]O=IKNAL;KNRbF8EbGEROQ@BSX"
                                                                                                                               "XtG!#t3!^"] /
                                                                                                                              1.16 -
                                                                                                                          68> x *
                                                                                                                          cos(a) +
                                                                                                                      y * sin(a)
                                                                                                                  ? k = p,
                        p = "<AFJPTX"[m++] - 50 : k == p ? c ^= 1 << n, m = 8 : 0)
                    {
                        a = (k["O:85!fI,wfO8!yZfO8!f*hXK3&fO;:O;#hP;\"i[by asloane"] - 79) / 14.64;
                    }
                }
            }
        }
    }
    return;
}

void print_log_info(const char *message)
{
    printf("\033[32m[INFO]\033[m %s\n", message);
}

void print_log_error(const char *message)
{
    printf("\033[31m[ERROR]\033[m %s\n", message);
}

struct tm get_cur_time() {
    // 获取当前时间
    time_t current_time;
    struct tm *local_time;

    current_time = time(NULL);
    local_time = localtime(&current_time);
    return *local_time;
}

void print_combined_logo()
{
    print_logo_head(); // Render the penguin logo
    print_logo_head1(); // Render the BitOS logo
}