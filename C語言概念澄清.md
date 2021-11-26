# C語言概念澄清

## 1. 請釐清 C 與 C++ 不同之處

### I. 物件導向 OOP 特性
C++ 支持物件導向(oop) 但 C 不支援，雖然經過爆改 C 還是可以用物件導向的，但基本上還是認為 C 不支援物件導向。

### II. for迴圈內宣告變數

這種寫法只有 C++, Java 支援

```java
for(int i=0; i<10; i++){

}
```

C 語言的正確寫法如下

```c
int i;
for(i=0; i<10; i++){

}
```

這裡指的是 ANSI C 的標準，在新的 C 語言標準中，C99, C11 都是允許的，但我們還是以傳統的寫法為主，這樣能讓比較舊的編譯器接受

### III. malloc 後的型態

也許你在許多教科書上會看到這種寫法

```c
int* arr;
arr = (int*)malloc(sizeof(int) * 10);
```

在標準 C 語言中此舉是**脫褲子放屁**，malloc() 這回傳值為 `void*` ，意思是任意指標，在標準 C 語言中 `void*` 可以隱式轉換成其他指標型態

但是，在 C++ 中 `void*` 並不能直接丟給 `int*` ，編譯器會視他們為不同東西，所以才有這種轉型的寫法，不過值得一題的是，在 C++ 中有 new 可以宣告記憶體啊，用 malloc 幹嘛？除非是有腦袋撞到的低能助教叫大家寫 C 語言存 .cpp 就 2018 入學那屆的，還有哪屆有低能助教我們再陸續追蹤！

C語言

```c
int* arr;
arr = malloc(sizeof(int) * 10);
```

C++
```cpp
//建議
int* arr;
arr = new int[10];

//不建議
int* arr;
arr = (int*)malloc(sizeof(int) * 10)
```
Go
```go
var arr *int
arr = new(int)
```

## 2. 正確的 main()

錯誤

```cpp
void main(){

}
```

正確

```c
// 不接受額外的參數
int main(){

    return 0;
}

// 接受額外的參數
int main(int argc, char** args){

}
```

## 3. typedef 配合指標的用途

假設我宣告了一個結構體叫做 tree

```c
struct t{
    int val;
    struct t* left;
    struct t* right;
};

typedef struct t tree;
```

此時，如果我要宣告3個tree的指標變數，而我這樣寫：

```c
tree* a,b,c;
```

```c
//編譯器會以為你是這個意思：
struct tree* a, b, c;

//其實也是這個意思:
struct tree *a, b, c;

//此時只有 a 是指標變數，其他都不是
```

其實這時你可以寫成這樣：

```c
tree *a,*b,*c;
//a,b,c 都確確實實是指標變數
```

但這樣有點複雜，這時如果把指標變數也 typedef 就不會出現這種問題：

```c
struct t{
    int val;
    struct t* left;
    struct t* right;
};

typedef struct t tree;
typedef struct t* treePointer;

treePointer a,b,c;
//a,b,c 都確確實實是指標變數
```

## 4. 請釐清全域、區域變數及指標變數使用時機
簡而言之，如果我在 main() 裡有個變數叫 foo ，另外我自定義一個函數叫 modify() ，如果我今天要更動 foo 內的值時沒有辦法只透過 foo ，而必需是 foo 的位置，即 &foo。透過 &foo 我就可以改變 foo 的值

將變數 foo 增為 10 倍
```c
void modify(int* p){
    *p = (*p) * 10;
}

int main(){
    int foo=10;
    modify(&foo);
    return 0;
}
```

如果你看不懂以上的程式碼，代表你對指標不夠熟悉。

你以為結束了嗎？沒有！這只是改變 int 的簡單示範，在資料結構的課程中更常見是改變 int* 的值，也就是你現在需要透過兩個星星來改變一個星星。

```c
#include<stdio.h>
#include<stdlib.h>

struct s{
    int val;
    struct s* next;
};
typedef struct s* stack;
typedef struct s** stackPointer;

void push(stackPointer p, int val){
    stack newElement = malloc(sizeof(stack*));
    newElement->val = val;
    newElement->next = *p;

    *p = newElement;
    // 如果看不懂上面那行請再回去看一下前一個例子的 modify()
    // 因為沒有辦法在別的函數直接更改stack的值
    // 所以透過stack的位置來進行更改(即俗稱的雙重指標)
}

int main(){
    stack foo = NULL;
    push(&foo, 10);
    push(&foo, 14);
    push(&foo, 18);

    return 0;
}
```

## 5. 只有指標變數可以設為 NULL

**宣告指標變數後一律先指向NULL**

常常會忘記設成NULL導致後面問題一堆，而且還會 debug 不到哦！

## 6. 請務必釐清 for 迴圈的運作
因為大家太常只把 for 用來做只跑幾次，所以基本上都把 for 的初衷給忘了

for迴圈一共分為 3 段

```c
for( A ; B ; C ){
    D
}
```

其中for迴圈 run 下來是這樣的
1. A 就是進入 for 迴圈之前會幹的事
2. 接著進入 B 如果 B 是錯的，直接離開，如果 B 是對的，就進入 D (這步很關鍵 A 做完會到 B 不是到 C，常常有人根本搞不懂)
3. D 執行完後會跳到 C
4. C 執行完後會跳到 B 如果 B 是錯的，直接離開，如果 B 是對的，就進入 D
5. 重複第 3 點

舉個例子(用for迴圈遍歷一個stack)

```c
#include<stdio.h>
#include<stdlib.h>

struct s{
    int val;
    struct s* next;
};
typedef struct s* stack;
typedef struct s** stackPointer;

void push(stackPointer p, int val){
    //省略
}

int main(){
    stack foo = NULL;
    push(&foo,10);
    push(&foo,14);
    push(&foo,18);

    //----------------重點----------------//
    stack cur = NULL;
    for(cur = foo; cur != NULL; cur = cur->next){
        printf("%d ", cur->val);
    }
    //------------------------------------//

    return 0;
}
```

如果你看不懂那沒關係，只要觀念懂了，以後應該漸漸能了解

## 7. 條件式就是 0 或 1 (非0)
考慮以下情況

```c
printf("%d", 10 > 9); // 1
printf("%d", 10 < 9); // 0
```

所以 if 是怎麼運作的呢？if 裡面放`0`就不做，放`非0`就做

```c
if(1){
    // 這會執行
}
if(-1){
    // 這也會執行
}
if(3){
    // 這也會執行
}
if(0){
    // 這裡不會執行
}

//------而一般常見的是長這樣------
if(8 > 9){
    // 這裡不會執行
}

// 你可以把剛剛的if看成這樣
if(0){

}

if(9 > 8){
    // 這裡會執行
}

// 你可以把剛剛的if看成這樣
if(1){

}
```

為什麼要講這個呢？
1. 因為有時候會看到一些程式把「條件式」當成函數回傳值，這是OK的
2. 有些需要放條件式的地方不需要放條件式

第一點我舉個例子

```c
// if a > b return 1 else return 0
int big(int a, int b){
    if(a > b){
        return 1;
    }else{
        return 0;
    }
}
```

以上的程式可以直接換成這樣

```c
int big(int a, int b){
    return a>b;
}
```

第二點我舉個例子

```c
int* f;

//...中間省略...

if(f!=NULL){
    //blablabla
}
```

以上的程式可以直接換成這樣

```c
int* f;

//...中間省略...

if(f){
    //blablabla
}
```

## 8. 請務必熟悉字串的相關操作
[字串操作大補帖](https://github.com/liao2000/Data-Structure-in-C/tree/master/String)

## 9. 請務必理解記憶體的分配

<img src="https://blog.gtwang.org/wp-content/uploads/2017/03/memory-layout-of-c-program-diagram-20170301-1024x962.png" style="max-width:450px; width:100%;">

```c
#include <stdio.h>
const int global_x = 1;  // 儲存於 data 區段（唯讀區域）
int global_y = 1;        // 儲存於 data 區段（可讀寫區域）
int global_z;            // 儲存於 bss 區段
int main() {
  const static int x = 1; // 儲存於 data 區段（唯讀區域）
  static int y = 1;       // 儲存於 data 區段（可讀寫區域）
  static int z;           // 儲存於 bss 區段
  int w = 1;              // 儲存於 stack 區段

  // 儲存於 heap 區段
  char* buf = malloc(sizeof(char) * 100);
  // ...
  free(buf);

  return 0;
}
```

**malloc() & free() 說明**
+ malloc() 底層是呼叫 system call 請 OS 實作
+ C 語言不會去記得 `buf` 所指向的記憶體有多大！但 OS 本身會
+ free() 底層也是呼叫 system call 請 OS 實作
+ 雖然 C 語言不記得 `buf` 原本指向有多大，但 OS 記得，所以當初宣告多大，free() 就清空多大的記憶體！
+ **在 C 語言中只有 Heap 區可以 free()**

參考：[https://blog.gtwang.org/programming/memory-layout-of-c-program/](https://blog.gtwang.org/programming/memory-layout-of-c-program/)


<img src="./迷因/老娘直接把你的bss區free掉.png" style="max-width:300px; width:100%;">

## 廣告 學員偶像社 熱情招生

[![](https://school-idol-nchu.github.io/img/%E7%AC%AC0%E5%B1%86%E6%96%87%E5%AE%A3.png)](https://school-idol-nchu.github.io/)
