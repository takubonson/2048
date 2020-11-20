#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 4
int random_in_range(int);
void print_board(int [SIZE][SIZE]);
void put_random_2_in(int [SIZE][SIZE]);
void start_game(int [SIZE][SIZE]);
void move_up(int [SIZE][SIZE]);
void move_down(int [SIZE][SIZE]);
void move_left(int [SIZE][SIZE]);
void move_right(int [SIZE][SIZE]);


int main (int argc, char *argv[]) {
    int board[SIZE][SIZE] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    printf("Press any key to conitnue\n");
    int c;
    system("clear");
    printf("Press '.' to close\r\n");
    start_game(board);
    print_board(board);

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる

    while((c = getchar()) != '.') {
        system("clear");
        printf("Press '.' to close\r\n");
        if (c == 'A'){
            move_up(board);
            put_random_2_in(board);
        }else if (c == 'D')
        {
            move_left(board);
            put_random_2_in(board);
        }else if (c == 'B')
        {
            move_down(board);
            put_random_2_in(board);
        }else if (c == 'C')
        {
            move_right(board);
            put_random_2_in(board);
        }
        print_board(board);
        printf("You pressed '%c'\r\n", c);
    }

    system("/bin/stty cooked");  // 後始末

    return 0;
}

int random_in_range(int rand_max){
    return rand()%rand_max;
}

void print_board(int board[SIZE][SIZE]) {
    for (int j=0; j<SIZE; j++){
        for (int i=0; i<SIZE; i++){
            if (board[j][i]!=0){
                int color = (((int)log2(board[j][i]))%6)+1;
                printf("\x1b[3%dm", color);//色をつける
                printf("%5d", board[j][i]);
                printf("\x1b[39m");//色をデフォルトに
                printf("|");
            }
            else
            {
                printf("     ");
                printf("|");
            }
        }
        printf("\r\n-----");
        printf("|-----");
        printf("|-----");
        printf("|-----|");
        printf("\r\n");
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

void start_game(int board[SIZE][SIZE]){
    put_random_2_in(board);
    put_random_2_in(board);
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
