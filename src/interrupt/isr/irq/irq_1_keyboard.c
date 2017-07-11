/*
 *     The PS/2 controller, or keyboard controller. It is single chip(8042) in
 * early days. It has 2 connector, IRQ 1 for keyboard, IRQ 12 for mouse. PS/2
 * controller has 2 (one byte) buffer for data. One for data received from
 * devices that is waiting to be read from you OS, and another for data writern
 * by your OS.
 *     The ouput buffer contains devices output data.
 *     The input buffer contains devices input data.
 *     PS/2 controller IO ports
 * +---------+-------------+---------+
 * | IO port | Access Type | Purpose |
 * +---------+-------------+---------+
 * | 0x60    | R/W         | Data    |
 * +---------+-------------+---------+
 * | 0x64    | R           | Status  |
 * +---------+-------------+---------+
 * | 0x64    | W           | Command |
 * +---------+-------------+---------+
 */

static inline uint8
irq_1_keyboard_data_key(s_keyboard_data_t *data)
{
    kassert(data);

    return data->key;
}

static inline uint8
irq_1_keyboard_data_release(s_keyboard_data_t *data)
{
    kassert(data);

    return data->release;
}

static inline uint8
irq_1_keyboard_key_to_ascii(uint8 key)
{
    uint8 c;

    if (irq_1_keyboard_key_shift_pressed_p()
        && irq_1_keyboard_key_shifted_p(key)) {
        c = ascii_map[key].shifted;
    } else {
        c = ascii_map[key].ascii;
    }

    return c;
}

static inline bool
irq_1_keyboard_pressed_sensitive_p(uint8 key)
{
    switch (key) {
        case KEYBOARD_KEY_SHIFT_L:
        case KEYBOARD_KEY_SHIFT_R:
            return true;
        default:
            return false;
    }
}

static inline s_keyboard_pressed_t *
irq_1_keyboard_pressed(void)
{
    return &keyboard_pressed;
}

static inline uint8
irq_1_keyboard_pressed_key(uint32 i)
{
    s_keyboard_pressed_t *pressed;

    kassert(i < KEYBOARD_PRESSED_MAX);

    pressed = irq_1_keyboard_pressed();

    return pressed->array[i];
}

static inline void
irq_1_keyboard_pressed_key_set(uint8 key, uint32 i)
{
    s_keyboard_pressed_t *pressed;

    kassert(i < KEYBOARD_PRESSED_MAX);

    pressed = irq_1_keyboard_pressed();

    pressed->array[i] = key;
}

static inline void
irq_1_keyboard_pressed_key_clean(uint32 i)
{
    s_keyboard_pressed_t *pressed;

    kassert(i < KEYBOARD_PRESSED_MAX);

    pressed = irq_1_keyboard_pressed();

    pressed->array[i] = KEYBOARD_KEY_NULL;
}

static inline bool
irq_1_keyboard_pressed_null_key_p(uint32 i)
{
    uint8 key;

    kassert(i < KEYBOARD_PRESSED_MAX);

    key = irq_1_keyboard_pressed_key(i);

    if (key == KEYBOARD_KEY_NULL) {
        return true;
    } else {
        return false;
    }
}

static inline void
irq_1_keyboard_pressed_key_add(uint8 key)
{
    uint32 i;
    uint32 limit;

    RETURN_IF_FALSE(irq_1_keyboard_pressed_sensitive_p(key));

    i = 0;
    limit = KEYBOARD_PRESSED_MAX;

    while (i < limit) {
        if (irq_1_keyboard_pressed_null_key_p(i)) {
            irq_1_keyboard_pressed_key_set(key, i);
            return;
        }

        i++;
    }
}

static inline void
irq_1_keyboard_pressed_key_remove(uint8 key)
{
    uint32 i;
    uint32 limit;

    RETURN_IF_FALSE(irq_1_keyboard_pressed_sensitive_p(key));

    i = 0;
    limit = KEYBOARD_PRESSED_MAX;

    while (i < limit) {
        if (irq_1_keyboard_pressed_key(i) == key) {
            irq_1_keyboard_pressed_key_clean(i);
            return;
        }

        i++;
    }
}

static inline void
irq_1_keyboard_key_release(uint8 key)
{
    RETURN_IF_FALSE(irq_1_keyboard_pressed_sensitive_p(key));

    return irq_1_keyboard_pressed_key_remove(key);
}

static inline bool
irq_1_keyboard_key_pressed_p(uint8 key)
{
    uint32 i;
    uint32 limit;

    i = 0;
    limit = KEYBOARD_PRESSED_MAX;

    while (i < limit) {
        if (irq_1_keyboard_pressed_key(i) == key) {
            return true;
        }

        i++;
    }

    return false;
}

static inline bool
irq_1_keyboard_key_shift_pressed_p(void)
{
    if (irq_1_keyboard_key_pressed_p(KEYBOARD_KEY_SHIFT_L)) {
        return true;
    } else if (irq_1_keyboard_key_pressed_p(KEYBOARD_KEY_SHIFT_R)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
irq_1_keyboard_key_shifted_p(uint8 key)
{
    switch (key) {
        case KEYBOARD_KEY_0:
        case KEYBOARD_KEY_1:
        case KEYBOARD_KEY_2:
        case KEYBOARD_KEY_3:
        case KEYBOARD_KEY_4:
        case KEYBOARD_KEY_5:
        case KEYBOARD_KEY_6:
        case KEYBOARD_KEY_7:
        case KEYBOARD_KEY_8:
        case KEYBOARD_KEY_9:

        case KEYBOARD_KEY_Q:
        case KEYBOARD_KEY_W:
        case KEYBOARD_KEY_E:
        case KEYBOARD_KEY_R:
        case KEYBOARD_KEY_T:
        case KEYBOARD_KEY_Y:
        case KEYBOARD_KEY_U:
        case KEYBOARD_KEY_I:
        case KEYBOARD_KEY_O:
        case KEYBOARD_KEY_P:

        case KEYBOARD_KEY_A:
        case KEYBOARD_KEY_S:
        case KEYBOARD_KEY_D:
        case KEYBOARD_KEY_F:
        case KEYBOARD_KEY_G:
        case KEYBOARD_KEY_H:
        case KEYBOARD_KEY_J:
        case KEYBOARD_KEY_K:
        case KEYBOARD_KEY_L:

        case KEYBOARD_KEY_Z:
        case KEYBOARD_KEY_X:
        case KEYBOARD_KEY_C:
        case KEYBOARD_KEY_V:
        case KEYBOARD_KEY_B:
        case KEYBOARD_KEY_N:
        case KEYBOARD_KEY_M:
            return true;
        default:
            return false;
    }
}

void
irq_1_keyboard_handler(s_pro_context_t *context)
{
    uint8 c;
    uint8 key;
    uint8 release;
    s_keyboard_data_t *data;

    code = io_bus_read_byte(IRQ_1_KEYBOARD_DATA);
    data = (void *)&code;

    key = irq_1_keyboard_data_key(data);
    release = irq_1_keyboard_data_release(data);

    if (release) {
        c = irq_1_keyboard_key_to_ascii(key);
        printf_vga("%c", c);
        irq_1_keyboard_key_release(key);
    } else { /* press key */
        irq_1_keyboard_pressed_key_add(key);
    }

    if (false) {
        printf_vga_tk("Triggered keyboard %x -> eip %x.\n", code, context->eip);
    }
}

