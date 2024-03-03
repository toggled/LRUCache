# LRUCache
Implementation of LRU Cache

Main Idea:
1. Use a doubly linked list (DLL) to hold the `(key, value)` pairs. The DLL should have the following functions: 
   -- insert(Node* n) (Insert at the beginning of the DLL),
   -- int evict() (Deletes the tail Node and returns the `key` corresponding to the deleted node),
   -- int get(Node* n) (returns n->value and "move to head" to make n the Most recently used) and
   -- update(Node* n, int value) (Updates n->value, then "move to head" to make n Most recently used)
2. The LRUCache  maintains a hashtable with `key' as the key and pointer to the corresponding Node (containing `(key, value)` in DLL)
3. get() and put() functions of LRUCache
