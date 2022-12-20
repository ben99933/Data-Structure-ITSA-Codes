#include<stdio.h>
#define Long long long
typedef char boolean;
#define True 1
#define False 0
/* 
 * 題目規定輸入六個數字(固定6個) 然後以相反的順序輸出
 * 那我就先反著將數字存入陣列
 * 輸出的時候順著輸出就好
 */
int main(){
    Long array[6];
    //反著存放數字
    for(int index = 5;index >= 0;index--){
        scanf("%lld",&array[index]);
    }
    boolean flag = False;//控制是否要print空白 如果flag=true則加空白 否則把flag設為false
    for(int index = 0;index <6;index++){
        if(flag)printf(" ");
        else flag = True;
        printf("%lld",array[index]);
    }
    printf("\n");
    return 0;
}
