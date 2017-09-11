static inline uint32
arithmetic_rate_up_i(uint32 a, uint32 base)
{
    uint32 rate_up;

    kassert(base);

    rate_up = a / base;

    if (a % base != 0) {
        rate_up++;
    }

    return rate_up;
}

uint32
arithmetic_rate_up(uint32 a, uint32 base)
{
    if (base == 0) {
        return SIZE_INVALID;
    } else {
        return arithmetic_rate_up_i(a, base);
    }
}

