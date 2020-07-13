#ifndef DEB_H
#define DEB_H

struct PackageInfo {
    int size;
    char *** list;
};

struct PackageInfo deb_list(void);

#endif