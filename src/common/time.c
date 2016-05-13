uint64
time_stamp_counter(void)
{
    uint32 data[2];
    uint64 *retval;

    retval = (void *)data;

    asm volatile (
        "rdtsc\n\t"
        "mov %%eax, %0\n\t"
        "mov %%edx, %1\n\t"
        :"=m"(data[0]), "=m"(data[1])
        :
        :"eax", "edx", "memory");

    return *retval;
}


