#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

//Use function definitions to call functions in the library.
typedef int (*lib_function)(const char  *data);

int main(int argc, char *argv[]) {

    int rc = 0;
    check(argc == 4, "USAGE: ex29 libex29.so function data");

    char *lib_file = argv[1];
    char *func_to_run = argv[2];
    char *data = argv[3];

    void *lib = dlopen(lib_file, RTLD_NOW);
    //Usual check but with dlerror at the end to find what that library related error was
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

    //dlsym to get a function out of the lib by its string name in func_to_run.
    lib_function func = dlsym(lib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s: %s", func_to_run, lib_file, dlerror());

    //Call the func function that was returned and check return value.
    rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

    //Close the library like a file
    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return 1;
}
