#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class HashTable {
private:
    struct HashNode {
        T key;
        bool occupied;

        HashNode() : occupied(false) {}
    };

    vector<HashNode> table;
    hash<T> hasher;

public:
    HashTable(size_t size) : table(size) {}

    size_t length() const {
        size_t count = 0;
        for (const auto& node : table) {
            if (node.occupied) {
                count++;
            }
        }
        return count;
    }

    void insert(T key) {
        size_t index = hasher(key) % table.size();

        while (table[index].occupied) {
            if (table[index].key == key) {
                return; // Key already exists
            }

            index = (index + 1) % table.size(); // Linear probing
        }

        table[index].key = key;
        table[index].occupied = true;
    }

    bool find(T key) const {
        size_t index = hasher(key) % table.size();

        while (table[index].occupied) {
            if (table[index].key == key) {
                return true; // Key found
            }

            index = (index + 1) % table.size(); // Linear probing
        }

        return false; // Key not found
    }

    void remove(T key) {
        size_t index = hasher(key) % table.size();

        while (table[index].occupied) {
            if (table[index].key == key) {
                table[index].occupied = false;
                return; // Key removed
            }

            index = (index + 1) % table.size(); // Linear probing
        }
    }
};


template <typename T>
class Set {
private:
    HashTable<T> hashTable;

public:
    Set(size_t size) : hashTable(size) {}

    size_t length() const {
        return hashTable.length();
    }

    void insert(T key) {
        hashTable.insert(key);
    }

    bool contains(T key) const {
        return hashTable.find(key);
    }

    void remove(T key) {
        hashTable.remove(key);
    }
};


int main() {
    Set<int> mySet(10);

    mySet.insert(4);
    mySet.insert(2);
    mySet.insert(8);
    mySet.insert(1);
    mySet.insert(5);
    mySet.insert(7);
    mySet.insert(3);
    mySet.insert(9);
    mySet.insert(10);
    mySet.insert(6);

    cout << "Set elements: ";
    for (int i = 1; i <= 10; ++i) {
        if (mySet.contains(i)) {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Set length: " << mySet.length() << endl;

    mySet.insert(3);
    mySet.insert(6);

    cout << "Set elements after insertions: ";
    for (int i = 1; i <= 10; ++i) {
        if (mySet.contains(i)) {
            cout << i << " ";
        }
    }
    cout << endl;

    mySet.remove(2);
    mySet.remove(8);

    cout << "Set elements after deletions: ";
    for (int i = 1; i <= 10; ++i) {
        if (mySet.contains(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
    // prueba para todos los casos
    mySet.remove(1);
    mySet.remove(3);
    mySet.remove(4);
    mySet.remove(5);
    mySet.remove(6);
    mySet.remove(7);
    mySet.remove(9);
    mySet.remove(10);

    cout << "Set elements after deletions: ";
    for (int i = 1; i <= 10; ++i) {
        if (mySet.contains(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
