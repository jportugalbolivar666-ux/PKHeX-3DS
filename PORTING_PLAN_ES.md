# Plan de adaptación — Pokémon Ultrasol

## Fase 1 — lector seguro (incluida)
Reconocer exportación desencriptada USUM de 0x6CC00 bytes, marcador BEEF y tabla de 39 bloques. Solo lectura.

## Fase 2 — CRC de bloques
Portar `Checksums.CRC16Invert` de PKHeX y verificar cada bloque con el checksum guardado en la tabla.

## Fase 3 — entrenador y equipo
Portar lectura de los bloques MyStatus y PokePartySave. Mostrar nombre, TID/SID y Pokémon del equipo.

## Fase 4 — cajas
Interpretar BoxPokemon y mostrar las cajas, respetando offsets y tamaños de PKHeX.

## Fase 5 — edición y guardado
Editar una copia temporal, recalcular CRC de bloques modificados y gestionar firma USUM. Nunca sobrescribir automáticamente el original.

## Restricciones
PKHeX.Core es C#/.NET y no se enlaza directamente como biblioteca .NET en un homebrew nativo de 3DS. La lógica se porta por módulos a C/C++. Citra ejecuta homebrew compilado para 3DS; no convierte una aplicación Windows Forms en programa 3DS.
