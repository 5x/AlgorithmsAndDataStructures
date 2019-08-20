#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
private:
    int length;
    std::vector<int>* storage;

public:
    Graph(int _length) {
        length = _length + 1;
        storage = new std::vector<int>[length];
    }

    ~Graph() {
        delete[] storage;
    }

    void add(int from, int to) {
        storage[from].push_back(to);
    }

    /* Breadth-first search */
    void BFS(int index) {
        bool* visited = new bool[length]();
        std::queue<int> queue;
        queue.push(index);

        std::cout << "BFS: ";

        while (!queue.empty()) {
            index = queue.front();

            if (visited[index]) {
                break;
            }

            std::cout << index << ", ";
            visited[index] = true;
            queue.pop();

            for (std::vector<int>::iterator i = storage[index].begin(); i != storage[index].end(); i++) {
                if (!visited[*i]) {
                    queue.push(*i);
                }
            }
        }

        std::cout << std::endl;

        delete visited;
    }

    /* Depth-first search */
    void DFS(int start_index) {
        bool* visited = new bool[length]();
        std::stack<int> stack;

        stack.push(start_index);

        std::cout << "DFS: ";

        while (!stack.empty()) {
            const int edge = stack.top();

            if (visited[edge]) {
                break;
            }

            std::cout << edge << ", ";

            visited[edge] = true;
            stack.pop();

            for (std::vector<int>::iterator i = storage[edge].begin(); i != storage[edge].end(); i++) {
                if (!visited[*i]) {
                    stack.push(*i);
                }
            }
        }

        std::cout << std::endl;

        delete visited;
    }

};

int main() {
    Graph* graph = new Graph(7);
    graph->add(0, 2); graph->add(2, 0);
    graph->add(2, 3); graph->add(3, 2);
    graph->add(2, 5); graph->add(5, 2);
    graph->add(2, 4); graph->add(4, 2);
    graph->add(1, 3); graph->add(3, 1);
    graph->add(1, 7); graph->add(7, 1);
    graph->add(3, 6); graph->add(6, 3);
    graph->add(5, 7); graph->add(7, 5);
    graph->BFS(0);
    graph->DFS(0);
    graph->~Graph();

    std::cout << "----" << std::endl;
    Graph* graph2 = new Graph(7);
    graph2->add(0, 2);
    graph2->add(2, 4);
    graph2->add(2, 5);
    graph2->add(1, 3);
    graph2->add(3, 2);
    graph2->add(3, 6);
    graph2->add(5, 7);
    graph2->add(7, 1);
    graph->BFS(0);
    graph->DFS(0);
    graph2->~Graph();

    system("pause");

    return 0;
}
