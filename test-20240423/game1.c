#include <stdio.h>
#include <stdlib.h>

void MapPrint(int map[][10]) {
    printf("\n开始游戏(w:up, a:left, s:down, d:right, 0:退出)-->: \n");
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
		{1, 0, 2, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 2, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 2, 1},
		{1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	int x = 4;
	int y = 4;

	while(1)
	{
		system("clear");

		map[x][y] = 3;

        MapPrint(map);
        char ch = getchar();

		switch(ch)
		{
		    case 'w':
                map[x--][y] = 0;
                break;
            case 'a':
                map[x][y--] = 0;
                break;
            case 's':
                map[x++][y] = 0;
                break;
            case 'd': 
                map[x][y++] = 0;
                break;
            case '0':
                printf("退出成功~~\n");
                exit(-1);
                break;
            default:
                printf("请输入有效字符~~");
                break;
		}

        if(x==0) x=1;
		if(x==9) x=8;
		if(y==0) y=1;
		if(y==9) y=8;
	}
}