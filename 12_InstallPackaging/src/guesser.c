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
 * @brief Program for lab12. Guess the hidden number. Supports roman numbers.
 * @version 0.1
 * @date 2026-02-23
 */

#include "config.h"
#include <stdio.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <guesserlib.h>


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