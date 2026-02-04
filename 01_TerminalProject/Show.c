#include <curses.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#define DX 7
#define DY 3



// fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffsssssssssssssssssssssssssssssfafsafasfasfasfasfasfafasfasfasfasfasfasfasfasfasfasfassssssafasfasfasfasfasfasfasfasfasfasfasfa


int main(int argc, char *argv[]) {
    FILE *fp;
    WINDOW *frame, *win;
    char buffer[2096];

    setlocale(LC_ALL, "");

    if (argc != 2) {
        fprintf(stderr, "wrong arg number\n");
        return 1;
    }

    fp = fopen(argv[1], "r");

    if (!fp) {
        fprintf(stderr, "can't read file\n");
        return 1;
    }


    initscr();
    noecho();
    cbreak();
    refresh();

    int winCols = COLS - 2 * DX - 2;
    int winLines = LINES - 2 * DY - 2;


    if (winCols > 2096)
        return 1;

    frame = newwin(LINES - 2 * DY, COLS - 2 * DX, DY, DX);
    box(frame, 0, 0);
    mvwaddstr(frame, 0, (COLS - 2*DX - strlen(argv[1])) / 2, argv[1]);
    wrefresh(frame);

    win = newwin(winLines, winCols, DY + 1, DX + 1);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    for (int line = 0; line < winLines && fgets(buffer, winCols, fp); ++line) {
        wprintw(win, "%s", buffer);
    }


    
    wrefresh(win);
    refresh();
//    getch();
    
    for (int c = wgetch(win); c != 27; c = wgetch(win)) {
        if (c == ' ' && fgets(buffer, winCols, fp)) {
            wprintw(win, "%s", buffer);
        }
    }

    delwin(win);
    delwin(frame);
    endwin();
    fclose(fp);
    return 0;
}
