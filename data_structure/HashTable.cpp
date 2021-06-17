#include <iostream>
#include <cstring>

using namespace std;

/* 
    키와 값으로 문자열을 가지는 Hash _table 구현.
    해시 충돌이 일어날 때는 chaining 방식으로 해결
 */

struct Node{
    char* key;
    char* value;
    Node *next;
};

class HashTable{
private:
    const static int MAX_TABLE = 20;
    
    
    Node* _table[MAX_TABLE];
    
    int _hash(const char* str);
    
public:
    HashTable();
    ~HashTable();

    void insertNode(char* key, char* value);
    void deleteNodeByKey(char* key);
    Node* findNodeByKey(char* key);
};

int HashTable::_hash(const char* str){
    int hash = 401;
    int c;
    
    while(*str != '\0'){
        hash = ((hash << 4) + (int)(*str)) % MAX_TABLE;
        str++;
    }
    
    return hash % MAX_TABLE;
}

HashTable::HashTable(){
    for(int i = 0; i < MAX_TABLE; i++)
        _table[i] = NULL;
}
HashTable::~HashTable(){
    for(int i = 0; i < MAX_TABLE; i++){
        if (_table[i] == NULL)
            continue;
        
        while(_table[i]){
            Node* next = _table[i]->next;
            delete _table[i];
            _table[i] = next;    
        }
    }
}

void HashTable::insertNode(char* key, char* value){
    Node* node = new Node;
    node->key = key;
    node->value = value;
    node->next = NULL;
    
    int hashKey = _hash(key);
    if (_table[hashKey] == NULL){
        _table[hashKey] = node;
    }
    else{
        node->next = _table[hashKey];
        _table[hashKey] = node;
    }
}

void HashTable::deleteNodeByKey(char* key){
    int hashKey = _hash(key);
    if (_table[hashKey] == NULL)
        return;
    
    Node* delNode = NULL;
    if (strcmp(_table[hashKey]->key, key) == 0){
        delNode = _table[hashKey];
        _table[hashKey] = delNode->next;
    }
    else{
        Node* prev = _table[hashKey];
        Node* cur = prev->next;
        while(cur){
            if (strcmp(cur->key, key) == 0){
                prev->next = cur->next;
                delNode = cur;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    
    delete delNode;
}

Node* HashTable::findNodeByKey(char* key){
    int hashKey = _hash(key);
    if (_table[hashKey] == NULL)
        return NULL;
    
    if (strcmp(_table[hashKey]->key, key) == 0){
        return _table[hashKey];
    }
    else{
        Node* cur = _table[hashKey]->next;
        while(cur){
            if (strcmp(cur->key, key) == 0){
                return cur;
            }
            cur = cur->next;
        }
    }
    
    return NULL;
}


int main(){
    HashTable ht;
    
    ht.insertNode("aaa", "bbb");
    ht.insertNode("aaaa", "b33bb");
    ht.insertNode("2", "bb22b");
    ht.insertNode("33", "b4bb");
    ht.insertNode("asd", "b5bb");
    
    cout << ht.findNodeByKey("2")->value << endl;
    cout << ht.findNodeByKey("aaa")->value << endl;
    
    return 0;
}