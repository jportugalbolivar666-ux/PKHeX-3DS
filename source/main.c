#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include "usum_save.h"
#define SAVE_PATH "sdmc:/3ds/PKHeX3DS/ultrasol.sav"
static void inspect_save(void){
 FILE *f=fopen(SAVE_PATH,"rb"); if(!f){printf("No se pudo abrir:\n%s\n\n",SAVE_PATH);printf("Crea la carpeta y copia una exportacion\n.sav DESENCRIPTADA de Ultrasol.\n");return;}
 if(fseek(f,0,SEEK_END)!=0){printf("Error al leer el archivo.\n");fclose(f);return;}
 long length=ftell(f); rewind(f); if(length<0||(unsigned long)length>2UL*1024UL*1024UL){printf("Tamano no admitido.\n");fclose(f);return;}
 uint8_t *data=(uint8_t*)malloc((size_t)length); if(!data){printf("Memoria insuficiente.\n");fclose(f);return;}
 size_t got=fread(data,1,(size_t)length,f); fclose(f); if(got!=(size_t)length){printf("Lectura incompleta.\n");free(data);return;}
 UsumSaveInfo info=usum_validate_save(data,got); printf("Resultado: %s\n\n",info.valid?"VALIDA":"NO VALIDADA"); printf("%s\n",info.message); printf("Tamano: 0x%lX bytes\n",(unsigned long)info.size); printf("Bloques: %lu/%lu\n",(unsigned long)info.valid_blocks,(unsigned long)info.total_blocks); if(info.valid)printf("\nSiguiente: leer datos del entrenador.\n"); free(data);
}
int main(int argc,char **argv){(void)argc;(void)argv;gfxInitDefault();consoleInit(GFX_TOP,NULL);consoleInit(GFX_BOTTOM,NULL);
 consoleSelect(GFX_TOP);printf("PKHeX Gen 7 - Ultrasol\n======================\nLector experimental de partidas\nSolo lectura: no modifica archivos.\n");
 consoleSelect(GFX_BOTTOM);printf("A: analizar partida\nSTART: salir\n\nArchivo esperado:\n%s\n\nUsa una copia exportada y desencriptada.\n",SAVE_PATH);
 while(aptMainLoop()){hidScanInput();u32 down=hidKeysDown();if(down&KEY_START)break;if(down&KEY_A){consoleSelect(GFX_BOTTOM);consoleClear();printf("Analisis de Pokemon Ultrasol\n\n");inspect_save();printf("\nA: analizar otra vez\nSTART: salir\n");}gfxFlushBuffers();gfxSwapBuffers();gspWaitForVBlank();}
 gfxExit();return 0;}
