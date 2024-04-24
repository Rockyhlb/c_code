#include <stdio.h>
#include <stdlib.h>
#include "snake.c"

void show_map(int map[10][10]) {
    printf("\n开始游戏(w:up, a:left, s:down, d:right, 0:退出)--> \n");
    for(int i=0; i<10; i++)
		{
			for(int j=0; j<10; j++)
			{
				switch(map[i][j])
				{
					case 0: 
                        printf("\033[44;33m  \033[0m" ); 
                        break;
					case 1: 
                        printf("\033[43;33m  \033[0m" );
                        break;
					case 2: 
                        printf("\033[42;33m  \033[0m" ); 
                        break;
					case 3: 
                        printf("\033[41;33m  \033[0m" ); 
                        break;
				}
			}
			printf("\n");
		}
}

int main()
{
    system("stty -icanon");

    // 1：边界    2：食物   0：移动范围
	int map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	SNAKE snake;
	snake_init(&snake);
	snake_insert(&snake, 7, 6,map);
	snake_insert(&snake, 6, 6,map);

	while(1)
	{
		system("clear");

		// map[x][y] = 3;
		snake_on_map(&snake, map);
        show_map(map);

        char ch = getchar();

		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
			snake_clear_map(&snake,map);
		}
		
		switch(ch)
		{
		    case 'w':
				snake_up(&snake,map);
                // map[x--][y] = 0;
                break;
            case 'a':
				snake_left(&snake,map);
                // map[x][y--] = 0;
                break;
            case 's':
				snake_down(&snake,map);
                // map[x++][y] = 0;
                break;
            case 'd': 
				snake_right(&snake,map);
                // map[x][y++] = 0;
                break;
            case '0':
                printf("退出成功~~\n");
                exit(-1);
                break;
            default:
                printf("请输入有效字符~~");
                break;
		}
	}
}