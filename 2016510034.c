#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct record
{
 int id;
 int grade;
 char name[15];
 char surname[15];
 char email[26];
};

/*
  // Main function to do heap sort
  void heapSort(int arr[], int n, struct record rcd[5][32768], int row) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i, rcd, row);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);
      //swaprcd(&rcd[row][0], &rcd[row][i]);
  
      // Heapify root element to get highest element at root again
      heapify(arr, i, 0, rcd, row);
    }
}
void heapify(int arr[], int n, int i, struct record rcd[5][32768], int row) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      //swaprcd(&rcd[row][i], &rcd[row][largest]);
      heapify(arr, n, largest, rcd, row);
    }
  }
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

void swaprcd(struct record *rcd_1, struct record *rcd_2){
    
    struct record temp = *rcd_1;
    *rcd_1 = *rcd_2;
    *rcd_2 = temp;
}

*/

int main(int argc, char *argv[]){

    if(atoi(argv[4]) > 32 && atoi(argv[4]) < 1){
        printf("Invalid input !");
        exit(1);
    }

    if(atoi(argv[3]) > 5 && atoi(argv[4]) < 2){
        printf("Invalid input !");
        exit(1);
    }

    struct record buffer[atoi(argv[3])][atoi(argv[4]) * 16];

    int row = sizeof(buffer) / sizeof(buffer[0]);
    int column = sizeof(buffer[0]) / sizeof(buffer[0][0]);

    FILE *rp = fopen(argv[1], "r");
    FILE *wp = fopen(argv[2], "w");

    if(rp == NULL){
        printf("Couldn't open the file!");
        exit(1);
    }

    char line[1024];
    fgets(line, 1024, rp);
    printf("%s", line);

    char * token = strtok(line, ";");

    while( token != NULL ){
      printf("%s\n", token );
      token = strtok(NULL, ";");
    }

    for(int i = 0; i < row - 1; i++){
        for(int j = 0; j < column; j++){

            fgets(line, sizeof(struct record), rp);

            buffer[i][j].id = atoi(strtok(line, ";"));
            strcpy(buffer[i][j].name, strtok(NULL, ";"));
            strcpy(buffer[i][j].surname, strtok(NULL, ";"));
            strcpy(buffer[i][j].email, strtok(NULL, ";"));
            buffer[i][j].grade = atoi(strtok(NULL, ";"));
        }
    }

    for(int i = 0; i < row - 1; i++){
        int temp[column];
        for(int j = 0; j < column; j++){

            temp[j] = buffer[i][j].id;
        }
        for(int k = 0; k < column; k++){    // I had to do this sorting because I am getting segmentation fault with heapsort
            for( int l = 0; l < column - 1; l++){

                if(buffer[i][l].id > buffer[i][l + 1].id){
                    struct record tmp = buffer[i][l];
                    buffer[i][l] = buffer[i][l + 1];
                    buffer[i][l + 1] = tmp;
                }
            }
        }
    }

/*                        //RAN OUT OF TIME HERE SO COULDN'T FINISH THIS PART
    if(row == 5){
        int counter_a = 0;
        int counter_b = 0;
        int counter_c = 0;
        int counter_d = 0;

        for(int i = 0; i < column; i++){
            if(buffer[0][counter_a] < )
        }

    }
    else if(row == 4){
        int counter_a = 0;
        int counter_b = 0;
        int counter_c = 0;

    }
    else if(row == 3){
        int counter_a = 0;
        int counter_b = 0;

    }
    else{

    }

*/
    for(int i = 0; i < row - 1; i++){
        for(int j = 0; j < column; j++){

            fprintf(wp, "%d;%s;%s;%s;%d\n", buffer[i][j].id, buffer[i][j].name, buffer[i][j].surname, buffer[i][j].email, buffer[i][j].grade);
        }
    }







    fclose(rp);
    fclose(wp);
}