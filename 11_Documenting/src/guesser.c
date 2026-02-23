/** @mainpage guesser
 * @copydetails library
 */

/** @page library
 * A program for lab11. Guess the hidden number. 
 * @section SYNOPSIS
 * `guesser [-r | --help]`
 *
 * @section DESCRIPTION
 * The program Guess the hidden number using half division method.
 *
 * @b -r
 * @n print numerals in Roman
 *
 * @b --help
 * @n display the program's help and exit
 * @section AUTHORS
 * github.com/xAksara 
 */

/**
 * @file guesser.c
 * @author I (a@a.a)
 * @brief Program for lab11. Guess the hidden number. Supports roman numbers.
 * @version 0.1
 * @date 2026-02-23
 */

#include "config.h"
#include <stdio.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

/** Macro for gettext to improve readability */
#define _(STRING) gettext(STRING)
/** Define locale path directory */
#define LOCALE_PATH "po"

/** Roman numbers table */
static char *roman_numerals[100] = {
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X",
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX",
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX",
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL",
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L",
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX",
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX",
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX",
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC",
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};
/**
 * @brief Maps int number to roman number
 * 
 * @param num target number
 * @return char* result roman number
 */
char *int_to_roman(int num) {
    if (num < 1 || num > 100) {
        return NULL;
    }
    return roman_numerals[num - 1];
}
/**
 * @brief Maps roman number to int. In this program this is useless, but required ind task
 * 
 * @param roman target roman number
 * @return int result int number
 */
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

/**
 * @brief prints help into provided FILE * stream
 * 
 * @param prog program name
 * @param f stream for printing
 */
void print_help(char *prog, FILE *f) {
    fprintf(f, "Usage: %s [parameter]\n", prog);
    fprintf(f, "Optional parameters:\n");
    fprintf(f, "\t-r\tuse roman numerals\n");
    fprintf(f, "\t--help\tprint this help\n");
}
/**
 * @brief Get the str of int number in arabic or roman form
 * 
 * @param n target number
 * @param use_roman flags is function must return roman
 * @return char* result string
 */
char *get_str_num(int n, int use_roman, char *buf) {
    if (n > 100 || n < 1) return "";
    if (use_roman)
        sprintf(buf, "%s", int_to_roman(n));
    else {
        sprintf(buf, "%d", n);
    }
    return buf;
}

int main(int argc, char *argv[]) {
    if (argc > 2) { 
        fprintf(stderr, "Wrong arguments\n");
        print_help(argv[0], stderr);
        return 1;
    }
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        print_help(argv[0], stdout);
        return 0;
    }
    int use_roman = 0;
    if (argc == 2 && !strcmp(argv[1], "-r")) {
        use_roman = 1;
    } else if (argc == 2) {
        fprintf(stderr, "Wrong arguments\n");
        print_help(argv[0], stderr);
        return 1;
    }

    setlocale(LC_ALL, "");
    bindtextdomain("guesser", LOCALE_PATH);
    textdomain("guesser");

    char buf1[10], buf2[10];
    printf(_("guess the number from %s to %s and press any key\n"), get_str_num(1, use_roman, buf1), get_str_num(100, use_roman, buf2));
    getchar();
    
    int left = 1, right = 100;
    while(left < right) {
        int n = (left + right) / 2;
        printf(_("is the number greater than %s? (y/n)\n"), get_str_num(n, use_roman, buf1));
        char c;
        int res = scanf(" %c", &c);
        if (res == EOF)
            return 0;
        if (c == 'y')
            left = n + 1;
        else if (c == 'n')
            right = n;
        else {
            fprintf(stderr, _("wrong answer. Please use 'y' or 'n'\n"));
        }
    }
    printf(_("guessed number is %s\n"), get_str_num(left, use_roman, buf1));
    return 0;
}