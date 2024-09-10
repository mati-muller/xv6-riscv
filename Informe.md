# Informe sobre la Llamada al Sistema `yosoytupadre`

## Funcionamiento de la Llamada al Sistema

### `yosoytupadre`

La llamada al sistema `yosoytupadre` permite a un proceso verificar si otro proceso es su hijo directo. Esta funcionalidad es útil para que un proceso pueda comprobar la relación de paternidad con otro proceso específico.

## Explicación de las Modificaciones Realizadas

### Implementación de `sys_yosoytupadre`

**Código en `kernel/sysproc.c`:**

```c
uint64 sys_yosoytupadre(void) {
    int pid;
    struct proc *p = myproc(); // Obtiene el proceso actual
    
    if (argint(0, &pid) < 0) {
        return -1; // Error en la obtención del argumento
    }
    
    if (p->parent != 0 && p->parent->pid == pid) {
        return 1; // El PID proporcionado es el padre del proceso actual
    }
    
    return 0; // El PID proporcionado no es el padre del proceso actual
}


**Codigo en syscall.h**
agregue la linea para definir la llamda al padre desde el sistema
#define SYS_getppid 22
 

 **Modificaciones en otros archivos**
 En user.h y en yo soy tu padre defini la inetraccion y la salida que ia a tener la funcion de yo soy tu padre, definiendo así la apternidad del proceso mostrandome su id y en user.h defini como el usuairio tiene que llamar a la funcion.




 **Dificultades**
 Para solo agregar una funcion se tienen que tocar varios archivos y no es simple y el proceso del ancestro es muy complicado por el manejo de datosm y procesos
