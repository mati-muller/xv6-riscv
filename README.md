# Informe sobre el Sistema de Permisos y Archivos Inmutables en xv6

## 1. Funcionamiento y Lógica

El objetivo de esta entrega fue desarrollar un sistema de permisos en xv6 que controle los accesos de lectura y escritura de los archivos, además de incorporar un nuevo permiso especial para marcar archivos como inmutables.

- **Permisos Básicos:**
  Se implementó un sistema de permisos mediante el campo `perm` en `struct inode`, con los siguientes valores:
  - `0`: Sin permisos.
  - `1`: Solo lectura.
  - `2`: Solo escritura.
  - `3`: Lectura y escritura (por defecto).
  - `5`: Inmutable (nuevo permiso especial).

- **Permiso Especial (Inmutable):**
  Los archivos marcados como inmutables funcionan como **solo lectura**, prohibiendo la escritura y la modificación de sus permisos, aunque sí permiten la lectura.

## 2. Cambios Realizados

### Modificaciones al Kernel

1. **Estructura `struct inode` en `file.h`:**
   - Se añadió el campo `perm` para gestionar los permisos:
     ```c
     uchar perm;
     ```
   - Este campo se inicializa con el valor `3` (lectura y escritura).

2. **Funciones Modificadas:**
   - **`iget`:** Ajustada para inicializar el campo `perm` al asignar nuevos inodos.
   - **`readi`:** Revisa si el archivo tiene permiso de lectura. Retorna un error si `perm == 2` (solo escritura) o `perm == 0` (sin permisos).
   - **`writei`:** Revisa los permisos de escritura y verifica si el archivo es inmutable (`perm == 5`). En ambos casos, retorna un error.

3. **Nueva syscall `chmod`:**
   - Se implementó para cambiar los permisos de los archivos:
     ```c
     uint64 sys_chmod(void);
     ```
   - Verifica:
     - Si el archivo es inmutable (`perm == 5`), no permite modificar permisos.
     - Si el permiso solicitado está fuera del rango válido (0-5), retorna un error.

4. **Comando `chmod`:**
   - Se creó un comando de usuario que invoca la syscall `chmod`:
     ```sh
     chmod <archivo> <perm>
     ```
   - Incluye validación para evitar valores inválidos.

5. **Programa de Pruebas:**
   - Se desarrolló el programa `testimmutable` para validar el permiso inmutable:
     - Marca un archivo como inmutable.
     - Intenta escribir y modificar permisos (ambos deben fallar).
     - Verifica que la lectura sea posible.

### Archivos Modificados y Nuevos
- **Archivos modificados:**
  - `file.h`: Adición del campo `perm` en `struct inode`.
  - `fs.c`: Ajustes en `iget`, `readi` y `writei` para manejar permisos.
  - `sysfile.c`: Implementación de la syscall `chmod`.
  - `syscall.c`: Registro de la syscall `chmod`.
  - `Makefile`: Inclusión de `_chmod` y `_testimmutable` en `UPROGS`.

- **Archivos nuevos:**
  - `user/chmod.c`: Comando para modificar permisos.
  - `user/testimmutable.c`: Programa para probar el permiso inmutable.

---

## 3. Dificultades y Soluciones

1. **Errores al compilar `chmod`:**
   - **Problema:** Las funciones `argint` y `argstr` causaban fallos.
   - **Solución:** Se separó la extracción de argumentos en pasos independientes.

2. **Problemas con constantes del kernel:**
   - **Problema:** `testimmutable` no encontraba definiciones como `O_CREATE`.
   - **Solución:** Se incluyó `kernel/fcntl.h` en los programas de usuario.

3. **Validación del Permiso Inmutable:**
   - **Problema:** Probar exhaustivamente combinaciones de permisos.
   - **Solución:** Se diseñó un conjunto completo de pruebas en `testimmutable`.

---

## 4. Conclusión

El sistema de permisos desarrollado permite un control eficiente de lectura y escritura en xv6, incluyendo la funcionalidad de archivos inmutables. Las modificaciones integraron correctamente la lógica en el kernel y el espacio de usuario, y las pruebas confirmaron su correcto funcionamiento.
