#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
int random_in_range(int);

void print_board(int board[SIZE][SIZE]) {
    for (int j=0; j<SIZE; j++){
        for (int i=0; i<SIZE; i++){
            printf("%5d", board[j][i]);
        }
        printf("\r\n\r\n");
    }
}

void put_random_2_in(int board[SIZE][SIZE]){
    int flag = 0;
    while(flag == 0){
        int m = random_in_range(SIZE);
        int n = random_in_range(SIZE);
        if (board[m][n] == 0){
            board[m][n] = 2;
            flag = 1;
        }
    }
}

void move_up(int board[SIZE][SIZE]){
    int flag[SIZE] = {0, 0, 0, 0}; //各列の足し算は一回までなので
    for (int j=0; j<SIZE; j++){
        for (int i=1; i<SIZE; i++){
            if (board[i][j] != 0){
                for (int k=i-1; k>=0; k--){
                    if (board[k][j] == 0){
                        board[k][j] = board[k+1][j];
                        board[k+1][j] = 0;
                    }else if (board[k][j] == board[k+1][j])
                    {
                        if (flag[j]==0){
                            board[k][j] *= 2;
                            board[k+1][j] = 0;
                            flag[j] = 1;
                        }
                    }
                }
            }
        }
    }
}

void move_down(int board[SIZE][SIZE]){
    int flag[SIZE] = {0, 0, 0, 0}; //各列の足し算は一回までなので
    for (int j=0; j<SIZE; j++){
        for (int i = SIZE-2; i>=0; i--){
            if (board[i][j]!=0){
                for (int k=i+1; k<SIZE; k++){
                    if (board[k][j] == 0){
                        board[k][j] = board[k-1][j];
                        board[k-1][j] = 0;
                    }else if (board[k][j] == board[k-1][j])
                    {
                        if (flag[j]==0){
                            board[k][j]*=2;
                            board[k-1][j]=0;
                            flag[j] = 1;
                        }
                    }
                }
            }
        }
    }
}

void move_left(int board[SIZE][SIZE]){
    int flag[SIZE] = {0, 0, 0, 0}; //各行の足し算は一回までなので
    for (int i=0; i<SIZE; i++){
        for (int j=1; j<SIZE; j++){
            if (board[i][j] != 0){
                for(int k=j-1; k>=0; k--){
                    if (board[i][k]==0){
                        board[i][k] = board[i][k+1];
                        board[i][k+1] = 0;
                    }else if (board[i][k] == board[i][k+1])
                    {
                        if(flag[i]==0){
                            board[i][k]*=2;
                            board[i][k+1]=0;
                            flag[i]=1;
                        }
                    }
                }
            }
        }
    }
}

void move_right(int board[SIZE][SIZE]){
    int flag[SIZE] = {0, 0, 0, 0};
    for (int i=0; i<SIZE; i++){
        for(int j=SIZE-2; j>=0; j--){
            if (board[i][j]!=0){
                for (int k=j+1; k<SIZE; k++){
                    if (board[i][k]==0){
                        board[i][k] = board[i][k-1];
                        board[i][k-1] = 0;
                    }else if (board[i][k]==board[i][k-1])
                    {
                        if (flag[i] == 0){
                            board[i][k] *= 2;
                            board[i][k-1] = 0;
                            flag[i]=1;
                        }
                    }
                    
                }
            }
        }
    }
}


int main (int argc, char *argv[]) {
    int board[SIZE][SIZE] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    printf("Press any key to conitnue\n");
    int c;

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる

    while((c = getchar()) != '.') {
        system("clear");
        printf("Press '.' to close\r\n");
        // int a = random_in_range(SIZE);
        // int b = random_in_range(SIZE);
        // board[a][b] = '2';
        if (c=='i'){
            move_up(board);
        }else if (c == 'j')
        {
            move_left(board);
        }else if (c == 'm')
        {
            move_down(board);
        }else if (c == 'k')
        {
            move_right(board);
        }
        
        
        
        put_random_2_in(board);
        print_board(board);
        printf("You pressed '%c'\r\n", c);
    }

    system("/bin/stty cooked");  // 後始末

    return 0;
}

int random_in_range(int rand_max){
    return rand()%rand_max;
}
