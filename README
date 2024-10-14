1. Introducción
Este informe detalla las modificaciones realizadas en el sistema operativo xv6 RISC-V para implementar un sistema de prioridades en el planificador de procesos. Además, se incluye un programa de prueba que verifica el correcto funcionamiento del nuevo planificador. A lo largo del desarrollo, se abordaron desafíos de sincronización y gestión eficiente de procesos, los cuales se documentan con las soluciones adoptadas.

2. Modificaciones Realizadas
2.1. Estructura del Proceso (proc.h)
Se añadieron dos nuevos campos a la estructura del proceso en proc.h:

prioridad: Define la prioridad del proceso (0 = mayor prioridad).
boost: Incremento o decremento de la prioridad (inicia en 1).

2.2. Inicialización de Prioridad y Boost (proc.c)
En la función allocproc(), se inicializaron los campos prioridad y boost. Cada nuevo proceso comienza con prioridad = 0 y boost = 1.

Modificación en allocproc():
Ubicación: kernel/proc.c

2.3. Modificación del Scheduler (scheduler())
Se modificó el scheduler para:

Buscar el proceso con mayor prioridad disponible (más bajo el valor de prioridad).
Aumentar la prioridad de los procesos RUNNABLE según su boost.
Alternar el boost entre 1 y -1 si la prioridad llega a los límites (0 o 9).
Evitar colisiones de locks, liberando los procesos que no se seleccionan.

3. Programa de Prueba
Se creó un programa de prueba llamado prioridad_test.c para validar el comportamiento del nuevo sistema de prioridades. Este programa genera 20 procesos con fork() y cada uno imprime un mensaje con su ID. Se añadió un delay proporcional al ID para evitar colisiones de salida.

Código de prioridad_test.c:
Ubicación: user/prioridad_test.c

3.1. Compilación del Programa de Prueba
Agregar prioridad_test al Makefile: Modificar el archivo Makefile para que incluya el nuevo programa:

5. Dificultades Encontradas y Soluciones
5.1. Salidas Mezcladas en la Consola
Problema: Varios procesos imprimían simultáneamente, generando texto desordenado.
Solución: Se añadió un sleep() proporcional al ID del proceso para evitar que todos impriman al mismo tiempo.
5.2. Locks Ineficientes en el Scheduler
Problema: Si no se liberan los locks correctamente, se puede generar un deadlock.
Solución: Se ajustaron los bloqueos de manera que solo el proceso seleccionado mantenga su lock hasta que termine.
6. Conclusión
El sistema de prioridades en xv6 fue implementado con éxito. Las prioridades se ajustan dinámicamente con un boost, alternando entre 1 y -1 para evitar que los procesos de baja prioridad sean ignorados indefinidamente. El scheduler modificado garantiza que el proceso con mayor prioridad siempre sea ejecutado primero. El programa de prueba confirma el correcto funcionamiento del sistema.