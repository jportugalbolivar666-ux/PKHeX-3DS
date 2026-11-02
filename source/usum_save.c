#include "usum_save.h"
#include <stdio.h>
#include <string.h>
typedef struct { uint32_t offset, length; } BlockDef;
/* Offsets and lengths cross-checked against PKHeX SaveBlockAccessor7USUM.cs. */
static const BlockDef blocks[USUM_BLOCK_COUNT] = {
{0x00000,0x00E28},{0x01000,0x0007C},{0x01200,0x00014},{0x01400,0x000C0},{0x01600,0x0061C},{0x01E00,0x00E00},{0x02C00,0x00F78},{0x03C00,0x00228},{0x04000,0x0030C},{0x04400,0x001FC},{0x04600,0x0004C},{0x04800,0x00004},{0x04A00,0x00058},{0x04C00,0x005E6},{0x05200,0x36600},{0x3B800,0x0572C},{0x41000,0x00008},{0x41200,0x01218},{0x42600,0x01A08},{0x44200,0x06408},{0x4A800,0x06408},{0x50E00,0x03998},{0x54800,0x00100},{0x54A00,0x00100},{0x54C00,0x10528},{0x65200,0x00204},{0x65600,0x00B60},{0x66200,0x03F50},{0x6A200,0x00358},{0x6A600,0x00728},{0x6AE00,0x00200},{0x6B000,0x00718},{0x6B800,0x001FC},{0x6BA00,0x00200},{0x6BC00,0x00120},{0x6BE00,0x001C8},{0x6C000,0x00200},{0x6C200,0x0039C},{0x6C600,0x00400}
};
static uint16_t rd16le(const uint8_t *p){return (uint16_t)(p[0]|((uint16_t)p[1]<<8));}
static uint32_t rd32le(const uint8_t *p){return (uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);}
UsumSaveInfo usum_validate_save(const uint8_t *data,size_t size){
 UsumSaveInfo r; memset(&r,0,sizeof(r)); r.size=(uint32_t)size; r.total_blocks=USUM_BLOCK_COUNT;
 if(!data){snprintf(r.message,sizeof(r.message),"No se recibieron datos.");return r;}
 if(size!=USUM_SAVE_SIZE){snprintf(r.message,sizeof(r.message),"Tamano incorrecto: %lu bytes (se esperan %u).",(unsigned long)size,(unsigned)USUM_SAVE_SIZE);return r;}
 /* Same BEEF marker check used by PKHeX SaveUtil for Gen 7 saves. */
 if(rd32le(data+size-0x1F0)!=0x42454546){snprintf(r.message,sizeof(r.message),"No aparece el marcador BEEF de la partida.");return r;}
 const uint8_t *table=data+USUM_META_OFFSET+0x14;
 for(uint32_t i=0;i<USUM_BLOCK_COUNT;i++){
  const uint8_t *entry=table+i*8; uint32_t len=rd32le(entry); uint16_t id=rd16le(entry+4);
  if(id==i && len==blocks[i].length && blocks[i].offset<=size && blocks[i].length<=size-blocks[i].offset) r.valid_blocks++;
 }
 if(r.valid_blocks!=USUM_BLOCK_COUNT){snprintf(r.message,sizeof(r.message),"Marcador correcto, pero tabla de bloques no coincide (%lu/%u).",(unsigned long)r.valid_blocks,(unsigned)USUM_BLOCK_COUNT);return r;}
 r.valid=true; snprintf(r.message,sizeof(r.message),"Partida USUM reconocida; estructura de bloques valida."); return r;
}
