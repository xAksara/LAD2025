#include <stdio.h>
#include <stdlib.h>

void print_help(char* prog) {
    printf("Usage:\n%s N\n\tprint sequence [0, 1, ..., N - 1]\n", prog);
    printf("%s M N\n\tprint sequence [M, M + 1, ..., N - 1]\n", prog);
    printf("%s M N S\n\tprint sequence [M, M + S, M + 2S, ..., N - 1]\n", prog);
    printf("%s\n\tprint this help\n", prog);
}

void print_sequence(int M, int N, int S) {
    for (int x = M, i = 0; x < N; x += S, ++i)
        printf("%d\n", x);
}


int main(int argc, char *argv[]) {
    switch (argc) {
        case 1:
            print_help(argv[0]);
            break;
        case 2: 
            print_sequence(0, atoi(argv[1]), 1); 
            break;
        case 3: 
            print_sequence(atoi(argv[1]), atoi(argv[2]), 1); 
            break;
        case 4: 
            print_sequence(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])); 
            break;
        default:
            print_help(argv[0]);
            return 1;
    }
    return 0;

}
