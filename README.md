# excalibur
[![Build Status](https://travis-ci.org/Incarnation-p-lee/excalibur.svg?branch=master)](https://travis-ci.org/Incarnation-p-lee/excalibur)

Implemented from JamesM's kernel development tutorials

```
[0x00000000] Hello, The World of OS.
[0x00000000] Boot loader magic -> 0x2badb002.
[0x00000000] In Protect Mode.
[0x00000000] Page disabled.
[0x00000000] OS image start -> 0x00100000
[0x00000000] OS image end -> 0x0010b000
[0x00000000] Stack base 0x00100fb4.
[0x00000000] Physical memory lower -> 0000000636 KB.
[0x00000000] Physical memory upper -> 0000261056 KB.
[0x00000000] GDT table initialized.
[0x00000000] IDT table initialized.
[0x00000001] IRQ timer initialized.
[0x00000b08] Page enabled from 0x00000000 -> 0x0012f000.
[0x00000d72] Page enabled from 0xc0000000 -> 0xc0400000.
[0x00055098] Page initialized.
[0x0005509f] In Protect Mode.
[0x000550a5] Page enabled.
[0x0005538d] Heap initialized.
[0x00055394] Test isr:
[0x0005539a]     Divide by zero at eip -> 0x00106186.
[0x0005539a]     Breakpoint at eip -> 0x00106187.
[0x0005539b]     Divide by zero at eip -> 0x00106189.
[0x0005539c] Test isr ................ OK.
[0x000553a5] Test page:
[0x000553ab]     Access address 0x0010b000, value 0x0010b00c.
[0x000553d7]     Access address 0xc0000000, value 0xc0040000.
[0x00055404] Test page ............... OK.
[0x0005542c] Test heap:
[0x00055456]     Allocate 0x00000008 bytes at 0xc004000c.
[0x00055482]     Allocate 0x00000008 bytes at 0xc0040028.
[0x000554b2]     Free 0xc004000c.
[0x000554d9]     Free 0xc0040028.
[0x00055503]     Allocate 0x0000000f bytes at 0xc004000c.
[0x0005552f]     Free 0xc004000c.
[0x00055f7c]     Allocate 0x00400000 bytes at 0xc040000c.
[0x00055faa]     Free 0xc040000c.
[0x00055fd1] Test heap ............... OK.
[0x00055ffa] Reach end of entry, will idle.
```
