#include "platform_api_vmcore.h"

int
os_thread_sys_init(void);

void
os_thread_sys_destroy(void);

int
bh_platform_init(void)
{
    return BHT_OK;
}

void
bh_platform_destroy(void)
{
}

void *
os_malloc(unsigned size)
{
    return malloc(size);
}

void *
os_realloc(void *ptr, unsigned size)
{
    return realloc(ptr, size);
}

void
os_free(void *ptr)
{
    free(ptr);
}

int
os_dumps_proc_mem_info(char *out, unsigned int size)
{
    return -1;
}

void *
os_mmap(void *hint, const size_t size, int prot, int flags, os_file_handle file)
{
    if (size >= UINT32_MAX) {
        return nullptr;
    }

    void *addr = BH_MALLOC(size);
    if (addr) {
        memset(addr, 0, (uint32)size);
    }

    return addr;
}

void *
os_mremap(void *old_addr, size_t old_size, size_t new_size)
{
    return os_mremap_slow(old_addr, old_size, new_size);
}

void
os_munmap(void *addr, size_t size)
{
    return BH_FREE(addr);
}

int
os_mprotect(void *addr, size_t size, int prot)
{
    return 0;
}

extern void vexos_dcache_invalidate(void);
extern void vexos_icache_invalidate(void);

void
os_dcache_flush(void)
{
    vexos_dcache_invalidate();
}

void
os_icache_flush(void *start, size_t len)
{
    vexos_icache_invalidate();
}
