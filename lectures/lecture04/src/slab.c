struct SLAB {
    uint64_t index;
    object_t objects[64];
    SLAB *prev;
    SLAB *next;
}

pool {
    SLAB *full;
    SLAB *parted;
    SLAB *empth;
}
