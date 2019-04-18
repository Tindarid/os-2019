-> Литература <-
================

# Что читать?
  * CCNA
  * TCP/IP Illustrated volume 1

---

-> Сегодня <-
=============

# Network 101
  * L2: ethernet
  * L3: network
  * L4: transport
  * L7: application
  * Misc: firewall, DPI

---

-> Start -<
===========
  * Packet switched networks
  * Circut switched networks

---

-> L2 -<
========
 * Frame
 * MAC адрес
  - OUI
   * Vendor assigned
  - Unicast   - least signigicat bit of the first octet is 0
  - Multicast - least significant bit of the first octet is 1
  - Broadcast - ff:ff:ff:ff:ff:ff
 * Broadcast domain
  * VLAN
    * trunk
    * access
 * L2 devices:
  - hub
    * exponential backoff
  - switch
    * active learning
    * Flooding
    * FIB
  - bridge
 * Мысленный эксперимент
  - Отправка пакетов в сеть через switch

---

-> L3 -<
========
 * IP адрес
   - Unicast
   - Multicast - 224.0.0/24
   - Broadcast - 255.255.255.255
 * CIDR
   - Сначала были классы
   - Потом классов не стало
 * Кто заведует адресами?
   * IANA / RIR / LIR
   * whois
   * AS
 * ARP
  - RARP
 * Routing
  - Статическая
  - Динамическая
    * Distance vector
      - Bellman-Ford
    * Link state
      - Dijkstra
    - IGP
      * RIP
      * OSPF
    - EGP
      * BGP
        - Full view
    - stub
    - assymetric
    - anycast
    - ECMP
 * RFC1918
 * Связь с L2
  - ARP
 * DHCP
 * L3 devices:
  - Router
 * Мысленный эксперимент
  - Отправка пакетов в соседнюю сеть

---

-> L4 -<
========
  * Ports
    - Priveleged
    - Well known (/etc/services)
    - Ephemeral
  * Reliable, connection oriented
    - TCP
  * Unreliable, message oriented
    - UDP

  * TCP
    - Header
    - Handshaking
    - Retransmits
    - Congestion
    - Timers
    - HOL
    - Active open / Passive open
      * Diagram
  * UDP
  * NAT
  * Мысленный эксперимент
    - telnet vk.com 80

---

-> L7 -<
========
  * DNS
    * Root servers
    * NS, A, PTR, MX
  * QUIC
  * HTTP
  * HTTP2
  * HTTP3
  * Мысленный эксперимент:
    - Открытие в браузере vk.com

---

-> Misc -<
==============
  * Firewall
  * Application Firewall
  * DPI
  * NOC
  * tcpdump / wireshark
---
