uint32
stack_size(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return SIZE_INVALID;
    } else {
        return stack_size_i(stack);
    }
}

static inline void **
stack_bp(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    return stack->bp;
}

static inline void **
stack_sp(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    return stack->sp;
}

static inline void
stack_bp_set(s_stack_t *stack, void **bp)
{
    kassert(stack_legal_ip(stack));

    stack->bp = bp;
}

static inline void
stack_sp_set(s_stack_t *stack, void **sp)
{
    kassert(stack_legal_ip(stack));

    stack->sp = sp;
}

static inline uint32
stack_size_i(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    return (uint32)(stack_sp(stack) - stack_bp(stack));
}

static inline void
stack_capacity_set(s_stack_t *stack, uint32 capacity)
{
    kassert(stack_legal_ip(stack));

    stack->capacity = capacity;
}

static inline uint32
stack_capacity_i(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    return stack->capacity;
}

uint32
stack_capacity(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return SIZE_INVALID;
    } else {
        return stack_capacity_i(stack);
    }
}

static inline bool
stack_legal_ip(s_stack_t *stack)
{
    if (stack == NULL) {
        return false;
    } else if (stack->bp == NULL) {
        return false;
    } else if (stack->sp == NULL) {
        return false;
    } else if (stack->capacity == 0) {
        return false;
    } else {
        return true;
    }
}

static inline bool
stack_illegal_ip(s_stack_t *stack)
{
    return !stack_legal_ip(stack);
}

bool
stack_legal_p(s_stack_t *stack)
{
    return stack_legal_ip(stack);
}

bool
stack_illegal_p(s_stack_t *stack)
{
    return stack_illegal_ip(stack);
}

s_stack_t *
stack_create(void)
{
    s_stack_t *stack;

    stack = kmalloc(sizeof(*stack));
    stack->bp = kmalloc(sizeof(void *) * STACK_CAPACITY_SIZE);

    stack->sp = stack->bp;
    stack->capacity = STACK_CAPACITY_SIZE;

    return stack;
}

void
stack_destroy(s_stack_t **stack)
{
    if (stack == NULL) {
        return;
    } else if (stack_legal_ip(*stack)) {
        kfree(stack_bp(*stack));
        kfree(*stack);

        *stack = NULL;
    }
}

static inline void
stack_resize_i(s_stack_t *stack, uint32 capacity)
{
    uint32 size;

    kassert(capacity);
    kassert(stack_legal_ip(stack));

    size = stack_size_i(stack);

    if (size > capacity) {
        size = capacity;
    }

    stack_bp_set(stack, krealloc(stack_bp(stack), sizeof(void *) * capacity));
    stack_sp_set(stack, stack_bp(stack) + size);
    stack_capacity_set(stack, capacity);
}

void
stack_resize(s_stack_t *stack, uint32 capacity)
{
    if (stack_illegal_ip(stack)) {
        return;
    } else if (capacity == 0) {
        return;
    } else {
        stack_resize_i(stack, capacity);
    }
}

static inline bool
stack_full_ip(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    if (stack_capacity_i(stack) == stack_size_i(stack)) {
        return true;
    } else {
        return false;
    }
}

bool
stack_full_p(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return true;
    } else {
        return stack_full_ip(stack);
    }
}

static inline uint32
stack_rest_i(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    return stack_capacity_i(stack) - stack_size_i(stack);
}

uint32
stack_rest(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return SIZE_INVALID;
    } else {
        return stack_rest_i(stack);
    }
}

void
stack_push(s_stack_t *stack, void *member)
{
    uint32 capacity;

    if (stack_illegal_ip(stack)) {
        return;
    } else if (stack_full_ip(stack)) {
        capacity = stack_capacity_i(stack) * 2;
        stack_resize_i(stack, capacity);
    }

    *stack->sp++ = member;
}

void *
stack_top(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return PTR_INVALID;
    } else if (stack_empty_ip(stack)) {
        return PTR_INVALID;
    } else {
        return *(stack_sp(stack) - 1);
    }
}

void *
stack_pop(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return PTR_INVALID;
    } else if (stack_empty_ip(stack)) {
        return PTR_INVALID;
    } else {
        return *(--stack->sp);
    }
}

static inline bool
stack_empty_ip(s_stack_t *stack)
{
    kassert(stack_legal_ip(stack));

    if (stack_bp(stack) == stack_sp(stack)) {
        return true;
    } else {
        return false;
    }
}

bool
stack_empty_p(s_stack_t *stack)
{
    if (stack_illegal_ip(stack)) {
        return false;
    } else {
        return stack_empty_ip(stack);
    }
}

void
stack_cleanup(s_stack_t *stack)
{
    if (stack_legal_ip(stack)) {
        kmemset(stack_bp(stack), 0, sizeof(void *) * stack_capacity_i(stack));
        stack_sp_set(stack, stack_bp(stack));
    }
}

static inline void
stack_fill_i(s_stack_t *stack_to, s_stack_t *stack_from)
{
    kassert(stack_legal_ip(stack_to));
    kassert(stack_legal_ip(stack_from));

    while (!stack_empty_ip(stack_from)) {
        stack_push(stack_to, stack_pop(stack_from));
    }
}

void
stack_fill(s_stack_t *stack_to, s_stack_t *stack_from)
{
    if (stack_illegal_ip(stack_to)) {
        return;
    } else if (stack_illegal_ip(stack_from)) {
        return;
    } else {
        stack_fill_i(stack_to, stack_from);
    }
}

