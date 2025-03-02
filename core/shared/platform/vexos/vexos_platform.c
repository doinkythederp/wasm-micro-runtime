#include "platform_api_vmcore.h"
#include "hydrozoa.h"

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

uint64
os_time_get_boot_us(void)
{
    return hydrozoa_get_microseconds_since_boot();
}

uint64
os_time_thread_cputime_us(void)
{
    return 0;
}

korp_tid
os_self_thread(void)
{
    return NULL;
}

uint8 *
os_thread_get_stack_boundary(void)
{
    return hydrozoa_get_stack_boundary();
}

void
os_thread_jit_write_protect_np(bool enabled)
{
}

// mutext APIs

int
os_mutex_init(korp_mutex *mutex)
{
    return 0;
}

int
os_mutex_destroy(korp_mutex *mutex)
{
    return 0;
}

int
os_mutex_lock(korp_mutex *mutex)
{
    return 0;
}

int
os_mutex_unlock(korp_mutex *mutex)
{
    return 0;
}

int
os_dumps_proc_mem_info(char *out, unsigned int size)
{
    return -1;
}

// AOT APIs

void *
os_mmap(void *hint, const size_t size, int prot, int flags, os_file_handle file)
{
    if (size >= UINT32_MAX) {
        return NULL;
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

void vexos_dcache_invalidate(void);
void vexos_icache_invalidate(void);

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
