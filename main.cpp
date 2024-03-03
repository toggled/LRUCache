#include <unordered_map> // hashtable
#include <iostream>
class Node{
    public:
    int key = -1;
    int val = -1;
    Node *next = NULL;
    Node *prev = NULL;
    Node(){}
    Node(int key, int value){
        val = value;
        this->key = key;
    }
};
class DoubleLinkedList{
    Node* head = new Node();
    Node* tail = new Node();
    public:
    DoubleLinkedList(){
        head->next = tail;
        tail->prev = head;
    }
    void insert(Node* node){
        // We insert at head. if capacity exceeds, delete the node from the tail
        head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
    }
    int evict(){
        // Same as deleting the tail Node.
        int evicted_key = tail->prev->key;
        tail = tail->prev;
        tail->next = NULL;
        tail->val = -1;
        tail->key = -1;
        return evicted_key;
    }
    int get(Node * n){
        // "Del and insertfirst"/"move to head" to make n the Most recently used
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
        return n->val;
    }
    void update(Node *n, int value){
        // Update the value of node n, then "move to head" to make n Most recently used
        n->val = value;
        // move to head 
        n->prev->next = n->next;
        n->next->prev = n->prev;
        n->next = head->next;
        n->prev = head;
        head->next->prev = n;
        head->next = n;
    }
    void print(){
        auto it = head;
        while(it!=NULL){
            std::cout<< "("<<it->key<<","<<it->val<<")-> ";
            it = it->next;
        }
        std::cout<<"\n";
    }
};

class LRUCache {
    std::unordered_map<int,Node*> hashtable; //integer key, address of node in the linked list as value
    DoubleLinkedList cache;
    int current_size = 0;
    int capacity = 0;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        auto it = hashtable.find(key);
        if (it != hashtable.end()){
            // std::cout<<"key exists!\n";
            auto address = hashtable[key];
            // print(typeof(address));
            return cache.get(address);
        }
        return -1;
    }
    
    void put(int key, int value) {
        auto it = hashtable.find(key);
        if (it != hashtable.end()){ // key exists
             auto address = hashtable[key];
             cache.update(address, value);
        }
        else{
            Node* n = new Node(key,value);
            if (current_size>= capacity){
                int evicted_key = cache.evict();
                current_size -= 1;
                hashtable.erase(evicted_key);
            }
            cache.insert(n);
            current_size+=1;
            hashtable[key] = n;
        }
        // cache.print();
    }
    // void print(){
    //     cache.print();
    // }
};
