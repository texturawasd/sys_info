#include <stdio.h>
#include <pwd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include <unistd.h>
#include "../common_utils/string_utils.c"

const char *get_os_pretty_name(void) {
    FILE *fp = popen("grep PRETTY_NAME /etc/os-release", "r");
    char buffer[1024]; while (fgets(buffer, sizeof(buffer), fp)) {
        const char *os_pretty_name = get_quoted_substring(buffer);
        return os_pretty_name;
    }
    return NULL;
}

const char *get_hostname(void) {
    static char hostname[HOST_NAME_MAX + 1];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return hostname;
    }
    return NULL;
}


int main(void) {
    const char *user = getenv("USER");
    const char *host = get_hostname();

    struct utsname u;
    if (uname(&u) == 0) {
        //printf("System:  %s\n", u.sysname);
        //printf("Node:    %s\n", u.nodename);
        const char *kernel = u.release;//printf("Release: %s\n", u.release);
        const char *arch = u.machine;
        //printf("Version: %s\n", u.version);
        //printf("Machine: %s\n", u.machine);


        printf("%s@%s", user ? user : "unknown", host ? host : "unknown");
        puts("\n--------------------");
        printf("OS: %s %s\n", get_os_pretty_name(), arch);
        printf("Kernel: %s\n", kernel);
    }
/*
    puts ("now to test uname");
        struct utsname u;

}*/
}