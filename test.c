#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ezdib.h"
#include <stdbool.h>

struct vertex
{
    char name[16];
    struct vertex* adjacent[32];
    int adjacentIndex;
    int level;
    int degree;
    int xoffset;
    int yoffset;
    bool mark;
    int down;
};

void draw(struct vertex* vertices, int count, HEZDIMAGE hDib, HEZDIMAGE hFont);

int main()
{
    char filename[100] = {0};
    HEZDIMAGE hDib;
    HEZDFONT hFont;

    hDib = ezd_create(1000, -1000, 32, 0);
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

    for(int i = 0; i < count; i++)
    {
        vertices[i].adjacentIndex = 0;
    }


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
                    for(int m = 0; m < count; m++)
                    {
                        if(strcmp(vertices[m].name, list[j+1]) == 0)
                        {
                            vertices[i].adjacent[adindex] = &vertices[m];
                            vertices[i].adjacentIndex++;
                        }
                    }
                    for(int k = 0; k < count; k++)
                    {
                        if(strcmp(vertices[k].name, list[j + 1]) == 0)
                            vertices[k].degree++;
                    }
                    adindex++;
                }
            }
        }
    }

    for(int i = 0; i < count; i++)
    {
        for(int l = 0; l < vertices[i].adjacentIndex; l++)
        {
            for(int j = 0; j < vertices[i].adjacent[l]->adjacentIndex; j++)
            {
                for(int k = 0; k < vertices[i].adjacentIndex; k++)
                {
                    struct vertex* temp = vertices[i].adjacent[j]->adjacent[j];
                    if(strcmp(vertices[i].adjacent[k]->name, temp->name) == 0)
                    {
                        for(int m = k; m < vertices[i].adjacentIndex; m++)
                        {
                            vertices[i].adjacent[m] = vertices[i].adjacent[m + 1];
                            vertices[i].adjacentIndex--;
                            temp->degree--;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < vertices[i].adjacentIndex; j++)
        {
            printf("%s %s\n", vertices[i].name, vertices[i].adjacent[j]);
        }
    }

    for(int k = 0; k < count; k++)
        vertices[k].down = false;

    int level = 1;
    int check = 0;
    while(check != count)
    {
        check = 0;
        for(int i = 0; i < count; i++)
        {
            if(vertices[i].degree == 0)
            {
                vertices[i].level = level;
                if(vertices[i].adjacentIndex == 0)
                {
                    vertices[i].degree = -1;
                }
                for(int j = 0; j < vertices[i].adjacentIndex; j++)
                {
                    vertices[i].degree = -1;
                    vertices[i].adjacent[j]->down++;
                }
            }    
        }   
        for(int k = 0; k < count; k++)
        {   
            if(vertices[k].down > 0)
            {
                vertices[k].level = level + 1;
                vertices[k].degree -= vertices[k].down;
            }
            if(vertices[k].degree == -1)
                check++;
        }   

        for(int k = 0; k < count; k++)
        {
            vertices[k].down = 0;
        }

        for(int k = 0; k < count; k++)
        {
            printf("%s %d %d\n", vertices[k].name, vertices[k].level, vertices[k].degree);
        }
        level++;
    }

    printf("here");

    int levelarr[32] = {0};
    for(int i = 0; i < level; i++)
    {
        for(int j = 0; j < count; j++)
        {
            if(i + 1 == vertices[j].level)
                levelarr[i]+=1;
        }
    }    
    printf("here");
    check = 0;
    index = 0;
    int xoffset = 0;
    int yoffset = level - 1;

    while(check < level)
    {
        xoffset = 1;
        for(int i = 0; i < count; i++)
        {
            if((check + 1) == vertices[i].level)
            {
                ezd_text(hDib, hFont, vertices[i].name, -1, xoffset * 1000/levelarr[index] - 200, yoffset * 1000/level, 0xffffff);
                vertices[i].xoffset = xoffset * 1000/levelarr[index] - 200;
                vertices[i].yoffset = yoffset * 1000/level;
                xoffset++;
            }
        }
        yoffset--;
        index++;
        check++;
    }
    printf("here");
    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < vertices[i].adjacentIndex; j++)
        ezd_line(hDib, vertices[i].xoffset, vertices[i].yoffset, vertices[i].adjacent[j]->xoffset, vertices[i].adjacent[j]->yoffset, 0xfffff);
    }

    
    ezd_save(hDib, "output.bmp");
    if(hFont)
        ezd_destroy_font(hFont);

    if(hDib)
        ezd_destroy(hDib);

    return 0;
}