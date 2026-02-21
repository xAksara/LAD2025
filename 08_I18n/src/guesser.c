#include "config.h"
#include <stdio.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define LOCALE_PATH "po"

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain("guesser", LOCALE_PATH);
    textdomain("guesser");

    printf(_("guess the number from 1 to 100 and press any key\n"));
    getchar();
    
    int left = 1, right = 100;
    while(left < right) {
        int n = (left + right) / 2;
        printf(_("is the number greater than %d? (y/n)\n"), n);
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
    printf(_("guessed number is %d\n"), left);
    return 0;
}