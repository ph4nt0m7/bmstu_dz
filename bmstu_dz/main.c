//
//  main.c
//  bmstu_dz
//
//  Created by Kostya on 02/09/2019.
//  Copyright © 2019 ph4nt0m7. All rights reserved.
//

//unsigned long = 0-18`446`744`073`709`551`615 (~18*10^18)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define DATA_TYPE_DEC int
#define DATA_TYPE_BIN char

unsigned long num = 0;

DATA_TYPE_BIN *dec2bin (const DATA_TYPE_DEC num){
    DATA_TYPE_DEC buff_num = num;
    DATA_TYPE_BIN *buff_bin;
    buff_bin = calloc(1, sizeof(DATA_TYPE_BIN));
    
    int clock = 0;
    
    while(buff_num != 0){
        buff_bin[clock] = '0' + (buff_num%2);
        buff_num /= 2;
        clock++;
        buff_bin = (DATA_TYPE_BIN*) realloc(buff_bin, clock+1);

//        printf("DEBUG: CLOCK: %d; BUFF_BIN: %f; BUFF_NUM %d\n",clock-1,buff_bin,buff_num);
    }
    
    DATA_TYPE_BIN temp=0;
    for(int i=0; i<clock/2; i++){
        temp = buff_bin[i];
        buff_bin[i] = buff_bin[clock-i-1];
        buff_bin[clock-i-1] = temp;
    }
    
    
    buff_bin[clock]='\0';
    
    return buff_bin;
}

DATA_TYPE_DEC *NumArray(void){
    DATA_TYPE_DEC *arr, buff_num=0;
    char c = 0;
    _Bool nextflag = 0;
    arr = calloc(num+1, sizeof(DATA_TYPE_DEC));
    
    while(c != '\n'){
        c=getchar();
        if(c>='0' && c<='9'){
            c-=48;
            buff_num *= 10;
            buff_num += c;
            nextflag = 0;
        } else if((c == ',' || c == '\n' || c == ' ') && nextflag == 0){
            arr[num] = buff_num;
            num++;
            buff_num = 0;
            arr = (DATA_TYPE_DEC*) realloc(arr, num+1);
            nextflag = 1;
//            printf("+%c",c);
        } else {
//            printf("\nDetect incorrect symbol, exiting...\n");
//            exit(9);
//            nextflag = 0;
        }
    }
    
//    arr = (DATA_TYPE_DEC*) realloc(arr, num+1);
    arr[num+1]='\0';
    return arr;
}

int main() {
    printf("Enter numbers separated by commas... e.g.: 10,432,310729\n");
//    DATA_TYPE_DEC *arr, *arr2;
//    arr2 = calloc(1, sizeof(DATA_TYPE_DEC));
//
//    arr = NumArray();
//
//    for(int i=0; i<num;i++){
//        printf("%d; ", arr[i]);
//    }
    DATA_TYPE_DEC test_num = 817233;
    DATA_TYPE_BIN *test_bin;
    test_bin = dec2bin(test_num);
    
    printf("%s\n",test_bin);
    
    return 0;
}
