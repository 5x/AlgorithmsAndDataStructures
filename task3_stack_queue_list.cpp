#include <iostream>

template<class T>
struct Node {
    T value;
    Node* next;

    Node(T _value, Node* _next) : value(_value), next(_next) {
    }
};

template<class T>
class Stack {
public:
    Stack() {
        last = NULL;
    }

    ~Stack() {
        clear();
    }

    void push(T const& value) {
        last = new Node<T>(value, last);
    }

    T peek() const {
        return (isEmpty()) ? NULL : last->value;
    }

    T pop() {
        if (isEmpty()) {
            return NULL;
        }

        T value = last->value;
        Node<T>* tmp = last->next;
        delete last;
        last = tmp;
        return value;
    }

    bool isEmpty() const {
        return (last == NULL);
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    void print() const {
        std::cout << '[';

        if (isEmpty()) {
            std::cout << "<empty>";
        } else {
            Node<T>* curr = last;

            while (curr) {
                std::cout << curr->value << ", ";
                curr = curr->next;
            }
        }

        std::cout << ']' << std::endl;
    }

private:
    Node<T>* last;
};


template<class T>
class Queue {
public:
    Queue() {
        head = tail = NULL;
    }

    ~Queue() {
        clear();
    }

    void enqueue(T const& value) {
        if (tail) {
            tail->next = new Node<T>(value, NULL);
            tail = tail->next;
        } else {
            head = tail = new Node<T>(value, head);
        }
    }

    T dequeue() {
        if (isEmpty()) {
            return NULL;
        }

        T value = head->value;
        Node<T>* tmp = head->next;
        delete head;
        head = tmp;
        return value;
    }

    bool isEmpty() const {
        return (head == NULL);
    }

    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void print() const {
        std::cout << '[';

        if (isEmpty()) {
            std::cout << "<empty>";
        } else {
            Node<T>* curr = head;

            while (curr) {
                std::cout << curr->value << ", ";
                curr = curr->next;
            }
        }

        std::cout << ']' << std::endl;
    }

private:
    Node<T>* head;
    Node<T>* tail;
};


template<class T>
class List {
public:
    List() {
        head = tail = NULL;
    }

    ~List() {
        clear();
    }

    /* Insert value to end of list */
    void add(const T& value) {
        if (isEmpty()) {
            head = tail = new Node<T>(value, NULL);
        } else {
            tail->next = new Node<T>(value, NULL);
            tail = tail->next;
        }
    }

    void remove(Node<T>* node) {
        if (isEmpty()) {
            return;
        }

        if (node->next == NULL) {
            removeLast();
        } else {
            *node = *node->next;
        }
    }

    void removeLast() {
        if (head->next == NULL) {
            delete tail;
            head = tail = NULL;
        } else {
            Node<T>* prev = head;

            while (prev->next->next) {
                prev = prev->next;
            }

            tail = prev;
            tail->next = NULL;

            delete prev->next;
        }
    }

    /* Insert value to start of list */
    void insert(const T& value) {
        head = new Node<T>(value, head);
    }

    /* Insert value after @prev node */
    void insert(const T& value, Node<T>* prev) {
        prev->next = new Node<T>(value, prev->next);
    }

    void clear() {
        Node<T>* tmp = NULL;

        while (!isEmpty()) {
            tmp = head;
            head = head->next;
            delete (tmp);
        }
    }

    bool isEmpty() const {
        return (head == NULL);
    }

    void print() const {
        std::cout << '[';
        if (isEmpty()) {
            std::cout << "<empty>";
        } else {
            Node<T>* curr = head;

            while (curr) {
                std::cout << curr->value << ", ";
                curr = curr->next;
            }
        }

        std::cout << ']' << std::endl;
    }

    Node<T>* first() const {
        return head;
    }

    Node<T>* last() const {
        return tail;
    }

protected:
    Node<T>* head;
    Node<T>* tail;
};


void testList() {
    std::cout << "\n-----------\nList:\n-----------\n";
    List<int>* list = new List<int>();

    std::cout << "Print(First->Last) stack: ";
    list->print();
    std::cout << "Add to end (60): ";
    list->add(60);
    list->print();
    std::cout << "Add to start (25, 5): ";
    list->insert(25);
    list->insert(5);
    list->print();
    std::cout << "Add after first (10): ";
    list->insert(10, list->first());
    list->print();
    std::cout << "Remove first: ";
    list->remove(list->first());
    list->print();
    std::cout << "Remove last: ";
    list->remove(list->last());
    list->print();
    std::cout << "Empty list: ";
    list->clear();
    list->print();

    list->~List();
}

void testStack() {
    std::cout << "\n-----------\nStack:\n-----------\n";
    Stack<int>* stack = new Stack<int>();

    std::cout << "Print(Last->First) stack: ";
    stack->print();
    std::cout << "Push (5): ";
    stack->push(5);
    stack->print();
    std::cout << "Push (10, 25, 60): ";
    stack->push(10);
    stack->push(25);
    stack->push(60);
    stack->print();
    std::cout << "Pop(" << stack->pop() << "): ";
    stack->print();
    std::cout << "Pop(" << stack->pop() << "): ";
    stack->print();
    std::cout << "Peak(" << stack->peek() << "): ";
    stack->print();
    std::cout << "Empty Stack: ";
    stack->clear();
    stack->print();

    stack->~Stack();
}

void testQueue() {
    std::cout << "\n-----------\nQueue:\n-----------\n";
    Queue<int>* queue = new Queue<int>();

    std::cout << "Print(First->Last) queue: ";
    queue->print();
    std::cout << "Enqueue (5): ";
    queue->enqueue(5);
    queue->print();
    std::cout << "Enqueue (10, 25, 60): ";
    queue->enqueue(10);
    queue->enqueue(25);
    queue->enqueue(60);
    queue->print();
    std::cout << "Dequeue(" << queue->dequeue() << "): ";
    queue->print();
    std::cout << "Dequeue(" << queue->dequeue() << "): ";
    queue->print();
    std::cout << "Empty Queue: ";
    queue->clear();
    queue->print();

    queue->~Queue();
}

int main() {
    testList();
    testStack();
    testQueue();

    system("pause");

    return 0;
}
