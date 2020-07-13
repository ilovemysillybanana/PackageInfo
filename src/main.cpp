#include <iostream>
#include <stdio.h>
#include "json.hpp"
#include "main.h"

extern "C" {
    #include "deb.h"
    #include <sys/utsname.h>
}


using namespace std; 

int main() {
    struct utsname buffer;
    uname(&buffer);

    struct PackageInfo pkg = packages();

    using json = nlohmann::json;

    std::string sysname = buffer.sysname;
    std::string machine = buffer.machine;
    std::string release = buffer.release;
    std::string nodename = buffer.nodename;
    std::string version = buffer.version;

    json j;
    j["name"] = sysname;
    j["machine"] = machine;
    j["release"] = release;
    j["nodename"] = nodename;
    j["version"] = version;
    j["packages"] = json::array();

    int i;
    for(i = 0; i < pkg.size; i++){
        std::string name = pkg.list[i][0];
        std::string vers = pkg.list[i][1];

        json temp_json = { 
            {name, vers} 
        };

        j["packages"] += temp_json;
    }

    std::cout << j.dump(4) << std::endl;

    // clean up
    for (int i = 0; i < pkg.size; i++){
        for (int j = 0; j < 3; j++){
            free(pkg.list[i][j]);
        }
        free(pkg.list[i]);
    }
    free(pkg.list);
    return 0;
}

struct PackageInfo packages(){
    struct PackageInfo packages = deb_list();
    return packages;
}