#include<stdio.h>  
#include<stdlib.h>  
#include<stdbool.h>  
#include<string.h>  
#include<assert.h>  
#include<stdarg.h>  
 
#define null NULL  
#define boolean bool  
#define True true  
#define False false  
#define private /*private*/  
#define public /*public*/  
#define Object void*  
#define Long long long  
#define infinity 0x7000FFFF  
#define debugMode false  
 
#define G(T) /*<T>*/  
  
  
void debug(const char* format, ...){  
    if(debugMode == false)return;  
    va_list args;  
    va_start(args, format);  
    vfprintf(stderr, format, args);  
    va_end(args);  
}  
void endl(){  
    printf("\n");  
}  
boolean isEven(int num){
    return (num & 1) == 0;
}
boolean isOdd(int num){
    return !isEven(num);
}
/** 
 * 前面200行基本上都是lib 
    ⣿⣿⣿⣿⣿⠟⠋⠄⠄⠄⠄⠄⠄⠄⢁⠈⢻⢿⣿⣿⣿⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣿⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⡀⠭⢿⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⡟⠄⢀⣾⣿⣿⣿⣷⣶⣿⣷⣶⣶⡆⠄⠄⠄⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⡇⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠄⠄⢸⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣇⣼⣿⣿⠿⠶⠙⣿⡟⠡⣴⣿⣽⣿⣧⠄⢸⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣿⣾⣿⣿⣟⣭⣾⣿⣷⣶⣶⣴⣶⣿⣿⢄⣿⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣿⣿⣿⣿⡟⣩⣿⣿⣿⡏⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣿⣿⣹⡋⠘⠷⣦⣀⣠⡶⠁⠈⠁⠄⣿⣿⣿⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣿⣿⣍⠃⣴⣶⡔⠒⠄⣠⢀⠄⠄⠄⡨⣿⣿⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⣿⣿⣿⣦⡘⠿⣷⣿⠿⠟⠃⠄⠄⣠⡇⠈⠻⣿⣿⣿⣿ 
    ⣿⣿⣿⣿⡿⠟⠋⢁⣷⣠⠄⠄⠄⠄⣀⣠⣾⡟⠄⠄⠄⠄⠉⠙⠻ 
    ⡿⠟⠋⠁⠄⠄⠄⢸⣿⣿⡯⢓⣴⣾⣿⣿⡟⠄⠄⠄⠄⠄⠄⠄⠄ 
    ⠄⠄⠄⠄⠄⠄⠄⣿⡟⣷⠄⠹⣿⣿⣿⡿⠁⠄⠄⠄⠄⠄⠄⠄⠄ 
    ⠄⠄⠄⠄⠄⠄⣸⣿⡷⡇⠄⣴⣾⣿⣿⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄ 
    ⠄⠄⠄⠄⠄⠄⣿⣿⠃⣦⣄⣿⣿⣿⠇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄ 
    ⠄⠄⠄⠄⠄⢸⣿⠗⢈⡶⣷⣿⣿⡏⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄ 
     
 */  
//======================================ArrayList(Vector)========================================================  
typedef struct ArrayList{  
    int length;  
    int maxCapacity;//計算目前陣列是否已經滿了  
    Object* data;  
}ArrayList;  
ArrayList* newArrayList(){  
    ArrayList* list = malloc(sizeof(ArrayList));  
    list->length = 0;  
    list->maxCapacity = 1;  
    list->data = malloc(list->maxCapacity * sizeof(Object));  
    return list;  
}  
void arrayList_add(ArrayList* list, Object value){  
    if (list->maxCapacity <= list->length){  
        list->maxCapacity *= 2;  
        Object* data = malloc(sizeof(Object) * list->maxCapacity);  
        for(int i = 0;i < list->length;i++){  
            data[i] = list->data[i];  
        }  
        for(int i = list->length;i < list->maxCapacity;i++){  
            data[i] = null;  
        }  
        //free(list->data);  
        list->data = data;  
    }  
    list->data[list->length] = value;  
    list->length++;  
}  
Object arrayList_get(ArrayList* list, int index){  
    assert(0<=index && index <list->length);  
    return list->data[index];  
}  
Object arrayList_peek(ArrayList* list){  
    return arrayList_get(list, list->length-1);  
}  
Object arrayList_pop(ArrayList* list){  
    Object obj = arrayList_peek(list);  
    list->length--;  
    return obj;  
}  
void arrayList_sort(ArrayList* list, int(*compareFunc)(const Object o1, const Object o2)){  
    //debug("arrayList.sort()\n");  
    //qsort(list->data, list->length, sizeof(Object), compareFunc);  
      
    int len = list->length;  
    for(int i = 0;i<len;i++){  
        int count = 0;  
        for(int j = 0;j<len-i-1;j++){  
            //debug("compare [%d] and [%d]\n", j, j+1);  
            int cmp = compareFunc(list->data[j], list->data[j+1]);  
            //debug("cmp=%lf\n", cmp);  
            if(cmp > 0){  
                //debug("swap\n");  
                Object temp = list->data[j];  
                list->data[j] = list->data[j+1];  
                list->data[j+1] = temp;  
                count++;  
            }  
            //debug("\n");  
        }  
        if(count==0)break;  
    }  
    //debug("sort complete\n");  
}  
boolean arrayList_contain(ArrayList* list, Object value){  
    int len = list->length;  
    for(int i = 0;i<len;i++){  
        if(list->data[i] == value)return true;  
    }  
    return false;  
}  
//================================================DequeNode========================================================  
struct DequeNode{  
    struct DequeNode* next;  
    struct DequeNode* previous;  
    Object value;  
};  
typedef struct DequeNode DequeNode;  
DequeNode* newDequeNode(Object value){  
    DequeNode* node = malloc(sizeof(DequeNode));  
    node->next = null;  
    node->previous = null;  
    node->value = value;  
    return node;  
}  
//=================================================Stack==========================================================  
typedef struct Stack{  
    DequeNode* head;  
    DequeNode* tail;  
    int size;  
}Stack;  
Stack* newStack(){  
    Stack* stack = malloc(sizeof(Stack));  
    stack->head = null;  
    stack->tail = null;  
    stack->size = 0;  
    return stack;  
}  
boolean stack_empty(Stack* stack){  
    return stack->size == 0;  
}  
  
void stack_add(Stack* stack, Object value){  
    assert(value != null);  
    DequeNode* node = newDequeNode(value);  
    if(stack_empty(stack)){  
        stack->head = node;  
        stack->tail = node;  
    }else{  
        stack->tail->next = node;  
        node->previous = stack->tail;  
        stack->tail = node;  
    }  
    stack->size++;  
      
}  
Object stack_peek(Stack* stack){  
    assert(stack_empty(stack)==false);  
    return stack->tail->value;  
}  
Object stack_pop(Stack* stack){  
      
    assert(stack_empty(stack)==false);  
    Object value = stack->tail->value;  
    assert(value != null);  
    if(stack->size == 1){  
        stack->tail = null;  
        stack->head = null;  
    }else{  
        stack->tail = stack->tail->previous;  
        stack->tail->next = null;  
    }  
    stack->size--;  
    //debug("pop complete\n");  
    return value;  
}  
//==========================================Queue=================================================================  
typedef struct Queue{  
    DequeNode* head;  
    DequeNode* tail;  
    int size;  
}Queue;  
Queue* newQueue(){  
    Queue* queue = malloc(sizeof(Queue));  
    queue->head = null;  
    queue->tail = null;  
    queue->size = 0;  
    return queue;  
}  
boolean queue_empty(Queue* queue){  
    return queue->size == 0;  
}  
  
void queue_add(Queue* queue, Object value){  
    DequeNode* node = newDequeNode(value);  
    if(queue_empty(queue)){  
        queue->head = node;  
        queue->tail = node;  
    }else{  
        queue->tail->next = node;  
        node->previous = queue->tail;  
        queue->tail = node;  
    }  
    queue->size++;  
}  
Object queue_peek(Queue* queue){  
    assert(queue_empty(queue)==false);  
    return queue->head->value;  
}  
Object queue_pop(Queue* queue){  
    assert(queue_empty(queue)==false);  
    DequeNode* node = queue->head;  
    if(queue->size == 1){  
        queue->tail = null;  
        queue->head = null;  
    }else{  
        queue->head = queue->head->next;  
        queue->head->previous = null;  
    }  
    queue->size--;  
    return node->value;  
}  

//=================================Scanner===================================================  
int scanner_nextInt(){
    int num = 0;
    scanf("%d", &num);
    return num;
}
Long scanner_nextLong(){
    Long num = 0;
    scanf("%lld", &num);
    return num;
}

typedef struct{
    int (*nextInt)();
    Long (*nextLong)();
}Scanner;

Scanner* newScanner(){
    Scanner* scanner = malloc(sizeof(Scanner));
    scanner->nextInt = scanner_nextInt;
    scanner->nextLong = scanner_nextLong;
    return scanner;
}
  
//=============================================================================================  

int cmp(const Object o1, const Object o2){
    return (*(int*)o1 - *(int*)o2);
}

int cmp2(const Object o1, const Object o2){
    return -(*(int*)o1 - *(int*)o2);
}

int* newInt(int num){
    int* i = malloc(sizeof(int));
    *i = num;
    return i;
}
    
int main(){ 
    Scanner* input = newScanner();
    Long num = input->nextLong();
    int day = num/86400;
    num = num %86400;
    int hour = num / 3600;
    num = num %3600;
    int min = num / 60;
    num = num % 60;
    int sec  = num;
    printf("%d days\n%d hours\n%d minutes\n%d seconds\n", day, hour, min, sec);

    return 0;  
}  
