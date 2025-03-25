#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char Vt[100] , Vn[100];
char Grammer[100][50];
int line = 0;

void initVn_Vt() {
    int j = 0;
    for(int i = 0 ; Grammer[0][i] != '\0' ; i++) {
        if(Grammer[0][i] != ' ') {
            Vt[j] = Grammer[0][i];
            Vt[j + 1] = '\0';
            j++;
        }
    }
    j = 0;
    for(int i = 0 ; Grammer[1][i] != '\0' ; i++) {
        if(Grammer[1][i] != ' ') {
            Vn[j] = Grammer[1][i];
            Vn[j + 1] = '\0';
            j++;
        }
    }
}

bool isVt(char ch) {
    for(int i = 0 ; Vt[i] != '\0' ; i++) {
        if(Vt[i] == ch) {
            return true;
        }
    }
    return false;
}

bool isVn(char ch) {
    for(int i = 0 ; Vn[i] != '\0' ; i++) {
        if(Vn[i] == ch) {
            return true;
        }
    }
    return false;
}

bool equal(char * a , char * b) {
    for(int i = 0 ; i < strlen(a) ; i++) {
        if(a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

char * isType1(char * rule) {
    char left[100];
    char right[100];
    int i = 0;
    int j = 0;
    while(rule[i] != '-') {
        if(rule[i] != ' ') {
            left[j] = rule[i];
            left[j + 1] = '\0';
            j++;
        }
        i++;
    }

    i += 2;
    j = 0;
    while(rule[i] != '\0') {
        if(rule[i] != ' ') {
            right[j] = rule[i];
            right[j + 1] = '\0';
            j++;
        }
        i++;
    }
    
    for(int i = 0 ; i < strlen(left) ; i++) {
        if(isVt(left[i])) {
            continue;
        }
        char pref1[100];
        pref1[0] = '\0';
        char suff1[100];
        suff1[0] = '\0';
        int k = 0;
        for(int j = 0 ; j < i ; j++) {
            pref1[k] = left[j];
            pref1[k + 1] = '\0';
            k++; 
        }
        k = 0;
        for(int j = i + 1 ; j < strlen(left) ; j++) {
            suff1[k] = left[j];
            suff1[k + 1] = '\0';
            k++; 
        }

        char pref2[100];
        pref2[0] = '\0';
        char suff2[100];
        suff2[0] = '\0';
        k = strlen(pref1);
        int j = 0;
        while(k--) {
            pref2[j] = right[j];
            pref2[j + 1] = '\0';
            j++;
        }

        k = strlen(suff1);
        suff2[k] = '\0';
        j = k - 1;
        int r = strlen(right) - 1;
        while(k--) {
            suff2[j] = right[r];
            j--;
            r--; 
        }
        
        char mid[100];
        j = 0;
        for(int l = strlen(pref1) ; l < strlen(right) - strlen(suff2) ; l++) {
            mid[j] = right[l];
            mid[j + 1] = '\0';
            j++;
        }
        if(equal(pref1 , pref2) && equal(suff1 , suff2)) {
            return "YES";
        }
    }
    
    return "NO";
}

char * isType2(char * rule) {
    int i = 0;
    char left[10];
    int j = 0;
    while(rule[i] != '-') {
        if(rule[i] != ' ') {
            left[j] = rule[i];
            left[j + 1] = '\0';
            j++;
        }
        i++;
    }

    if(strlen(left) == 1 && isVn(left[0])) {
       return "YES"; 
    } else {
        return "NO";
    }
}

char * isType3(char * rule) {
    int i = 0;
    char left[10];
    int j = 0;
    while(rule[i] != '-') {
        if(rule[i] != ' ') {
            left[j] = rule[i];
            left[j + 1] = '\0';
            j++;
        }
        i++;
    }
    
    i += 2;
    char right[10];
    j = 0;
    while(rule[i] != '\0') {
        if(rule[i] != ' ') {
            right[j] = rule[i];
            right[j + 1] = '\0';
            j++;
        }
        i++;
    }

    if(strlen(left) == 1 && isVn(left[0]) && ((strlen(right) == 1 && isVt(right[0]) || (strlen(right) == 2 && isVn(right[0]) != isVn(right[1]))))) {
       return "YES"; 
    } else {
        return "NO";
    }
} 

int typeOf(char * rule) {
    if(strlen(isType1(rule)) == 3) {
        return 1;
    }
    if(strlen(isType2(rule)) == 3) {
        return 2;
    }
    if(strlen(isType3(rule)) == 3) {
        return 3;
    }
}
void showRules() {
    printf("-Vt : {%s}\n" , Grammer[0]);
    printf("-Vn : {%s}\n" , Grammer[1]);
    printf("+----------+----------------------------------------+------+------+------+--------------+\n");
    printf("| Rule nbr |                  Rule                  |Type 1|Type 2|Type 3| Grammer Type |\n");
    printf("+----------+----------------------------------------+------+------+------+--------------+\n");
    for(int i = 4 ; i <= line ; i++) {
        printf("|  %6d  |%40s|%6s|%6s|%6s|%14d|\n" , i - 3 , Grammer[i] , isType1(Grammer[i]) , isType2(Grammer[i]) , isType3(Grammer[i]) , typeOf(Grammer[i]));
        printf("+----------+----------------------------------------+------+------+------+--------------+\n");
    }
}

void readFile() {
    FILE * file = fopen("file.txt" , "r");
    int i = 0;
    while(!feof(file)) {
        char ch = fgetc(file);
        if(ch == '\n') {
            line++;
            i = 0;
        } else {
            Grammer[line][i] = ch;
            Grammer[line][i + 1] = '\0';
            i++;
        }
    }
    Grammer[line][i - 1] = '\0';
    fclose(file);
}

int main() {
    readFile();
    initVn_Vt();
    showRules();
    return 0;
}