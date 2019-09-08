//
//  main.c
//  bmstu_dz
//
//  Created by Konstantin Zhurov on 02/09/2019.
//  Copyright © 2019 ph4nt0m7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#define ERROR "[\x1b[1m\x1b[31mERROR\x1b[0m]"
//#define WARNING "[\x1b[1m\x1b[33mWARNING\x1b[0m]"
#define WARNING "[WARNING]"

#define DATA_TYPE_DEC unsigned long
#define DATA_TYPE_BIN char
#define TURN_WRONG_NUMBER_INTO_ZERO 1
#define DO_A_NUM_LIST 1
#define START_LIST_FROM 1

unsigned long arr_size = 0;

void PrintArr2Sets(DATA_TYPE_BIN **array, char column, char line){
    int i = 0, j = 0;
    
    while(array[i] != '\0'){
        if(DO_A_NUM_LIST && j == 0)
            printf("%d: ",i+START_LIST_FROM);
        
        printf("%c", array[i][j]);
        
        if(line != '\0')
            printf("%c", line);
        j++;
        
        if(array[i][j] == '\0'){
            if(j == 1)
                printf("0");
            if(column != '\0')
                printf("%c", column);
            i++; j=0;
        }
    }
}

DATA_TYPE_BIN *dec2bin (const DATA_TYPE_DEC num){
    DATA_TYPE_DEC buff_num = num;
    DATA_TYPE_BIN *buff_bin;
    buff_bin = calloc(1, sizeof(DATA_TYPE_BIN));
    buff_bin[0] = 0;
    int clock = 0;
    
    while(buff_num != 0){
        buff_bin[clock] = '0' + (buff_num%2);
        buff_num /= 2;
        clock++;
        buff_bin = (DATA_TYPE_BIN*) realloc(buff_bin, clock+1);
        buff_bin[clock] = 0;
        //        printf("DEBUG: CLOCK: %d; BUFF_BIN: %s; BUFF_NUM %lu\n",clock-1,buff_bin,buff_num);
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
    arr_size = 0;
    int clock_max_value = 0;
    DATA_TYPE_DEC *arr, buff_num=0;
    char c = 0;
    _Bool nextflag = 0;
    arr = calloc(arr_size+1, sizeof(DATA_TYPE_DEC));
    
    while(c != '\n'){
        c=getchar();
        if(c>='0' && c<='9'){
            c-=48;
            buff_num *= 10;
            buff_num += c;
            nextflag = 0;
            clock_max_value++;
        } else if((c == ',' || c == '\n' || c == ' ') && nextflag == 0){
            if(clock_max_value >= 20){
                printf("%s %lu Number reach max value! Conversion will be wrong\n", WARNING, arr_size+START_LIST_FROM);
                if(TURN_WRONG_NUMBER_INTO_ZERO)
                    buff_num = 0;
            }
            arr[arr_size] = buff_num;
            arr_size++;
            buff_num = 0;
            arr = (DATA_TYPE_DEC*) realloc(arr, arr_size+1);
            nextflag = 1;
            clock_max_value = 0;
            //            printf("+%c",c);
        } else {
            //            printf("\nDetect incorrect symbol, exiting...\n");
            //            exit(9);
            //            nextflag = 0;
        }
    }
    
    //    arr = (DATA_TYPE_DEC*) realloc(arr, num+1);
    arr[arr_size+1]='\0';
    return arr;
}

int main(int argc, char *argv[]) {
    if(!strcmp(argv[1],"testing")){
        printf("all fine)");
        exit(0);
    }
    printf("Enter numbers separated by commas... e.g.: 10,432,310729\n");
    DATA_TYPE_DEC *arr;
    DATA_TYPE_BIN **arr2;
    
    arr = NumArray();
    arr2 = calloc(arr_size+1, sizeof(DATA_TYPE_BIN));
    
    for(int i=0; i<arr_size;i++){
        arr2[i] = dec2bin(arr[i]);
    }
    arr2[arr_size] = NULL;
    PrintArr2Sets(arr2, '\n','\0');
    
    return 0;
}
