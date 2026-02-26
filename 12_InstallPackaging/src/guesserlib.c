#include <guesserlib.h>

char *int_to_roman(int num) {
    if (num < 1 || num > 100) {
        return NULL;
    }
    return roman_numerals[num - 1];
}

int roman_to_int(const char *roman) {
    if (!roman) return -1;
    
    char upper_roman[10];
    strncpy(upper_roman, roman, sizeof(upper_roman) - 1);
    upper_roman[sizeof(upper_roman) - 1] = '\0';
    
    for (char *p = upper_roman; *p; p++) {
        if (*p >= 'a' && *p <= 'z') {
            *p = *p - 'a' + 'A';
        }
    }
    
    for (int i = 0; i < 100; i++) {
        if (strcmp(upper_roman, roman_numerals[i]) == 0) {
            return i + 1;
        }
    }
    
    return -1;
}

char *get_str_num(int n, int use_roman, char *buf) {
    if (n > 100 || n < 1) return "";
    if (use_roman)
        sprintf(buf, "%s", int_to_roman(n));
    else {
        sprintf(buf, "%d", n);
    }
    return buf;
}

void print_help(char *prog, FILE *f) {
    fprintf(f, "Usage: %s [parameter]\n", prog);
    fprintf(f, "Optional parameters:\n");
    fprintf(f, "\t-r\tuse roman numerals\n");
    fprintf(f, "\t--help\tprint this help\n");
}