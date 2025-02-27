.global vexos_dcache_invalidate
vexos_dcache_invalidate:
    push {lr}                  @ Save the return address
    cpsid i                    @ Mask interrupts

    mov r0, #0x03800000        @ Start address of user memory

    @ Clean L1 data cache in the user memory range
    @ NOTE: 0x03800000 is already aligned to cache line size (32), so no work there.
    mov r1, 0x08000000         @ End address of user memory
dcache_clean_range:

    mcr p15, 0, r0, c7, c11, 1 @ Clean and invalidate D-cache line by MVA (DCCMVAU)
    add r0, #32                @ Move to the next cache line
    cmp r0, r1                 @ Check if we've reached the end
    blo dcache_clean_range     @ If not, continue cleaning
    dsb                        @ Wait until all cache operations complete

    cpsie i                    @ Unmask interrupts
    pop {pc}                   @ Return to caller

.global vexos_icache_invalidate
vexos_icache_invalidate:
    push {lr}                  @ Save the return address
    cpsid i                    @ Mask interrupts

    @ Invalidate entire L1 instruction cache
    mov r0, #0
    mcr p15, 0, r0, c7, c1, 0  @ ICIALLUIS
    dsb                        @ Wait until all cache operations complete

    cpsie i                    @ Unmask interrupts
    pop {pc}                   @ Return to caller

