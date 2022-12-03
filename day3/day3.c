#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int item_prio(char c) {
    if (c > 90) {
        return 1 + (c - 'a');
    } else {
        return 27 + (c - 'A');
    }
}

int prio_a() {
    FILE *fp;

    fp = fopen("input", "r");
    char * buff;
    size_t len = 0;
    int nonempty;

    int priority = 0;
    while ((nonempty = getline(&buff, &len, fp)) != -1) {
        int found = 0;
        for (size_t i = 0; i < ((nonempty-1)/2); i++) {
            for (size_t x = ((nonempty-1)/2); x < nonempty; x++) {
                if (buff[i] == buff[x]) {
                    priority += item_prio(buff[i]);
                    found = 1;
                    break;
                }
            }
            if (found) { break; }
        }
    }

    return priority;
}

int prio_b() {
    FILE *fp;
    fp = fopen("input", "r");
    char * buff_1;
    size_t len = 0;
    int length_1;

    int prio = 0;
    while ((length_1 = getline(&buff_1, &len, fp)) != -1) {
        char * buff_2;
        char * buff_3;
        size_t len_2 = 0;
        size_t len_3 = 0;
        int length_2 = getline(&buff_2, &len_2, fp);
        int length_3 = getline(&buff_3, &len_3, fp);
        int found = 0;
        for (size_t x = 0; x < length_1; x++) {
            for (size_t y = 0; y < length_2; y++) {
                if (buff_1[x] == buff_2[y]) {
                    for (size_t z = 0; z < length_3; z++) {
                        if (buff_1[x] == buff_3[z]) {
                            prio += item_prio(buff_1[x]);
                            found = 1;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    }
                }
            }
            if (found) {
                break;
            }
        }
    }
    return prio;
}

int main() {
    printf("A: %d\n", prio_a());
    printf("B: %d\n", prio_b());

    return 0;
}