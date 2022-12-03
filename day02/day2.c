#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 3

int calc_score_a(char a, char b) {
    int score = 0;
    switch (b)
    {
    case 'X': // rock
        score += 1;
        if (a == 'A') { score += 3; }
        if (a == 'C') { score += 6; } 
        return score;
    case 'Y': // paper
        score += 2;
        if (a == 'A') { score += 6; }
        if (a == 'B') { score += 3; } 
        return score;
    case 'Z': // scissors
        score += 3;
        if (a == 'C') { score += 3; }
        if (a == 'B') { score += 6; } 
        return score;
    default:
        break;
    }
}

int calc_score_b(char a, char b) {
    int score = 0;
    switch (b)
    {
    case 'X': // LOSE
        if (a == 'A') { score += 3; }
        if (a == 'B') { score += 1; }
        if (a == 'C') { score += 2; } 
        return score;
    case 'Y': // DRAW
        score += 3;
        if (a == 'A') { score += 1; }
        if (a == 'B') { score += 2; }
        if (a == 'C') { score += 3; } 
        return score;
    case 'Z': // WIN
        score += 6;
        if (a == 'A') { score += 2; }
        if (a == 'B') { score += 3; }
        if (a == 'C') { score += 1; }  
        return score;
    default:
        break;
    }
}

int main() {
    FILE *fp;

    fp = fopen("input", "r");
    char * buff;
    size_t len = 0;
    int nonempty;

    int score_a = 0;
    int score_b = 0;
    while ((nonempty = getline(&buff, &len, fp)) != -1) {
        score_a += calc_score_a(buff[0], buff[2]);
        score_b += calc_score_b(buff[0], buff[2]);
    }

    printf("Score for A is %d.\n", score_a);
    printf("Score for B is %d.\n", score_b);

    fclose(fp);
    return 0;
}