/* This header is for testing purposes with our Python/C suite.
 */

#ifndef _FORMAT_TEST_H
#define _FORMAT_TEST_H

#include <linux/ioctl.h>

// Magic number for FORMAT IOCTLs
#define CAMERA_MAGIC 'C'

// Max name lenght costant
#define NAME_MAX_LEN 32

/**
 * struct format_data - Data structure for camera format
 * Format mapping: "32BII"
 * - 32B: name array (32 unsigned chars)
 * - I:   width (unsigned int)
 * - I:   height (unsigned int)
 */
struct format_data {
    unsigned char name[NAME_MAX_LEN];
    unsigned int width;
    unsigned int height;
};

/* IOCTL Definitions */

// IOCTL_SET_FORMAT: Write the format to the device
#define IOCTL_SET_FORMAT _IOW(CAMERA_MAGIC, 1, struct format_data)

// IOCTL_GET_FORMAT: Read the format from the device
#define IOCTL_GET_FORMAT _IOR(CAMERA_MAGIC, 2, struct format_data)

#endif // _FORMAT_TEST_H