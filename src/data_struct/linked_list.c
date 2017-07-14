static inline bool
linked_list_legal_p(s_linked_list_t *linked_list)
{
    if (linked_list == NULL) {
        return false;
    } else if (linked_list->next == linked_list) {
        return false;
    } else if (linked_list->prev == linked_list) {
        return false;
    } else {
        return true;
    }
}

static inline bool
linked_list_illegal_p(s_linked_list_t *linked_list)
{
    return !linked_list_legal_p(linked_list);
}

static inline s_linked_list_t *
linked_list_next_i(s_linked_list_t *linked_list)
{
    kassert(linked_list_legal_p(linked_list));

    return linked_list->next;
}

s_linked_list_t *
linked_list_next(s_linked_list_t *linked_list)
{
    if (linked_list_illegal_p(linked_list)) {
        return PTR_INVALID;
    } else {
        return linked_list_next_i(linked_list);
    }
}

static inline s_linked_list_t *
linked_list_prev_i(s_linked_list_t *linked_list)
{
    kassert(linked_list_legal_p(linked_list));

    return linked_list->prev;
}

s_linked_list_t *
linked_list_prev(s_linked_list_t *linked_list)
{
    if (linked_list_illegal_p(linked_list)) {
        return PTR_INVALID;
    } else {
        return linked_list_prev_i(linked_list);
    }
}

static inline s_linked_list_t *
linked_list_insert_after_i(s_linked_list_t *node, s_linked_list_t *inserted)
{
    s_linked_list_t *next;

    kassert(linked_list_legal_p(node));
    kassert(inserted);

    next = linked_list_next_i(node);

    node->next = inserted;
    inserted->prev = node;
    inserted->next = next; /* It also take care of next == NULL */

    if (next) {
        next->prev = inserted;
    }

    return inserted;
}

s_linked_list_t *
linked_list_insert_after(s_linked_list_t *node, s_linked_list_t *inserted)
{
    if (linked_list_illegal_p(node)) {
        return PTR_INVALID;
    } else if (inserted == NULL) {
        return PTR_INVALID;
    } else {
        return linked_list_insert_after_i(node, inserted);
    }
}

static inline s_linked_list_t *
linked_list_insert_before_i(s_linked_list_t *node, s_linked_list_t *inserted)
{
    s_linked_list_t *prev;

    kassert(linked_list_legal_p(node));
    kassert(inserted);

    prev = linked_list_prev_i(node);

    node->prev = inserted;
    inserted->next = node;
    inserted->prev = prev; /* It also take care of next == NULL */

    if (prev) {
        prev->next = inserted;
    }

    return inserted;
}

s_linked_list_t *
linked_list_insert_before(s_linked_list_t *node, s_linked_list_t *inserted)
{
    if (linked_list_illegal_p(node)) {
        return PTR_INVALID;
    } else if (inserted == NULL) {
        return PTR_INVALID;
    } else {
        return linked_list_insert_before_i(node, inserted);
    }
}

static inline s_linked_list_t *
linked_list_remove_i(s_linked_list_t *node)
{
    s_linked_list_t *next;
    s_linked_list_t *prev;

    kassert(linked_list_legal_p(node));

    next = linked_list_next_i(node);
    prev = linked_list_prev_i(node);

    if (next) {
        next->prev = prev;
    }

    if (prev) {
        prev->next = next;
    }

    return node;
}

s_linked_list_t *
linked_list_remove(s_linked_list_t *node)
{
    if (linked_list_illegal_p(node)) {
        return PTR_INVALID;
    } else {
        return linked_list_remove_i(node);
    }
}

static inline bool
linked_list_head_ip(s_linked_list_t *node)
{
    kassert(linked_list_legal_p(node));

    if (node->prev == NULL) {
        return true;
    } else {
        return false;
    }
}

bool
linked_list_head_p(s_linked_list_t *node)
{
    if (linked_list_illegal_p(node)) {
        return false;
    } else {
        return linked_list_head_ip(node);
    }
}

static inline bool
linked_list_tail_ip(s_linked_list_t *node)
{
    kassert(linked_list_legal_p(node));

    if (node->next == NULL) {
        return true;
    } else {
        return false;
    }
}

bool
linked_list_tail_p(s_linked_list_t *node)
{
    if (linked_list_illegal_p(node)) {
        return false;
    } else {
        return linked_list_tail_ip(node);
    }
}

static inline void
linked_list_initialize_i(s_linked_list_t *node)
{
    kassert(linked_list_legal_p(node));

    node->next = node->prev = NULL;
}

void
linked_list_initialize(s_linked_list_t *node)
{
    if (linked_list_illegal_p(node)) {
        return;
    } else {
        linked_list_initialize_i(node);
    }
}

