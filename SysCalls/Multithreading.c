#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

int a[4][4],b[4][4];

void *matrixEvaluation(void* val){
    int row = *(int *)(val);

    for(int i = 0;i<4;i++){
        b[row][i] = a[row][i];
    }

    for(int i = 0;i<4;i++){
        for(int j = 0;j<row;j++){
            b[row][i] *= a[row][i];
        }
    }

    printf("\nMatrix Evaluation at %d",row);
}

int main(){
    pthread_t p[4];
    
    printf("Assigning each row elements to its row number !!\n");
    
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            a[i][j] = i+1;
        }
    }

    for(int i = 0;i<4;i++){
        pthread_create(&p[i],NULL,matrixEvaluation,&i);
        sleep(1);
    }

    for(int i = 0;i<4;i++){
        pthread_join(p[i],NULL);
    }

    printf("\n");

    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}