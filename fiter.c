#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void* bh_opendir(const char* path) {
    return (void*)opendir(path);
}

void bh_closedir(void* d) {
    closedir((DIR*)d);
}

char* bh_readdir(void* d) {
    struct dirent *e;
    while ((e = readdir((DIR*)d)) != NULL) {
        if (e->d_name[0] == '.' &&
           (e->d_name[1] == '\0' ||
           (e->d_name[1] == '.' && e->d_name[2] == '\0')))
            continue;
        return strdup(e->d_name);
    }
    return NULL;
}

int bh_is_dir(const char* path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}

int bh_is_reg(const char* path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

char* bh_path_join(const char* dir, const char* name) {
    size_t dlen = strlen(dir);
    size_t nlen = strlen(name);
    char *p = malloc(dlen + nlen + 2);
    if (!p) return NULL;
    memcpy(p, dir, dlen);
    p[dlen] = '/';
    memcpy(p + dlen + 1, name, nlen + 1);
    return p;
}

char* bh_strdup(const char* s) {
    return strdup(s);
}
