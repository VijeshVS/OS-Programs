#include <stdio.h>
#include <stdlib.h>

int search(int arr[],int size,int key){
    int ind = -1;

    for(int i = 0;i<size;i++){
        if(arr[i] == key) {
            ind = i;
            break;
        }
    }

    if(ind == -1){
        printf("Element could not be found !!\n");
    }
    else{
        printf("Element is found at the index %d\n",ind);
    }
}

int main(){
    int arr[] = {1,2,3,4,5};

    search(arr,5,3);
}