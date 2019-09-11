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
#define END_PROG_WHEN_INCOR_SMBL 0
#define DO_A_NUM_LIST 1
#define START_LIST_FROM 1

unsigned long arr_size = 0;
unsigned long dec2bin_lastnum = 0;

void PrintArr2Sets(DATA_TYPE_BIN **array, char column, char line){
    int i = 0, j = 0, test=0;
    
    while(array[i] != '\0' && array != NULL && array[i] != NULL){
        if(DO_A_NUM_LIST && j == 0)
            printf("%d: ",i+START_LIST_FROM);
        
        printf("%c", array[i][j]);
        if(array[i][j] == 0)
            printf("0");
        
        if(line != '\0')
            printf("%c", line);
        j++;
        
        if(array[i][j] == '\0'){
            if(column != '\0')
                printf("%c", column);
            i++; j=0;
        }
        test++;
    }
}

DATA_TYPE_BIN *dec2bin (const DATA_TYPE_DEC num){
    dec2bin_lastnum = 0;
    DATA_TYPE_DEC buff_num = num;
    DATA_TYPE_BIN *buff_bin;
    buff_bin = calloc(1, sizeof(DATA_TYPE_BIN));
    buff_bin[0] = 0;
    int clock = 0;
    
    while(buff_num != 0){
        DATA_TYPE_BIN *temp_buff_bin;
        temp_buff_bin = calloc(clock+1, sizeof(DATA_TYPE_BIN));
        for(int cl=0; cl<clock; cl++){
            temp_buff_bin[cl] = buff_bin[cl];
        }

        temp_buff_bin[clock] = '0' + (buff_num%2);
        buff_num /= 2;
        buff_bin = temp_buff_bin;
        clock++;
        buff_bin[clock] = 0;
    }
    
    DATA_TYPE_BIN temp=0;
    for(int i=0; i<clock/2; i++){
        temp = buff_bin[i];
        buff_bin[i] = buff_bin[clock-i-1];
        buff_bin[clock-i-1] = temp;
    }
    
    buff_bin[clock]='\0';
    dec2bin_lastnum = clock;
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
        if(c>='0' && c<='9') {
            c-='0';
            buff_num *= 10;
            buff_num += c;
            nextflag = 0;
            clock_max_value++;
        } else if (c == ',' || c == '\n' || c == ' ' || c == '\t' || c == ';') {
            if(nextflag == 0){
                if(clock_max_value >= 20){
                    printf("%s %lu Number reach max value! Conversion will be wrong\n", WARNING, arr_size+START_LIST_FROM);
                    if(TURN_WRONG_NUMBER_INTO_ZERO)
                        buff_num = 0;
                }
                DATA_TYPE_DEC *temp_arr;
                temp_arr = calloc(arr_size+1, sizeof(DATA_TYPE_DEC));
                for(int cl = 0; cl < arr_size; cl++){
                    temp_arr[cl] = arr[cl];
                }
                temp_arr[arr_size] = buff_num;
                arr = temp_arr;
                
                arr_size++;
                buff_num = 0;
                nextflag = 1;
                clock_max_value = 0;
            }
        } else if (END_PROG_WHEN_INCOR_SMBL){
            printf("\nDetect incorrect symbol, exiting...\n");
            exit(9);
        } else {
            nextflag = 0;
        }
    }
    arr[arr_size+1]='\0';
    return arr;
}

int main(int argc, char *argv[]) {
    if(argc > 1 && (!strcmp(argv[1],"testing"))){
        printf("all fine");
        exit(0);
    }
    printf("Enter numbers separated by commas... e.g.: 10,432,310729\n");
    DATA_TYPE_DEC *arr;
    
    arr = NumArray();
    DATA_TYPE_BIN *arr2[arr_size+1], *arr2_temp;
    
    for(int i=0; i<arr_size;i++){
        arr2_temp = dec2bin(arr[i]);
        arr2[i] = calloc(dec2bin_lastnum+1, sizeof(DATA_TYPE_BIN));
        for(int j=0; j<dec2bin_lastnum; j++){
            arr2[i][j] = arr2_temp[j];
        }
    }
    arr2[arr_size] = NULL;
    PrintArr2Sets(arr2, '\n','\0');
    
    return 0;
}
