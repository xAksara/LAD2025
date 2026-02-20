#include <config.h>
#include <ctype.h>
#include <rhash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#endif

char *get_line(char *prompt) {
    char *line = NULL;
#ifdef USE_READLINE
    line = readline(prompt);
#else
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    size_t n, size = 0;
    n = getline(&line, &size, stdin);
    if (n == -1) {
        free(line);
        line = NULL;
        return line;
    }
    if (n > 0 && line[n - 1] == '\n')
        line[n - 1] = '\0';
#endif
    return line;
}

void set_alg(char *str, int *rhpr, int *rhash_id) {
    *rhpr = isupper(str[0]) ? RHPR_HEX : RHPR_BASE64;
    if (!strcasecmp(str, "MD5")) {
        *rhash_id = RHASH_MD5;
    } else if (!strcasecmp(str, "TTH")) {
        *rhash_id = RHASH_TTH;
    } else if (!strcasecmp(str, "SHA1")) {
        *rhash_id = RHASH_SHA1;
    } else {
        *rhash_id = -1;
    }
}


int main(int argc, char *argv[]) {
    rhash_library_init();
    char *line;
    while((line = get_line(NULL))) {
        char *algstr = strtok(line, " ");
        char *source = strtok(NULL, " ");
        if (!algstr || !source) {
            fprintf(stderr, "bad input\n");
            free(line);
            continue;
        }

        int rhash_id, rhpr;
        set_alg(algstr, &rhpr, &rhash_id);
        if(rhash_id == -1) {
            fprintf(stderr, "bad algorithm\n");
            free(line);
            continue;
        }
        unsigned char digest[64];
        int res;
        if (source[0] == '"') {
            size_t len = strlen(source);
            if (len > 1 && source[len-1] == '"') { 
                source[len-1] = '\0';
                res = rhash_msg(rhash_id, source + 1, strlen(source) - 1, digest);
            } else { 
                fprintf(stderr, "bad second param\n");
                free(line);
                continue;
            } 
        } else {
            res = rhash_file(rhash_id, source, digest);
        }

        if (res < 0) {
            fprintf(stderr, "bad hash\n");
            free(line);
            continue;
        }

        char output[256];
        rhash_print_bytes(output, digest, rhash_get_digest_size(rhash_id), rhpr);
        printf("%s\n", output);
        free(line);
    }
    return 0;
}
