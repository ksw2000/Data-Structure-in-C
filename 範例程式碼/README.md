# C語言概念澄清
**某學長犧牲寒假編寫，信哥一把，全部看完保證收獲滿滿。**

**興大志工隊社員熱情招幕中**

## 1. 請釐清 C 與 C++ 不同之處

### I. 物件導向 OOP 特性
C++ 支持物件導向(oop) 但 C 不支援，雖然經過爆改 C 還是可以用物件導向的，但基本上還是認為 C 不支援物件導向，這可能也是各位這輩子碰到少數幾個不能使用物件導向的程式語言。

### II. for迴圈內宣告變數

這種寫法只有 C++, Java 支援

    for(int i=0; i<10; i++){

    }

C 語言的正確寫法如下

    int i;
    for(i=0; i<10; i++){

    }

另外其他需要宣告變數的程式語言，基本上都能接受第一種方法的邏輯，舉例

GO

    for i:=0; i<10; i++{

    }

JavaScript

    for(let i=0; i<10; i++){

    }

### III. malloc 後的型態

也許你在許多教科書上會看到這種寫法

    int* arr;
    arr=(int*)malloc(sizeof(int) * 10);

在 C 語言中此舉是 **脫褲子放屁**，malloc() 這整串的回傳值是 **(void*)** 這個有點難懂，反正你只要知道這種型態丟給誰都能接受就是了，不需要再轉型

但是，在 C++ 中 (void\*) 並不能直接丟給 (int\*) 他們是不一樣的東西，所以才有這種轉型的寫法，不過值得一題的是，在 C++ 中有 new 可以宣告記憶體啊，用 malloc 幹嘛？除非是有腦袋撞到的低能助教叫大家寫 C 語言存 .cpp 就 2018 入學那屆的，還有哪屆有低能助教我們再陸續追蹤！

C語言

    int* arr;
    arr=malloc(sizeof(int) * 10);

C++

    //建議
    int* arr;
    arr=new int[10];

    //不建議
    int* arr;
    arr=(int*)malloc(sizeof(int) * 10)

Java

    //沒有指標
    //但宣告陣列時一樣用new

## 2. 正確的 main()

錯誤 (反正就是不正確我也不知道怎麼說)

    void main(){

    }

正確

    // 不接受額外的參數
    int main(){

        return 0;
    }

    // 接受額外的參數
    int main(int argc, char** args){

    }

## 3. typedef 的實際用途

假設我宣告了一個結構體叫做 tree

    struct t{
        int val;
        struct t* left;
        struct t* right;
    };

    typedef struct t tree;

此時，如果我要用tree的指標變數我這樣寫：

    tree* a,b,c;

這時會出現問題，編譯器會以為你是這個意思：

    struct tree* a, b, c;
    //只有 a 是指標變數，其他都不是

其實這時你可以寫成這樣：

<pre><code>
tree &ast;a,&ast;b,&ast;c;
//a,b,c 都確確實實是指標變數
</pre></code>

但這樣有點複雜，這時如果把指標變數也 typedef 就不會出現這種問題：

    struct t{
        int val;
        struct t* left;
        struct t* right;
    };

    typedef struct t tree;
    typedef struct t* treePointer;

    treePointer a,b,c;
    //a,b,c 都確確實實是指標變數

## 4. 請釐清全域、區域變數及指標變數使用時機
簡而言之，如果我在 main() 裡有個變數叫 foo ，另外我自定義一個函數叫 modify() ，如果我今天要更動 foo 內的值時沒有辦法只透過 foo ，而必需是 foo 的位置，即 &foo。透過 &foo 我就可以改變 foo 的值

將變數 foo 增為 10 倍
<pre><code>
void modify(int* p){
    &ast;p=(&ast;p)&ast;10;
}

int main(){
    int foo=10;
    modify(&foo);
    return 0;
}
</pre></code>

如果你看不懂以上的程式碼，代表你對指標不夠熟悉。以下是簡單的指標複習：
[超連結(待補)]

你以為結束了嗎？沒有！這只是改變 int 的簡單示範，在資料結構的課程中更常見是改變 int* 的值，也就是你現在需要透過兩個星星來改變一個星星。(按：雖然我比較常講米字號，&ast; 長得根本不像星星啊)
<pre><code>
&num;include&lt;stdio.h&gt;
&num;include&lt;stdlib.h&gt;

struct s{
    int val;
    struct s&ast; next;
};
typedef struct s&ast; stack;
typedef struct s&ast;&ast; stackPointer;

void push(stackPointer p, int val){
    stack newElement=malloc(sizeof(stack*));
    newElement->val=val;
    newElement->next=&ast;p;

    &ast;p=newElement;
    // 如果看不懂上面那行請再回去看一下前一個例子的 modify()
    // 因為沒有辦法在別的函數直接更改stack的值
    // 所以透過stack的位置來進行更改(即俗稱的雙重指標)
}

int main(){
    stack foo=NULL;
    push(&foo,10);
    push(&foo,14);
    push(&foo,18);

    return 0;
}
</pre></code>

## 5. 只有指標變數可以設為 NULL，也只有指標變數可以 free()
如標題，之前看到同學把不是指標的東西free掉，差點吐血

**如果你是菜雞請把一開始的指標變數都指向NULL**

如果你是菜雞就照作，如果不是的話那就隨便你，因為菜雞們常常會忘記設成NULL導致後面問題一堆，而且還debug不到呢！

## 6. 請務必釐清 for 迴圈的運作
因為大家太常只把 for 用來做只跑幾次，所以基本上都把 for 的初衷給忘了

for迴圈一共分為 3 段

    for( A ; B ; C ){
        D
    }

其中for迴圈 run 下來是這樣的
1. A 就是進入 for 迴圈之前會幹的事 (一定會做，一定會幹！很重要但我懶得打三遍)
2. 接著進入 B 如果 B 是錯的，直接離開，如果 B 是對的，就進入 D (這步很關鍵 A 做完會到 B 不是到 C，常常有人根本搞不懂)
3. D 執行完後會跳到 C
4. C 執行完後會跳到 B 如果 B 是錯的，直接離開，如果 B 是對的，就進入 D
5. 重複第 3 點

舉個例子(用for迴圈遍歷一個stack)

<pre><code>
&num;include&lt;stdio.h&gt;
&num;include&lt;stdlib.h&gt;

struct s{
    int val;
    struct s&ast; next;
};
typedef struct s&ast; stack;
typedef struct s&ast;&ast; stackPointer;

void push(stackPointer p, int val){
    //省略
}

int main(){
    stack foo=NULL;
    push(&foo,10);
    push(&foo,14);
    push(&foo,18);

    //----------------重點----------------//
    stack cur=NULL;
    for(cur=foo; cur!=NULL; cur=cur->next){
        printf("%d ", cur->val);
    }
    //------------------------------------//

    return 0;
}
</pre></code>
如果你看不懂那沒關係，只要觀念懂了，以後應該漸漸能了解

## 7. 條件式就是 1 或 0
考慮以下情況

    printf("%d",10>9);

會印出 1 ，懂？

    printf("%d",10<9);

會印出 0 ，懂？

所以 if 是怎麼運作的，if裡面放 0 就不幹，放 非0 就幹

    if(1){
        //這會執行
    }
    if(-1){
        //這也會執行
    }
    if(3){
        //這也會執行
    }
    if(0){
        //這裡不會執行
    }

    //------而一般常見的是長這樣------
    if(8>9){
        //這裡不會執行
    }

    //你可以把剛剛的if看成這樣
    if(0){

    }

    if(9>8){
        //這裡會執行
    }

    //你可以把剛剛的if看成這樣
    if(1){

    }

為什麼要講這個呢？
1. 因為有時候會看到一些程式把「條件式」當成函數回傳值，這是OK的
2. 有些需要放條件式的地方不需要放條件式

第一點我舉個例子

    //if a>b return 1 else return 0
    int big(int a, int b){
        if(a>b){
            return 1;
        }else{
            return 0;
        }
    }

以上的程式可以直接換成這樣

    int big(int a, int b){
        return a>b;
    }

第二點我舉個例子

    int* f;

    //...中間省略...

    if(f!=NULL){
        //blablabla
    }

以上的程式可以直接換成這樣

    int* f;

    //...中間省略...

    if(f){
        //blablabla
    }

## 8. 請務必熟悉字串的相關操作
[連結待補]

## 9. 經常出現的 Bug
[連結待補]
