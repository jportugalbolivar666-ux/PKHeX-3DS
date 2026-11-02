#ifndef USUM_SAVE_H
#define USUM_SAVE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define USUM_SAVE_SIZE 0x6CC00
#define USUM_META_OFFSET (USUM_SAVE_SIZE - 0x200)
#define USUM_BLOCK_COUNT 39
typedef struct { bool valid; char message[96]; uint32_t size, valid_blocks, total_blocks; } UsumSaveInfo;
UsumSaveInfo usum_validate_save(const uint8_t *data, size_t size);
#endif
