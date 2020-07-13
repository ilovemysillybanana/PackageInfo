#define LIBDPKG_VOLATILE_API 1
#include "deb.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <dpkg/dpkg.h>
#include <dpkg/dpkg-db.h>
#include <dpkg/pkg-array.h>


// void deb_list(void){
struct PackageInfo deb_list(void){
    struct PackageInfo Pack;

    int i;
    struct pkgset *set;
    struct pkginfo *info;
    struct pkg_array array; 


    dpkg_program_init("a.out");
    modstatdb_open(msdbrw_available_readonly);

    pkg_array_init_from_hash(&array);

    int array_size = 0;
    for (i = 0; i < array.n_pkgs; i++) {
        if (array.pkgs[i]->status == PKG_STAT_NOTINSTALLED){
            continue;
        } else {
           array_size+=1;
        }
    }

    int fields = 3;
    int elements = array_size;
    int strlength = 50;

    char ***packages = (char ***) malloc(elements * sizeof(char **));
    for (int i = 0; i < elements; i++){
        packages[i] = (char **) malloc(fields * sizeof(char *));
        for (int j = 0; j < fields; j++){
            packages[i][j] = (char *) malloc( (strlength) * sizeof(char));
        }
    }


    for (int i = 0; i < elements; i++){
        packages[i] = (char **) malloc(fields * sizeof(char *));
        for (int j = 0; j < fields; j++){
            packages[i][j] = (char *) malloc( (strlength) * sizeof(char));
        }
    }

    //track where we are 
    int index = 0;
    for (i = 0; i < array.n_pkgs; i++) {
        if (array.pkgs[i]->status == PKG_STAT_NOTINSTALLED){
            continue;
        } else {
            char *name = strdup(array.pkgs[i]->set->name);
            char *vers = strdup(array.pkgs[i]->configversion.version);
            packages[index][0] = name;
            packages[index][1] = vers;
            index += 1;
        }
    }

    pkg_array_destroy(&array);
    dpkg_program_done();

    Pack.size = array_size;
    Pack.list = packages;

    return Pack;
}