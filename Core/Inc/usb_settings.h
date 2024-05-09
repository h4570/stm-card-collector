#ifndef __USB_SETTINGS_H__
#define __USB_SETTINGS_H__

// FatFS requires minimum 128 sectors for volume and 63 sectors for FAT management
// Sektor to STORAGE_KB_SIZE * 1024 / STORAGE_BLOCK_BYTES (ram_glue.c)
// Więc 96KB to minimum

#define STORAGE_KB_SIZE 96
#define STORAGE_BLOCK_BYTES 512
#define STORAGE_BLOCKS_PER_1KB 2
#define STORAGE_BLOCKS_COUNT STORAGE_KB_SIZE *STORAGE_BLOCKS_PER_1KB

extern uint8_t ram_disk[STORAGE_BLOCK_BYTES * STORAGE_BLOCKS_COUNT];

#endif // __USB_SETTINGS_H__
