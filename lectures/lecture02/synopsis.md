-> Литература <-
================

# Что читать?
  * Windows Internals by Mark Russinovich
  * Операционная система UNIX. Андрей Робачевский
  * Unix и Linux. Руководство системного администратора. Эви Немет.

-> Сегодня <-
=============

# Процессы
  * Что это и зачем?
  * Контекcт процесса
  * Создание и замещение
  * Дерево процессов
  * Планировщик
  * Какие бывают?

---

-> Процесс <-
==============

Процесс:
  * Экземпляр запущенного исполняемого файла.
    - Примеры
      * Один из процессов браузера
      * Сервер баз данных PostgreSQL
      * Web сервер Nginx
  * Абстракция:
    * С точки зрения Userpace: монопольное владение ресурсами
      - Память
      - Файловые и сетевые ресурсы
      - Контекст вычисления
      - etc
    * С точки зрения Kernelspace: абстракция выполняемой работы пользователя

---

-> Контекст процесса <-
=======================

-> Другие ресурсы процесса <-
  * Память
  * Вычислительный контекст - потоки
    * Поток - абстракция контекста вычисления
    * Может быть несколько
    * Разделяют ресурсы
    * Эффективное использование вычислительных ресурсов
    * stack/execution context/etc per thread
    * tid
  * Файловые дескрипторы
    + Открытые файлы
    + Открытые сокеты
  * IPC(Inter Process Communication)
    + Сигналы
    + POSIX IPC
    + SystemV IPC
    + etc
  * Credentials
    + man 7 credentials
    + pid, ppid
    + process group, session group
      + Подробней когда будем говорить про tty
    + euid, ruid, suid
    + egid, rgid, sgid
    + cwd
    + ARGV, переменные окружения, etc.
  + etc

---

-> Модели памяти процесса <-
============================

```
▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
▮               ▮
▮    STACK      ▮
▮      ▼        ▮
▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
▮               ▮
▮               ▮
▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
▮      ▲        ▮
▮     HEAP      ▮
▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
▮     DATA      ▮
▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
▮     TEXT      ▮
▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬
```

---

-> Системные вызовы <-
======================

  * man syscall

Architecture calling conventions

| arch/ABI | instruction          |syscall # |retval |
|----------|----------------------|----------|-------|
|arm64     | svc #0               |x8        |x0     |
|i386      | int $0x80            |eax       |eax    |
|x86-64    | syscall              |rax       |rax    |

Registers used to pass the system call arguments

|arch/ABI  |   arg1 | arg2 | arg3 | arg4 | arg5 | arg6 |
|----------|--------|------|------|------|------|------|
|arm64     |   x0   |x1    |x2    |x3    |x4    |x5    |
|i386      |   ebx  |ecx   |edx   |esi   |edi   |ebp   |
|x86-64    |   rdi  |rsi   |rdx   |r10   |r8    |r9    |

  * Блокировка

---

-> Системные вызовы для работы с процессами <-
==============================================

  * Создание нового процесса:
    + fork(2)
```
  const pid_t pid = fork();
  if(pid == -1) {
    // handle error
  }
  if(!pid) {
    // we are child
  }
  if(pid) {
    // we are parent
  }
```
    - fork бомба
    - clone(2)
  * Замещение контекста выполнения
    - execve(2)
```
           int
           main(int argc, char *argv[])
           {
               char *newargv[] = { NULL, "hello", "world", NULL };
               char *newenviron[] = { NULL };
               if(argc != 2) {
                   fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
                   exit(EXIT_FAILURE);
               }
               newargv[0] = argv[1];
               execve(argv[1], newargv, newenviron);
               perror("execve");   /* execve() returns only on error */
               exit(EXIT_FAILURE);
           }
```

  * Ожидание завершения процесса
    - waitpid(2)
    - SIGCHLD
  * Завершение процесса
    - exit(2)
    - kill(2)
      * SIGTERM
      * SIGKILL
      * SIGCONT
      * SIGSTOP
      * Подробней когда будет говорить об IPC
  * Как работает SHELL?

---

-> Дерево процессов <-
======================

 * Процесс № 1
    - Создается ядром - подробней когда будем говорить о загрузке
    - init/systemd
    - Система инициализации
 * Zombie - child завершился, но не позвали waitpid
    - Не занимает ресурсов
    - Не обрабатывает сигналы - нельзя убить
    - Автоматически уничтожаются при завершении parent
 * Orphan - parent завершился, а child нет
    - Переподчинение init
    - Init делает waitpid и обрабатывает SIGCHLD
 * man 1 pstree
 * man 1 ps
 * man 1 top
 * man 5 proc
 * PID namespaces
    - Безопасность
    - Виртуализация
```
^[[1msystemd,1^[[0m splash
  |-ModemManager,1496
  |   |-{ModemManager},1543
  |   `-{ModemManager},1552
  |-NetworkManager,1429 --no-daemon
  |   |-dhclient,17032 -d -q -sf /usr/lib/NetworkManager/nm-dhcp-helper -pf /run/dhclient-wlp4s0.pid -lf...
  |   |-{NetworkManager},1561
  |   `-{NetworkManager},1571
  |-accounts-daemon,1455
  |   |-{accounts-daemon},1475
  |   `-{accounts-daemon},1479
  |-acpid,1509
  |-apache2,1786 -k start
  |   |-apache2,12287 -k start
  |   |-apache2,12288 -k start
  |   |-apache2,12289 -k start
  |   |-apache2,12290 -k start
  |   |-apache2,12291 -k start
  |   `-apache2,12292 -k start

```

---

-> Scheduler <-
===============
  * interrup-driven architecture
    - devices
    - timers
  * Interrupt vector, IDT
  * Состояние процесса
    - runnable
    - running
    - sleeping: interruptible
    - sleeping: uninterruptible
    - zombie
    - Диаграмма переходов
  * Чем занимается scheduler?
    - Выбор процесса для запуска
    - Переключение контекста процесса
      * Контекст выполнения
      * Виртуальная память
      * Прочие ресурсы

---

-> Системные процессы <-
========================
  * kthreadd
  * kswapd
  * ksoftirqd
