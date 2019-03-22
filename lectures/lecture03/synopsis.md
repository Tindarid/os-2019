-> Литература <-
================

# Что читать?
  * The Unix Programming Environment. Brian W. Kernighan, Rob Pike
  * Advanced Programming in the Unix Environment. W. Richard Stevens

---

-> Сегодня <-
=============

Поговорим о:
  * Железе
  * Файлах и правах доступа
  * Inode
  * Директории и иерархии
  * Устройства как файлы. Все есть файл.
  * Системные вызовы для всего этого
  * Файловые системы и точки монтирования
  * Немного о VFS

---

-> HDD <-
=========
  * Картинка
  * Достоинства
    - Стоимость
    - Объем
  * Недостатки
    - Время доступа
    - Надежность

---

-> SSD <-
=========
  * Достоинства
    - Время доступа
    - Надежность
  * Недостатки
    - Надежность
    - Стоимость
    - Объем
  * NVME

---

-> Общие соображения <-
=======================
 * Минимум информации - сектор - 512 байт -> 4096 байт
 * Чтение одного байта - чтение сектора с байтом
 * Запись одного байта - считать один сектор, заменить байт и записать один сектор
 * Аналогия - процессор-память - cacheline

---

-> Интересные числа <-
======================
 * Cycle
 * Main memory reference
 * Read 4K randomly from SSD
 * Read 1 MB sequentially from SSD
 * HDD Disk seek
 * Read 1 MB sequentially from HDD disk

---

-> Интересные числа <-
======================
 * Cycle                                      1     ns
 * Main memory reference                      100   ns
 * Read 4K randomly from SSD                  150   us
 * Read 1 MB sequentially from SSD            1     ms
 * Disk seek                                  10    ms
 * Read 1 MB sequentially from disk           20    ms

---

-> Выводы для HDD <-
============
 * Читать нужно последовательно
 * Обращения к диску следует минимизировать
 * Стоимость доступа сильно дороже передачи данных

---

-> Файл <-
==========

Что такое файл?
  * С точки зрения K: абстракция для данных
  * Последовательность байт
  * Формат не определен
  * Все есть файл
  * Типы файлов:
    - regular
    - directory
    - symlink
    - socket, fifo
    - character device, block device

---

-> Директории <-
================
 * Содержит имена находящихся в нем файлов
 * . и ..
 * Формирование дерева
 * filename vs pathname
 * Права:
  - eXecute - search
  - read - directory listing
  - write - changing directory(delete or create)
  - Темные директории
 * sticky bit
   - Удалять может тот, кто имеет право записи в директорию
   - Удалять может только root или владелец файла или владелец директории
   - /tmp
 * SGID
   - Группа создаваемого файла

---

-> Inode <-
===========
  * Номер
  * Индексный дескриптор, хранит служебную информацию
  * Атрибуты
    - Размер
    - atime, ctime, mtime
    - refcounting
    - Не содержит имени - разные пути
  * SUID, SGID: change User or Group
    - Безопасность
  * Права:
    - owner, group, other
    - read, write, execute
    - root может все
  * Inode корневой файловой системы фиксирован - 2
  * Vnode

---

-> Иерархия <-
==============
 * /
   - bin/
   - dev/
   - etc/
   - sbin/
   - home/
   - var/
   - usr/
   -  bin/
   -  sbin/
   - tmp

---

-> Аттрибуты процесса <-
=========================================
 * Файловые дескрипторы
 * cwd
 * Таблица файловых дескрипторов per process
 * Глобальная таблица открытых файлов
 * Глобальная таблица vnode

---

-> Файловые системы <-
======================
 * VFS
 * Сетевые
 * Виртуальные
 * In memory
 * On disk
 * Userspace - FUSE
 * Точки монтирования

---

-> Проход по пути <-
====================
 * path - /path/to/some/file
 * Рекурсивный процесс
 * Начинаем с корня с inode 2, pathIndex - 0
    - Ищем запись директории с именем path[pathIndex]
    - inode - inode найденной записи
    - ++pathIndex
 * namei(name-inode) cache

---

-> Алгоритмы элеватора <-
=========================
  * FIFO
  * SSTF - Shortest Seek Time First
  * SCAN
  * https://slideplayer.com/slide/5209336/

---

-> Долги с прошлой лекции <-
============================

  * Пример про дорогое обращение к оперативной памяти

---

-> Диски <-
===========
  * Картинка
    - Сектор
    - Цилиндр
    - Пластина
    - Трэк
    - Шпиндель
  * Сектор диска состоит из:
    - Header: метаданные для контроллера диска
    - Данные
    - Trailer: ECC
    - Внутренная фрагментация
  * При записи данных в сектор пишем ECC
  * При чтении сверяем ECC и пытаемся исправить
  * CLV - Constant Linear Velocity(CDROM)
  * CAV - Constant Angular Velocity(HDD)
  * Partitioning - treat as separate disks
  * Logical formatting - file system
  * RAW Disk - MySQL

---

-> Диски 2 <-
=============
  * Boot block - bootstrap program at fixed location
    - MBR - master boot record - boot code + partition table
    - ROM boot code -> MBR boot code -> boot sector from boot partition -> bootstraping
  * Bad block
    - man 1 badblocks
    - Sector sparing: replace bad sectors with spare

---

-> RAID <-
==========
  * RAID - Redundant Arrays of Independent Disks
  * Reliability
    - Redundancy (mirroring, parity, ECC)
  * Performance
    - Striping
  * Levels:
    - 0 - Pure striping
    - 1 - Pure mirroring
    - 0 + 1, 1 + 0
    - 2, 3, 4, 5 - not often used at practice(different parity and ECC)
  - Картинка
  - Rebuild
    - Rebuilding degrades performance
  - Software and hardware
  - Байка про аппаратный рейды и батарейку

---

-> Организация файловых систем <-
================================
  * Структура директорий:
    - Список
    - Хэш таблица
  * Выделение памяти
    - Линейное
      * Картинка
      * Внешняя фрагментация
      * Performance(both sequential and random)
    - Список
      * Картинка
      * Нет внешней фрагментации
      * Performance: random is awful, sequential
      * Надежность
    - FAT: File Allocation Table
      * Картинка
      * Все ссылки хранятся в начале диска - их можно эффективно кэшировать в памяти
    - Индексированная
      * Отдельный блок для ссылок на данные
      * Внутрення фрагментация
    - UNIX
      * Многоуровневая адресация
  * Свободные сектора
    - Bit Vector
      * Fast
      * Space usage
    - Список

---

-> Операции с файлами <-
========================
  * Картинка
  * U: libc: API
  * K: VFS: common interface
  * K: FS: implementation
  * K: I/O control: drivers and interrupts
  * H: device

---

-> Системные вызовы <-
======================
  * Картинка
  * Файловый дескриптор
  * Создание файла
  * Открытие, закрытие
  * Позиционирование
  * Чтение, запись
  * Обрезание
  * Блокировки
  * Забегая вперед - buffer cache, картинка
  * Перемещение по файловой иерархии

---

-> Системные вызовы 2 <-
======================
  * creat, open, close, unlink
  * chdir, getcwd
  * read, write,  lseek
  * scattered, gathered IO
  * chmod, chown
  * getdents, mkdir, rmdir
  * mount, umount
  * cwd у процесса
  * dup, dup2 - подробнее в одной из следующих лекций

---

-> Пару слов о типах <-
======================
  * off_t
  * size_t, ssize_t
---

-> Common pitfalls <-
=====================
  * Утечка дескрипторов
  * TOCTOU уязвимости и как правильно? openat, etc.
---
