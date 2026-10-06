.global keyboard_read
.global keyboard_readStatus

keyboard_read:
    inb $0x60, %al
    ret

keyboard_readStatus:
    inb $0x64, %al
    ret
