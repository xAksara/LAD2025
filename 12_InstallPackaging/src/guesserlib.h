
#pragma once
#include "config.h"
#include <stdio.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

/** Macro for gettext to improve readability */
#define _(STRING) gettext(STRING)


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
char *int_to_roman(int num);

/**
 * @brief Maps roman number to int. In this program this is useless, but required ind task
 * 
 * @param roman target roman number
 * @return int result int number
 */
int roman_to_int(const char *roman);

/**
 * @brief prints help into provided FILE * stream
 * 
 * @param prog program name
 * @param f stream for printing
 */
void print_help(char *prog, FILE *f);

/**
 * @brief Get the str of int number in arabic or roman form
 * 
 * @param n target number
 * @param use_roman flags is function must return roman
 * @return char* result string
 */
char *get_str_num(int n, int use_roman, char *buf);