/* This header replicates the standard Linux termios structure 
 * for testing purposes with our Python/C suite.
 */

#ifndef _TTY_TEST_H
#define _TTY_TEST_H

#include <linux/ioctl.h>

// Magic number for TTY IOCTLs
#define TTY_MAGIC 'T'

// Control characters array size (Standard for most Linux archs)
#define NCCS 32

/**
 * struct termios - Standard TTY configuration structure
 * This matches the "IIIIB32BII" format from our JSON
 */
struct termios {
    unsigned int c_iflag;      /* input mode flags */
    unsigned int c_oflag;      /* output mode flags */
    unsigned int c_cflag;      /* control mode flags */
    unsigned int c_lflag;      /* local mode flags */
    unsigned char c_line;      /* line discipline */
    unsigned char c_cc[NCCS];  /* control characters array (32B) */
    unsigned int c_ispeed;     /* input speed */
    unsigned int c_ospeed;     /* output speed */
};

/**
 * struct winsize - Terminal window size structure
 * Format: "HHHH" (4 unsigned shorts)
 */
struct winsize {
    unsigned short ws_row;    /* rows, in characters */
    unsigned short ws_col;    /* columns, in characters */
    unsigned short ws_xpixel; /* horizontal size, pixels */
    unsigned short ws_ypixel; /* vertical size, pixels */
};

/* IOCTL Definitions */

// TIOCGWINSZ: Get window size
#define TIOCGWINSZ _IOR(TTY_MAGIC, 19, struct winsize)

// TCGETS: Read the current serial port settings
#define TCGETS _IOR(TTY_MAGIC, 1, struct termios)

// TIOCMGET: Get the status of modem bits (DTR, RTS, etc.)
#define TIOCMGET _IOR(TTY_MAGIC, 21, unsigned int)

// TCSBRK: Send a break signal (No data passed)
#define TCSBRK _IO(TTY_MAGIC, 9)

#endif // _TTY_TEST_H