#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }
    else {
        printf("No arguments.");
    }
    return 0;
}