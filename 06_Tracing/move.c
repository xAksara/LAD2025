/*
Еще можно проверять fprintf на успешность, но всему есть предел...
*/


#include <stdio.h>
#include <stdlib.h>

enum Errors {
    ERRARGS = 1,
    ERROPEN,
    ERRCLOSE,
    ERRREAD,
    ERRWRITE,
    ERRFSEEK,
    ERRFTELL,
    ERRALLOC,
    ERRREMOVE
};

int main(int argc, char *argv[]) {
    int status;
    FILE *outfile = NULL, *infile = NULL;
    char* buff = NULL;
    if (argc != 3) {
        fprintf(stderr, "Usage: move infile outfile\n");
        status = ERRARGS;
        goto err;
    }

    infile = fopen(argv[1], "rb");
    if (!infile) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        status = ERROPEN;
        goto err;
    }

    if (fseek(infile, 0, SEEK_END)) {
        fprintf(stderr, "Error with fseek\n");
        status =  ERRFSEEK;
        goto err;
    }

    long file_size = ftell(infile);
    if (file_size < 0) {
        fprintf(stderr, "Error with ftell\n");
        status = ERRFTELL;
        goto err;
    }

    if (fseek(infile, 0, SEEK_SET)) {
        fprintf(stderr, "Error with fseek\n");
        status =  ERRFSEEK;
        goto err;
    }

    buff = malloc(file_size);
    if (!buff) {
        fprintf(stderr, "Can't malloc %ld bytes\n", file_size);
        status = ERRALLOC;
        goto err;
    }

    size_t n = fread(buff, sizeof(char), file_size, infile);
    if (n != file_size || ferror(infile)) {
        fprintf(stderr, "Error when read from %s\n", argv[1]);
        status = ERRREAD;
        goto err;
    }


    outfile = fopen(argv[2], "wb");
    if (!outfile) {
        fprintf(stderr, "Can't open %s\n", argv[2]);
        status = ERROPEN;
        goto err;
    }

    n = fwrite(buff, sizeof(char), file_size, outfile);
    free(buff);
    buff = NULL;
    if (ferror(outfile) || n != file_size) {
        fprintf(stderr, "Error when write in %s\n", argv[2]);
        status = ERRWRITE;
        goto err;   
    }
    if(fclose(outfile)) {
        fprintf(stderr, "Can't close %s\n", argv[2]);
        status = ERRCLOSE;
        goto err;
    }
    if(fclose(infile)) {
        fprintf(stderr, "Can't close %s\n", argv[1]);
        return ERRCLOSE;
    }

    if (remove(argv[1])) {
        fprintf(stderr, "Error when remove %s\n", argv[1]);
        return ERRREMOVE;
    }

    return 0;

err:
    free(buff);
    if(outfile && fclose(outfile)) {
        if(infile && fclose(infile)) {
            fprintf(stderr, "Can't close %s and %s\n", argv[1], argv[2]);
            return ERRCLOSE;
        }
        fprintf(stderr, "Can't close %s\n", argv[2]);
        return ERRCLOSE;
    }
    if(infile && fclose(infile)) {
        fprintf(stderr, "Can't close %s\n", argv[1]);
        return ERRCLOSE;
    }
    return status;
}