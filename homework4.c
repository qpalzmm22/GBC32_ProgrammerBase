#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ezdib.h"
#include <stdbool.h>

struct vertex
{
    char name[16];
    char adjacent[32][16];
    int adjacentIndex;
    int level;
    int degree;
    bool mark;
};

int main()
{
    char filename[100] = {0};
    HEZDIMAGE hDib;
    HEZDFONT hFont;

    hDib = ezd_create(500, -500, 32, 0);
    if(!hDib)
        return 1;
    hFont = ezd_load_font(EZD_FONT_TYPE_MEDIUM,0, 0);

    printf("input filename : ");
    scanf("%s", filename);

    FILE * file = fopen(filename, "r"); // receive each line as input
    char token[16];
    char temp[32][16] = {0}; 
    int count = 0;

    struct vertex vertices[32] = {0};

    //Receive the file as a line and save it into an array
    while(fscanf(file, "%s", token) != EOF)
    {
        int check = 0;
        for(int i = 0; i < 32; i++)
        {
            if(strcmp(vertices[i].name, token) == 0)
                check = 1;
        }

        if(check != 1)
        {
            strcpy(vertices[count].name, token);
            count++;
        }
    }
    fclose(file);

    FILE * file2 = fopen(filename, "r");
    memset(token, 0 , sizeof(token));
    char list[64][32]={0};
    int index = 0;
    // 파일을 다시 열어서 파일 그대로 리스트 안에 저장하기
    while(fscanf(file, "%s", token) != EOF)
    {
        strcpy(list[index],token);
        index++;
    }

    fclose(file2);
    //각 각 vertex 안에 무엇이 있는 지 정리하는 과정. 예를 들면 C : java, DS, 등등
    for(int i = 0; i < count; i++)
    {
        int adindex = 0;
        for(int j = 0; j < index; j++)
        {
            if(j % 2 == 0)
            {
                if(strcmp(vertices[i].name, list[j]) == 0)
                {
                    if(strcmp(vertices[i].name, list[j + 1]) == 0) // comparing left side and right side
                        continue;
                    strcpy(vertices[i].adjacent[adindex], list[j + 1]);
                    for(int k = 0; k < count; k++)
                    {
                        if(strcmp(vertices[k].name, list[j + 1]) == 0)
                            vertices[k].degree++;
                    }
                    adindex++;
                }
            }
        }
        printf("%s %d\n", vertices[i].name, vertices[i].degree);
    }
    
    

    for(int i = 0; i < count; i++)
    {
        ezd_text(hDib, hFont, vertices[i].name, -1, i * 500/count + 10, 300, 0xffffff);
        int adindex = 0;
        int xoffset = 0;
        while(adindex < vertices[i].adjacentIndex)
        {
            ezd_text(hDib, hFont, vertices[i].adjacent[adindex], -1, i * 500/count + 10 + xoffset, 100, 0xffffff);
            xoffset += 30;
            adindex++;
        }
        ezd_line(hDib, i * 500/count + 10, 300, i * 500/count + 10, 100, 0xfffff);
    }

    ezd_save(hDib, "output.bmp");
    if(hFont)
        ezd_destroy_font(hFont);

    if(hDib)
        ezd_destroy(hDib);
    return 0;
}