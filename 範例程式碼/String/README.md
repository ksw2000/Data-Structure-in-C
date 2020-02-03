# 常用的 string 函數
在資料結構的課堂上可能會需要用到一些字串的操作。在操作字串時雖然可以自己土法鍊鋼寫一函數，但用函數庫預設的方便許多，以下提到的函數除了第一個其他都要 include string.h

## 1. 超實用 sprintf()
sprintf()簡單易學，雖然速度是慢了點。另外 sprintf() 是 stdio.h 裡的函數所以不用再另外 include string.h

<pre><code>
int sprintf(char&ast; str, const char&ast; format, ...)
</pre></code>

這個函數其實很好懂，主要就是你可把你想 printf() 出的結果傳到str裡

**注意：str必需是陣列或指向一塊足夠大空間的指標**

#### 拼接兩字串
<pre><code>
char str1[]="hello ";
char str2[]="world";
char result[16];
sprintf(result, "%s%s", str1, str2);

printf("%s",result);
//hello world
</pre></code>

#### 複製字串
<pre><code>
char str_ori[]="Taiwan NO.1";
char str_copy[16];
sprintf(str_copy, "%s", str_ori);

printf("%s",str_copy);
//Taiwan NO.1
</pre></code>

#### 任意型態轉換為字串( sprintf() 最佳優勢 )
<pre><code>
int a=10;
char b='A';
float c=9.487;
char str[16];
sprintf(str,"%d %c %.3f", a, b, c);

printf("%s",str);
//10 A 9.487
</pre></code>

## 2. strcmp() string comparison 比較兩字串
<pre><code>
int strcmp(const char&ast; str1, const char&ast; str2)
/&ast;
如果返回值 = 0，則表明str1 等於 str2
如果返回值 < 0，則表明str1 小於 str2
如果返回值 > 0，則表明str2 小於 str1
這裡指的小於是由左至右比較 ASCII 值，另外回傳的確切值，由不同編譯器決定，一般是 1 或 -1
&ast;/
</pre></code>

我們一般主要利用兩字串相等回傳0的特性即可

<pre><code>
if(!strcmp(str,"student")){
    //TODO
}
</pre></code>

## 3. strlen() string length 返回字串長度(字元數)

    printf("%d ",strlen("abc"));
    //3

要注意的是，中文字在UTF8的情形下是由3個字元拼起來的，如果你用的是 VScode 或 Atom 將得到以下結果

    printf("%d ",strlen("中文"));
    //6

如果你用的是 dev C++ 他採用Big5編碼，中文字算2個字元

    printf("%d ",strlen("中文"));
    //4

---
**以下函數皆可由 sprintf 實現**

## 4. strcat() string concatenation 字串拼接
將一個字串拼接到另一個字串的後面
<pre><code>
char&ast; strcat(char&ast; dest, const char&ast; src)
</pre></code>

把 src 加在 dest 後面，並回傳拼完的字串，但其實dest就是拼接完的結果，所以一般不用特別再宣告新的變數去接回傳值

## 5. strcpy() string copy 字串複製
將一個字串複製到另一個字串
<pre><code>
char&ast; strcpy(char&ast; dest, const char&ast; src)
</pre></code>
strcpy()可以將src字串複製到dest裡面，並回傳複製完的新字串，但其實dest就是複製後的結果，所以一般不用特別再宣告新的變數去接回傳值
