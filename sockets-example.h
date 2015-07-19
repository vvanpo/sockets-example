#ifndef SOCKETS_EXAMPLE_H
#define SOCKETS_EXAMPLE_H

#include <errno.h>
#include <stdio.h>
#include <string.h>

// error macro definitions
#define error_fmt(f, t, m) fprintf(stderr, "%s: %s() %s: %s\n", program_name, \
        f, t, m)
#define error_m(f, m) error_fmt(#f, "error", m)
#define error_no(f, n) error_m(f, strerror(n))
#define error(f) error_no(f, errno)
#define fatal(m) do { error_fmt(__func__, "fatal", m); exit(EXIT_FAILURE); \
    } while (0)

// extern function declarations
extern int get_address(struct sockaddr **, socklen_t *, char *, char *);
extern int recv_start(int);
extern void *send_start(void *);

// extern globals declarations
extern char const *program_name;

#endif