//
//  main.c
//  bmstu_dz
//
//  Created by Kostya on 02/09/2019.
//  Copyright © 2019 ph4nt0m7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define DATA_TYPE int

unsigned long num = 0;

int *num_array(void){
    DATA_TYPE *arr, c, buff_num=0;
    arr = calloc(num+1, sizeof(DATA_TYPE));
    
    while((c=getchar()) !='\n'){
        if(c>='0' && c<='9'){
            c-=48;
            buff_num *= 10;
            buff_num += c;
        } else if(c == ','){
            arr[num] = buff_num;
            num++;
            arr = (DATA_TYPE*) realloc(arr, num+1);
        } else {
//            printf("\nDetect incorrect symbol, exiting...\n");
//            exit(9);
        }
    }
//    arr = (DATA_TYPE*) realloc(arr, num+1);
    arr[num+1]='\0';
    return arr;
}

int main() {
    printf("Enter numbers separated by commas... e.g.: 10,432,310729\n");
    DATA_TYPE *arr, *arr2;
    arr2 = calloc(num+1, sizeof(DATA_TYPE));
    
    arr = num_array();
    
    for(int i=0; i<num;i++){
        
    }
    
    return 0;
}

//is iy updated?
