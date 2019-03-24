### Syscalls



*   exit, fork, kill, getpid, waitpid
*   zombie process, живет, пока родитель не вызовет waitpid.
*   orphan process, если умер родитель, то новый неявно  pid == 1. 
*   strace - полезно следить за работой процесса
*   ERRNO - переменная с номером последней ошибки, strerror
*   char * strerror(int errnum) - текстовое описание ошибки
*   thread local errno переменные
*   finalizers, библиотечный вызов exit.

### Железки

*   ssd, hdd - iops, mtbf
*   считываем  и записываем секторами по 4096 байт
*   алгоритмы считывания (алгоритмы elevatorА) fifo, sstf, scan

### В unix все есть файл



1. Директории
*   . , .. , имена находящихся в ней файлов
*   формирование дерева
*   filename vs filepath
*   uid, gid - {user|group}id, у процесса есть информация о тех, кто его запустил для знания прав
*   права rwx - read, write, execute
*   chmod 123,  1 - user, 2 - group, 3 - other
*   sticky bit
*   atime
