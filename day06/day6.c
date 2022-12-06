#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int char_in_string(char * buff, char c) {
    for (size_t i = 0; buff[i] != '\0'; i++) {
        if (buff[i] == c) { return 1; }
    }
    return 0;
}

// Check if every char is different. If not, return the index of the first double char
int diff_chars(char * buff) {
    for (size_t i = 0; buff[i] != '\0'; i++) {
        char * buff_cut = buff + i + 1;
        if (char_in_string(buff_cut, buff[i])) {
            return i;
        }
    }
    return -1;
}

int marker(char * buff, int buff_length, int mark_length) {
    char *buff_mark = malloc(mark_length + 1);
    buff_mark[mark_length] = '\0';
    int doubles = 0;
    for (size_t i = 0; i < buff_length; i++) {
        memcpy(buff_mark,buff+i,mark_length);
        int t = diff_chars(buff_mark);
        if (t == -1) {
            return i+mark_length;
        }
        i += t;
    }

    return -1;
}

int main() {
    FILE *fp;
    fp = fopen("input", "r");
    char * buff;
    size_t len = 0;
    int length = getline(&buff, &len, fp);

    if (length != -1) {
        int marker_pos = marker(buff, length,4);
        int marker_pos_b = marker(buff, length,14);
        printf("First marker  4 pos at %d\n", marker_pos);
        printf("First marker 14 pos at %d\n", marker_pos_b);
    }
    
    return 0;
}