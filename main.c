#include <stdio.h>
#include <stdlib.h>

void print_board() {
    printf("aaaaa\r\n");
    printf("aaaaa\r\n");
    printf("aaaaa\r\n");
    printf("aaaaa\r\n");
    printf("aaaaa\r\n");
}

int main (int argc, char *argv[]) {
    printf("Press any key to conitnue\n");
    int c;

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる

    while((c = getchar()) != '.') {
        system("clear");
        printf("Press '.' to close\r\n");
        print_board();
        printf("You pressed '%c'\r\n", c);
    }

    system("/bin/stty cooked");  // 後始末

    return 0;
}