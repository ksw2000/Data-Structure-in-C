#include<stdio.h>
#include<stdlib.h>
void swap(int* a, int* b){
	int tmp=*a;
	*a = *b;
	*b = tmp;
}

int main(){
//Phase1: Read file
    FILE* f=fopen("input1.txt","r");
    if(!f){
        fprintf(stderr,"Cannot open input1.txt");
        exit(1);
    }
    int i,j,tmp;
	int bounding, object_weight[10], object_unit_price[10];
    fscanf(f,"%d",&bounding);
    for(i=0; i<10; i++){
    	fscanf(f,"%d",&object_weight[i]);	             //(weight)
	}
	for(i=0; i<10; i++){
		fscanf(f,"%d",&tmp);	                         //(price)
		object_unit_price[i] = tmp/object_weight[i];     //(unit_price)
	}
	fclose(f);

//Phase2: Sort by unit_price
	for(i=0; i<10; i++){
		for(j=0; j<10-i-1; j++){
			if(object_unit_price[j]<object_unit_price[j+1]){
				swap(&object_unit_price[j], &object_unit_price[j+1]);
				swap(&object_weight[j], &object_weight[j+1]);
			}
		}
	}

//Phase3: Print array for debugging
	for(i=0; i<10; i++){
		printf("%d ",object_unit_price[i]);
	}
	printf("\n");
	for(i=0; i<10; i++){
		printf("%d ",object_weight[i]);
	}
	printf("\n");

//Phase4: Greedy. Get objects as many as possible
	int max_price=0;
	for(i=0; i<10 ; i++){
		if(bounding-object_weight[i]>=0){
			bounding -= object_weight[i];
			max_price += object_weight[i]*object_unit_price[i];
		}else{
			break;
		}
	}

	if(i!=10){
		max_price += bounding * object_unit_price[i];
	}

    printf("max_price:%d\n",max_price);

//Phase5: Write to file
 	f=fopen("output1.txt","w");
 	fprintf(f,"%d",max_price);
 	fclose(f);

 	system("pause");
    return 0;
}
