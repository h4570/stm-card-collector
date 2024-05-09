#include "FatFs/diskio_ram_glue.h"
#include "usb_settings.h"
#include <string.h>

DSTATUS RAM_disk_status()
{
	return RES_OK; // Zakładamy, że dysk jest zawsze gotowy
}

DSTATUS RAM_disk_initialize()
{
	return RES_OK; // Dysk jest zainicjowany przez główny kod
}

DRESULT RAM_disk_read(
	BYTE *buff,	  /* Data buffer to store read data */
	LBA_t sector, /* Start sector in LBA */
	UINT count	  /* Number of sectors to read */
)
{
	memcpy(buff, &ram_disk[sector * STORAGE_BLOCK_BYTES], count * STORAGE_BLOCK_BYTES);
	return RES_OK;
}

DRESULT RAM_disk_write(
	const BYTE *buff, /* Data to be written */
	LBA_t sector,	  /* Start sector in LBA */
	UINT count		  /* Number of sectors to write */
)
{
	memcpy(&ram_disk[sector * STORAGE_BLOCK_BYTES], buff, count * STORAGE_BLOCK_BYTES);
	return RES_OK;
}

DRESULT RAM_disk_ioctl(
	BYTE cmd,  /* Control code */
	void *buff /* Buffer to send/receive control data */
)
{
	switch (cmd)
	{
	case CTRL_SYNC:
		return RES_OK;
	case GET_SECTOR_SIZE:
		*(WORD *)buff = STORAGE_BLOCK_BYTES;
		return RES_OK;
	case GET_BLOCK_SIZE:
		*(DWORD *)buff = 1; // Blok to jeden sektor
		return RES_OK;
	case GET_SECTOR_COUNT:
		*(DWORD *)buff = STORAGE_KB_SIZE * 1024 / STORAGE_BLOCK_BYTES;
		return RES_OK;
	default:
		return RES_PARERR;
	}
}
