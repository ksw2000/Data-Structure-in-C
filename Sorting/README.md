# Data Structure Chapter 7 Sorting

期末考考試範圍

ch5的p15~ch7的p49

## 7.1 Motivation

### Sequential Search

O(n)

### Binary search

```c
int binsearch(element list[], int searchnum, int n){
/*search list[0],...,list[n-1]*/
    int left=0, right=n-1, middle;
    while(left<=right){
        middle=(left+right)/2;
        switch(COMPARE(list[middle],key, searchnum)){
            case -1:
                left=middle+1;    //right
                break;        
            case 0:
                return middle;
            case 1:               //left
                right=middle-1;
                break;                
        }
    }
    return -1;
}
```

O(log<sub>2</sub>n)

## 7.2 Insertion Sort

建立一個 insert 函數可以把 e 插入 1 到 i 已排序的陣列中，插入後會有 1 到 i+1 個排好的陣列，另一方面，再插入時是由後面往前面插

```c
/*insert e into the ordered list a[1:i] s.t. the resulting list a[i:i+1] is also ordered, the array a must have space allocated for at least i+2 elements*/
void insert(element e, element a[], int i){
    a[0]=e;
    while(e.key<a[i].key){
        a[i+i]=a[i];
        i--;        
    }
    a[i+1]=e;
}
```

```c
/*sort a[i:n] into non-decreasing order*/
void insertionSort(element a[], int n){
    for(j=2; j<n; j++){
        element temp=a[j];
        insert(temp, a, j-1);
    }
}
```

#### Supplement: Section Sort

實作步驟

1. 取得要排序的數字

2. 找出最小值

3. 從未排序的陣列中選出最小的並與未排序的最開頭交換

| 40 48 24 55 **19** 89    (將19與40交換)

19 | 48 **24** 55 40 89    (將24與48交換)

19 24 | 48 55 **40** 89    (將40與48交換)

19 24 40 | 55 **48** 89    (將48與55交換)

19 24 40 48 | **55** 89

19 24 40 48 55 | 89

```c
void selectionSort(int array[], int len){
    int smallest; /*index of smallest element*/
    int i,j; /*used in for loops*/

    /*loop over len-1 elements*/
    for(i=0; i<len-1; i++){
        smallest=i; /*first index of remaining array*/

        /*loop to find index of smallest element*/
        for(j=i+1; j<len; j++){
            if(array[j]<array[smallest]){
                smallest=j;
            }        
        }

        
    }
}
```

worst case: **O(n<sup>2</sup>)** best case: **O(n)**

## 7.3 Quick Sort

實作步驟

1. 取得要排序的數字

2. 設 left 為 pivot

3. 從 **left** 開始找出比pivot**大**的值

4. 從**right**開始找出比pivot**小**的值

5. **把3,4步驟的值進行交換**

6. 重複2 ~ 5 直到排序完成

```c
/*sort a[left:right] into nondecreasing order on the key field; a[left].key is arbitrarily chosen as the pivot key; it is assumed that a[left].key <= a[right+1].key*/
void quickSort(element a[], int left, int right){
    int pivot, i, j;
    element temp;
    if(left<right){
        i=left;
        j=right+1;
        pivot=a[left].key;
        do{
            /*search for keys from the left and right sublists, swapping out-or-order elements until the left and right boundaries cross or meet*/
            do{i++;}while(a[i].key<pivot);
            do{j--;}while(a[j].key>pivot);
            if(i<j){
                SWAP(a[i],a[j],temp)
            }
        }while(i<j);
        quickSort(a, left, j-1);
        quickSort(a, j+1, right);
    }
}
```
