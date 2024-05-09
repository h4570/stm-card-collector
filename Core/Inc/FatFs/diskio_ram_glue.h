
#ifndef _DISKIO_RAM_GLUE
#define _DISKIO_RAM_GLUE

#include "FatFs/ff.h"
#include "FatFs/diskio.h"

DSTATUS RAM_disk_status();

DSTATUS RAM_disk_initialize();

DRESULT RAM_disk_read(
    BYTE *buff,   /* Data buffer to store read data */
    LBA_t sector, /* Start sector in LBA */
    UINT count    /* Number of sectors to read */
);

DRESULT RAM_disk_write(
    const BYTE *buff, /* Data to be written */
    LBA_t sector,     /* Start sector in LBA */
    UINT count        /* Number of sectors to write */
);

DRESULT RAM_disk_ioctl(
    BYTE cmd,  /* Control code */
    void *buff /* Buffer to send/receive control data */
);

#endif