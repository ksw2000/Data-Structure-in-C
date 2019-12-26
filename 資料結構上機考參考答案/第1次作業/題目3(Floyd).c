/*
    This question is required to use 'stack' or 'queue'
    But Floyd-Warshall algorithm neither needs stack nor queue
*/
#include<stdio.h>
#include<stdlib.h>
#define INFINITE 99999

int main(){
//Phase1: Read file
    FILE* f=fopen("input3.txt","r");
    if(!f){
        fprintf(stderr,"Cannot open input3.txt");
        exit(1);
    }
    int i,j,k;
    char c;
	int adj_matrix[7][7],tmp;
	for(i=0; i<7; i++){
    	for(j=0; j<7; j++){
    		fscanf(f,"%d",&tmp);
    		adj_matrix[i][j]=(tmp==0)? INFINITE:tmp;
		}
	}
	fclose(f);

	//print for debuging
	for(i=0; i<7; i++){
    	for(j=0; j<7; j++){
    		printf("%5d ",adj_matrix[i][j]);
		}
		printf("\n");
	}

//Phase2: Floyd-Warshall algorithm
    //Notice: i,j,k can not be interchange
	for(i=0; i<7; i++){
		for(j=0; j<7; j++){
			for(k=0; k<7; k++){
				if(adj_matrix[j][k] > adj_matrix[j][i] + adj_matrix[i][k]){
					adj_matrix[j][k] = adj_matrix[j][i] + adj_matrix[i][k];
				}
			}
		}
	}

	printf("\n");
	//print for debuging
	for(i=0; i<7; i++){
    	for(j=0; j<7; j++){
    		printf("%5d ",adj_matrix[i][j]);
		}
		printf("\n");
	}

	printf("\nans:%d\n",adj_matrix[0][6]);

//Phase3: Write to file
    f=fopen("output3.txt","w");
    fprintf(f,"%d",adj_matrix[0][6]);
    fclose(f);

 	system("pause");
    return 0;
}
