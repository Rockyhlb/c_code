#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void color(const char *color_code);

void kongge(int sum);

void chars(int sum);

// 打印 Logo
void print_logo_head();
void print_logo_head1();
void print_logo_tail();
void print_combined_logo();

// 打印日志
void print_log_info(const char *message);
void print_log_error(const char *message);

// 获取时间
struct tm get_cur_time();