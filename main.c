#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 4
int random_in_range(int);
void print_board(int [SIZE][SIZE]);
int check_if_full(int [SIZE][SIZE]);
void put_random_2_in(int [SIZE][SIZE]);
void start_game(int [SIZE][SIZE]);
void move_up(int [SIZE][SIZE], int *);
void move_down(int [SIZE][SIZE], int *);
void move_left(int [SIZE][SIZE], int *);
void move_right(int [SIZE][SIZE], int *);


int main (int argc, char *argv[]) {
    int board[SIZE][SIZE] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    int score = 0;
    int c;
    
    system("clear");
    printf("Press '.' to close\r\n");
    start_game(board);
    print_board(board);

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる

    while((c = getchar()) != '.') {
        system("clear");
        printf("Press '.' to close\r\n");
        if (check_if_full(board)){
            system("clear");
            print_board(board);
            printf("\r\n\r\nGAME OVER !\r\n\r\n");
            printf("Your Score: %d\r\n", score);
            break;
        }else if (c == 'A')
        {
            move_up(board, &score);
            put_random_2_in(board);
        }else if (c == 'D')
        {
            move_left(board, &score);
            put_random_2_in(board);
        }else if (c == 'B')
        {
            move_down(board, &score);
            put_random_2_in(board);
        }else if (c == 'C')
        {
            move_right(board, &score);
            put_random_2_in(board);
        }
        print_board(board);
        printf("Your Score: %d\r\n", score);
    }
    system("/bin/stty cooked");  // 後始末

    return 0;
}

int random_in_range(int rand_max){
    int r = rand();
    return r%rand_max;
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

int check_if_full(int board[SIZE][SIZE]){
    for (int i=0; i<SIZE; i++){
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0){
                return 0;
            }
        }
    }
    return 1;
}

void put_random_2_in(int board[SIZE][SIZE]){
    int flag = 0;

    while(flag == 0){
        if(check_if_full(board)){
            break;
        }else
        {
            int m = random_in_range(SIZE);
            int n = random_in_range(SIZE);
            if (board[m][n] == 0){
                board[m][n] = 2;
                flag = 1;
            }
        }
    }
}

void start_game(int board[SIZE][SIZE]){
    put_random_2_in(board);
    put_random_2_in(board);
}

void move_up(int board[SIZE][SIZE], int *s){
    int flag[SIZE] = {0, 0, 0, 0}; //各列の足し算は一回まで
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
                            *s += board[k][j];
                            board[k+1][j] = 0;
                            flag[j] = 1;
                        }
                    }
                }
            }
        }
    }
}

void move_down(int board[SIZE][SIZE], int *s){
    int flag[SIZE] = {0, 0, 0, 0}; //各列の足し算は一回まで
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
                            *s += board[k][j];
                            board[k-1][j]=0;
                            flag[j] = 1;
                        }
                    }
                }
            }
        }
    }
}

void move_left(int board[SIZE][SIZE], int *s){
    int flag[SIZE] = {0, 0, 0, 0}; //各行の足し算は一回まで
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
                            *s += board[i][k];
                            board[i][k+1]=0;
                            flag[i]=1;
                        }
                    }
                }
            }
        }
    }
}

void move_right(int board[SIZE][SIZE], int *s){
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
                            *s += board[i][k];
                            board[i][k-1] = 0;
                            flag[i]=1;
                        }
                    }
                    
                }
            }
        }
    }
}
