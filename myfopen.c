//コンソールに出力関数 *でポインタ FILE *fp1, *fpw;で参照

#include<stdio.h>
#include<stdlib.h>

FILE *myfopen(char *fmame,char *mode)
{
    FILE *fp;
    fp = fopen(fmame,mode);
    if(fp == NULL){
        fprintf(stderr,"Can't Open this file: %s\n",fmame);
        exit(0);
    }
    return fp;
}