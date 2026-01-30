#include <iostream>
#include <fstream>
#include <cassert>


struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    LinkedList reverse() const {
        LinkedList revList;
        Node* current = head;
        while (current) {
            Node* newNode = new Node(current->data);
            newNode->next = revList.head;
            revList.head = newNode;
            current = current->next;
        }
        return revList;
    }

    bool equals(const LinkedList& other) const {
        Node* a = head;
        Node* b = other.head;
        while (a && b) {
            if (a->data != b->data) {
                return false;
            }
            a = a->next;
            b = b->next;
        }
        return a == nullptr && b == nullptr;
    }

    bool isSymmetric() const {
        LinkedList rev = this->reverse();
        return this->equals(rev);
    }

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};



void test_empty_list() {
    LinkedList list;
    assert(list.isSymmetric() == true);
    std::cout << " test_empty_list passed\n";
}

void test_single_element() {
    LinkedList list;
    list.push_back(42);
    assert(list.isSymmetric() == true);
    std::cout << " test_single_element passed\n";
}

void test_symmetric_odd() {
    LinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(2);
    list.push_back(1);
    assert(list.isSymmetric() == true);
    std::cout << "test_symmetric_odd passed\n";
}

void test_symmetric_even() {
    LinkedList list;
    list.push_back(5);
    list.push_back(7);
    list.push_back(7);
    list.push_back(5);
    assert(list.isSymmetric() == true);
    std::cout << " test_symmetric_even passed\n";
}

void test_not_symmetric() {
    LinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(45);
    list.push_back(2);
    list.push_back(1);
    assert(list.isSymmetric() == false);
    std::cout << " test_not_symmetric passed\n";
}

void test_all_same() {
    LinkedList list;
    for (int i = 0; i < 5; ++i)
        list.push_back(9);
    assert(list.isSymmetric() == true);
    std::cout << " test_all_same passed\n";
}

void test_two_different() {
    LinkedList list;
    list.push_back(10);
    list.push_back(20);
    assert(list.isSymmetric() == false);
    std::cout << " test_two_different passed\n";
}

void run_all_tests() {
    test_empty_list();
    test_single_element();
    test_symmetric_odd();
    test_symmetric_even();
    test_not_symmetric();
    test_all_same();
    test_two_different();
    std::cout << "\n all tests passed \n";
}

int main() {
    // Запуск модульных тестов
    run_all_tests();

    // Чтение из файла 
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл input.txt\n";
        return 1;
    }

    LinkedList list;
    int num;
    while (file >> num) {
        list.push_back(num);
    }
    file.close();

    if (list.isSymmetric()) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }

    return 0;
}
