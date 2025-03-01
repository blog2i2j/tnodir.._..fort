#ifndef FORTIOCTL_H
#define FORTIOCTL_H

#include "common.h"

#define FORT_DEVICE_NAME     "\\\\.\\fortfw"
#define FORT_NT_DEVICE_NAME  L"\\Device\\fortfw"
#define FORT_DOS_DEVICE_NAME L"\\DosDevices\\fortfw"

#define FORT_DEVICE_TYPE 0xD000
#define FORT_IOCTL_BASE  0xD00

#define FORT_CTL_CODE(i, a) CTL_CODE(FORT_DEVICE_TYPE, FORT_IOCTL_BASE + (i), METHOD_BUFFERED, (a))

/* Macro to extract function index out of the device io control code */
#define FORT_CTL_INDEX_FROM_CODE(ctrlCode) ((DWORD) (((ctrlCode) >> 2) & 0xFF))

enum {
    FORT_IOCTL_INDEX_VALIDATE = 0,
    FORT_IOCTL_INDEX_SETSERVICES,
    FORT_IOCTL_INDEX_SETCONF,
    FORT_IOCTL_INDEX_SETFLAGS,
    FORT_IOCTL_INDEX_GETLOG,
    FORT_IOCTL_INDEX_ADDAPP,
    FORT_IOCTL_INDEX_DELAPP,
    FORT_IOCTL_INDEX_SETZONES,
    FORT_IOCTL_INDEX_SETZONEFLAG,
    FORT_IOCTL_INDEX_SETRULES,
    FORT_IOCTL_INDEX_SETRULEFLAG,
    FORT_IOCTL_INDEX_COUNT,
};

#define FORT_IOCTL_VALIDATE    FORT_CTL_CODE(FORT_IOCTL_INDEX_VALIDATE, FILE_WRITE_DATA)
#define FORT_IOCTL_SETSERVICES FORT_CTL_CODE(FORT_IOCTL_INDEX_SETSERVICES, FILE_WRITE_DATA)
#define FORT_IOCTL_SETCONF     FORT_CTL_CODE(FORT_IOCTL_INDEX_SETCONF, FILE_WRITE_DATA)
#define FORT_IOCTL_SETFLAGS    FORT_CTL_CODE(FORT_IOCTL_INDEX_SETFLAGS, FILE_WRITE_DATA)
#define FORT_IOCTL_GETLOG      FORT_CTL_CODE(FORT_IOCTL_INDEX_GETLOG, FILE_READ_DATA)
#define FORT_IOCTL_ADDAPP      FORT_CTL_CODE(FORT_IOCTL_INDEX_ADDAPP, FILE_WRITE_DATA)
#define FORT_IOCTL_DELAPP      FORT_CTL_CODE(FORT_IOCTL_INDEX_DELAPP, FILE_WRITE_DATA)
#define FORT_IOCTL_SETZONES    FORT_CTL_CODE(FORT_IOCTL_INDEX_SETZONES, FILE_WRITE_DATA)
#define FORT_IOCTL_SETZONEFLAG FORT_CTL_CODE(FORT_IOCTL_INDEX_SETZONEFLAG, FILE_WRITE_DATA)
#define FORT_IOCTL_SETRULES    FORT_CTL_CODE(FORT_IOCTL_INDEX_SETRULES, FILE_WRITE_DATA)
#define FORT_IOCTL_SETRULEFLAG FORT_CTL_CODE(FORT_IOCTL_INDEX_SETRULEFLAG, FILE_WRITE_DATA)

#endif // FORTIOCTL_H
