#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(const char *fname);

int remove(const char *fname) {
    if (strstr(fname, "PROTECT"))
        return 0;
    return ((remove_type)(dlsym(RTLD_NEXT, "remove")))(fname);
}