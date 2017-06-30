# excalibur
[![Build Status](https://travis-ci.org/Incarnation-p-lee/excalibur.svg?branch=master)](https://travis-ci.org/Incarnation-p-lee/excalibur)

Implemented from JamesM's kernel development tutorials

```
[0x0000017a] Page enabled from 0x00000000 -> 0x00120000.
[0x000003c8] Page enabled from 0xc0000000 -> 0xc0400000.
[0x000011ac] Page initialized.
[0x000011b2] In Protect Mode.
[0x000011b9] Page enabled.
[0x000014a1] Heap initialized.
[0x000014a8] Test isr:
[0x000014ae]     Divide by zero at eip -> 0x0010611d.
[0x000014af]     Breakpoint at eip -> 0x0010611e.
[0x000014b0]     Divide by zero at eip -> 0x00106120.
[0x000014b1] Test isr ................ OK.
[0x000014ba] Test page:
[0x000014c0]     Access address 0x0010b000, value 0x0010b00c.
[0x000014ec]     Access address 0xc0000000, value 0xc0040000.
[0x00001519] Test page ............... OK.
[0x00001541] Test heap:
[0x00001569]     Allocate 0x8 bytes at 0xc004000c.
[0x00001595]     Allocate 0x8 bytes at 0xc0040028.
[0x000015c2]     Free 0xc004000c.
[0x000015eb]     Free 0xc0040028.
[0x00001615]     Allocate 0xf bytes at 0xc004000c.
[0x00001640]     Free 0xc004000c.
[0x00001667] Test heap ............... OK.
[0x00001690] Reach end of entry, will idle.

```
