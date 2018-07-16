


long hash (long key, long capac);

void enlarge(HashMap* map);

void insert(HashMap* map, long key, void* data);

void* search(HashMap* map, long key);
void erase(HashMap* map, long key);

void* first(HashMap* map);

void* next(HashMap* map);
