.global keyboard_read

keyboard_read:
    inb $0x60, %al
    ret
