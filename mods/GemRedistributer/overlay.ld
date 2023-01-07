__heap_base = __ovr_end;

__ovr_start = 0x8000b0b8;

SECTIONS {
    OVERLAY __ovr_start : SUBALIGN(4)
    {
        .asmhook_cds
        {
            . = . + 0x28d80;
            KEEP(asm/hook_cd.o(.text*))
            KEEP(asm/hook_cd.o(.rodata*))
            KEEP(asm/hook_cd.o(.sdata*))
            KEEP(asm/hook_cd.o(.data*))
            KEEP(asm/hook_cd.o(.sbss*))
            KEEP(asm/hook_cd.o(.bss*))
            KEEP(asm/hook_cd.o(.ctors))
            
            . = ALIGN(4);
            __ovr_end = .;
        }
        .srccd_loadc
        {
            KEEP(src/cd_load.o(.text*))
            KEEP(src/cd_load.o(.rodata*))
            KEEP(src/cd_load.o(.sdata*))
            KEEP(src/cd_load.o(.data*))
            KEEP(src/cd_load.o(.sbss*))
            KEEP(src/cd_load.o(.bss*))
            KEEP(src/cd_load.o(.ctors))
            
            . = ALIGN(4);
            __ovr_end = .;
        }
        .mod
        {
            . = . + 0xf48;
            KEEP(src/GemRedistributer.o(.text*))
            KEEP(src/cutscene.o(.text*))
            KEEP(./../../common/my_math.o(.text*))
            KEEP(./../../common/moby.o(.text*))
            KEEP(./../../common/custom_text.o(.text*))
            KEEP(src/GemRedistributer.o(.rodata*))
            KEEP(src/cutscene.o(.rodata*))
            KEEP(./../../common/my_math.o(.rodata*))
            KEEP(./../../common/moby.o(.rodata*))
            KEEP(./../../common/custom_text.o(.rodata*))
            KEEP(src/GemRedistributer.o(.sdata*))
            KEEP(src/cutscene.o(.sdata*))
            KEEP(./../../common/my_math.o(.sdata*))
            KEEP(./../../common/moby.o(.sdata*))
            KEEP(./../../common/custom_text.o(.sdata*))
            KEEP(src/GemRedistributer.o(.data*))
            KEEP(src/cutscene.o(.data*))
            KEEP(./../../common/my_math.o(.data*))
            KEEP(./../../common/moby.o(.data*))
            KEEP(./../../common/custom_text.o(.data*))
            KEEP(src/GemRedistributer.o(.sbss*))
            KEEP(src/cutscene.o(.sbss*))
            KEEP(./../../common/my_math.o(.sbss*))
            KEEP(./../../common/moby.o(.sbss*))
            KEEP(./../../common/custom_text.o(.sbss*))
            KEEP(src/GemRedistributer.o(.bss*))
            KEEP(src/cutscene.o(.bss*))
            KEEP(./../../common/my_math.o(.bss*))
            KEEP(./../../common/moby.o(.bss*))
            KEEP(./../../common/custom_text.o(.bss*))
            KEEP(src/GemRedistributer.o(.ctors))
            KEEP(src/cutscene.o(.ctors))
            KEEP(./../../common/my_math.o(.ctors))
            KEEP(./../../common/moby.o(.ctors))
            KEEP(./../../common/custom_text.o(.ctors))
            
            . = ALIGN(4);
            __ovr_end = .;
        }
    }
}
