#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 9

#define SUM_I_9  SIZE * (SIZE +1) / 2




// Sudoku board. Modify this to test your checker!
// 0 == empty cell; 1-9 is the filled in digit.
int board[SIZE][SIZE] = {
    {2,3,1,8,7,9,4,5,6}, 
    {8,7,9,4,5,6,2,3,1},
    {6,5,4,2,3,1,8,7,9},
    {1,2,3,5,4,6,7,8,9},
    {7,8,9,1,2,3,5,4,6},
    {5,4,6,7,8,9,1,2,3},
    {3,2,1,7,9,8,4,5,6},
    {7,9,8,4,5,6,3,2,1},
    {4,5,6,3,2,1,7,9,8},
};
//All rows should pass
//All boxes should pass
//All columns should not pass

bool row_check[SIZE];
bool col_check[SIZE];
bool box_check[SIZE];

void printBoard(int board[SIZE][SIZE]) {
    for(int i = 0; i<SIZE; i++) {
        for(int j = 0; j<SIZE; j++) {
            printf("%5d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Checks the given row for duplicate numbers, and updates the row_check
// value for that row appropriately. If no number is repeated in that row,
// row_check[row] will be set to true; otherwise, it will be false.
void* checkRow(void* args) {
    // 1+ 2+ ... + n = n(n+1) / 2,'
    int i, j, sum;

    for(i = 0; i < SIZE; i++){    // iterates across all rows
        sum = 0;
        for(j = 0; j <SIZE; j++){  // check 1 row
             sum += board[i][j];
        }
        
        if(sum == SUM_I_9)
            row_check[i] = true;
        else
            row_check[i] = false;
        
    }
    
    return NULL;
}

// Checks the given col for duplicate numbers, and updates the col_check
// value for that col appropriately. If no number is repeated in that col,
// col_check[col] will be set to true; otherwise, it will be false.
void* checkCol(void* args) {
    int i, j, sum;

    for(i = 0,sum = 0; i < SIZE; i++){    // iterates across all cols
        for(j = 0; j < SIZE; j++){  // check 1 cols
             sum += board[j][i];
        }
        
        if(sum == SUM_I_9)
            col_check[i] = true;
        else
            col_check[i] = false;
        
    }
    
    return NULL;
}


// Checks the given 3x3 box for duplicate numbers, and updates the box_check
// value for that box appropriately. If no number is repeated in that box,
// box_check[box] will be set to true; otherwise, it will be false.
void* checkBox(void* args) {

    int i, j, sum;

    for(i = 0,sum = 0; i < 3; i++){    // iterates across first box
        for(j = 0; j < 3; j++){  // check 1 box
             sum += board[i][j];
        }
    }

    if(sum == SUM_I_9)
        box_check[0] = true;
    else
        box_check[0] = false;
        
    for(i = 3,sum = 0; i < 6; i++){    // iterates across second box
        for(j = 0; j < 3; j++){  // check 1 box
             sum += board[i][j];
        }
    }
    
    if(sum == SUM_I_9)
        box_check[1] = true;
    else
        box_check[1] = false;

    for(i = 6,sum = 0; i < 9; i++){    // iterates across third box
        for(j = 0; j < 3; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[2] = true;
    else
        box_check[2] = false;

//row two-------------------------
    for(i = 0,sum = 0; i < 3; i++){    // iterates across forth box
        for(j = 3; j < 6; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[3] = true;
    else
        box_check[3] = false;

    for(i = 3,sum = 0; i < 6; i++){    // iterates across fifth box
        for(j = 3; j < 6; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[4] = true;
    else
        box_check[4] = false;

    for(i = 6,sum = 0; i < 9; i++){    // iterates across sixth box
        for(j = 3; j < 6; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[5] = true;
    else
        box_check[5] = false;

    
//row three-------------------


    for(i = 0,sum = 0; i < 3; i++){    // iterates across seventh box
        for(j = 6; j < 9; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[6] = true;
    else
        box_check[6] = false;

    
    for(i = 3,sum = 0; i < 6; i++){    // iterates across eight box
        for(j = 6; j < 9; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[7] = true;
    else
        box_check[7] = false;

    for(i = 6,sum = 0; i < 9; i++){    // iterates across ninth box
        for(j = 6; j < 9; j++){  // check 1 box
             sum += board[i][j];
        }
       
    }
    
    if(sum == SUM_I_9)
        box_check[8] = true;
    else
        box_check[8] = false;

    return NULL;
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() { 
    // 1. Print the board.
    printf("Board:\n");
    printBoard(board);
    
    // 2. Create pthread_t objects for our threads.
    pthread_t row_thread;
    pthread_t col_thread;
    pthread_t box_thread;
    
    // 3. Create a thread for each cell of each matrix operation.
    pthread_create(&row_thread, NULL, checkRow, (void*)NULL);
    pthread_create(&col_thread, NULL, checkCol, (void*)NULL);
    pthread_create(&box_thread, NULL, checkBox, (void*)NULL);

    // 4. Wait for all threads to finish.
    pthread_join(row_thread, NULL);
    pthread_join(col_thread, NULL);
    pthread_join(box_thread, NULL);
    
    // 5. Print the results.
    printf("Results:\n");
    bool all_rows_passed = true;
    printf("Rows:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!row_check[i]) {
            printf("Row %i did not pass\n", i);
            all_rows_passed = false;
        }
    }
    if (all_rows_passed) {
        printf("All rows passed!\n");
    }
    
    bool all_cols_passed = true;
    printf("Cols:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!col_check[i]) {
            printf("Col %i did not pass\n", i);
            all_cols_passed = false;
        }
    }
    if (all_cols_passed) {
        printf("All cols passed!\n");
    }
    
    bool all_boxes_passed = true;
    printf("Boxes:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!box_check[i]) {
            printf("Box %i did not pass\n", i);
            all_boxes_passed = false;
        }
    }
    if (all_boxes_passed) {
        printf("All boxes passed!\n");
    }
    return 0;
}

