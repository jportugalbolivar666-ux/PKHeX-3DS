# PKHeX 3DS — lector inicial de Pokémon Ultrasol

Este paquete es un **prototipo de lectura y reconocimiento**, no un editor completo.

## Funciones actuales
- Busca `sdmc:/3ds/PKHeX3DS/ultrasol.sav`.
- Comprueba el tamaño de guardado Gen 7 USUM (`0x6CC00`).
- Comprueba el marcador BEEF que PKHeX usa para reconocer partidas Gen 7.
- Comprueba los 39 IDs y longitudes de bloques contra `SaveBlockAccessor7USUM.cs`.
- No modifica ni sobrescribe la partida.

## Archivo admitido
Una exportación `.sav` **desencriptada** de Pokémon Ultrasol con estructura USUM. Copia una copia de seguridad a `sdmc:/3ds/PKHeX3DS/ultrasol.sav`.

Esta versión no lee directamente un volcado cifrado de cartucho ni extrae automáticamente la partida desde Citra.

## Compilar
1. Instala devkitPro con devkitARM y libctru.
2. Abre la terminal de devkitPro.
3. Entra en esta carpeta.
4. Ejecuta `make`.
5. El resultado esperado es `PKHeX3DS.3dsx`.

## Limitaciones
- No descifra ni vuelve a firmar partidas.
- No lee todavía el nombre del entrenador, equipo ni cajas.
- No edita Pokémon ni guarda cambios.
- La validación estructural no verifica aún los CRC de cada bloque.
- El `.3dsx` es homebrew 3DS; la compatibilidad de Citra Android con el homebrew depende de la versión y configuración del emulador.

Referencias del código fuente aportado: `PKHeX.Core/Saves/SAV7USUM.cs`, `PKHeX.Core/Saves/Access/SaveBlockAccessor7USUM.cs` y `PKHeX.Core/Saves/Util/SaveUtil.cs`.
