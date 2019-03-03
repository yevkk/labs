#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <string>

double rand_num(double max) {
    static std::random_device rd;
    static std::seed_seq seed{rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    static std::uniform_real_distribution<double> dist(0, max);

    return dist(gen);
}

const double chance = 5;

struct Node {
    int data = (int) 0;
    Node *next = nullptr;
    Node *bottom = nullptr;
};
typedef Node *Layer;
typedef std::vector<Layer> SkipList;

Node *add_node_to_layer(Layer &lyr, int num, Node *bottom) {
    if ((lyr == nullptr) || (lyr->data > num)) {
        Node *tmp = lyr;
        lyr = new Node;
        lyr->next = tmp;
        lyr->bottom = bottom;
        lyr->data = num;
        return lyr;
    } else {
        Node *ptr = lyr;
        while (true) {
            if (ptr->next == nullptr) break;
            else if (ptr->next->data > num) break;
            ptr = ptr->next;
        }
        Node *tmp = ptr->next;
        ptr->next = new Node;
        ptr->next->next = tmp;
        ptr->next->bottom = bottom;
        ptr->next->data = num;
        return ptr->next;
    }
}

void add_node_to_skiplist(SkipList &lst, int num, int mode = 1) {
    int lyr_num = 0;
    double rand = rand_num(10);
    Node *ptr = add_node_to_layer(lst[0], num, nullptr);
    if (mode) std::cout << "Element " << num << " added to layers: 0 ";
    while (rand < chance) {
        lyr_num++;
        if (lyr_num + 1 > lst.size()) lst.push_back(nullptr);
        ptr = add_node_to_layer(lst[lyr_num], num, ptr);
        if (mode) std::cout << lyr_num << ' ';
        rand = rand_num(10);
    }
    if (mode) std::cout << std::endl;

}

void print_layer(Layer lyr) {
    Node *ptr = lyr;
    while (ptr != nullptr) {
        std::cout << ptr->data << ' ';
        ptr = ptr->next;
    }
    std::cout << std::endl;
}

void print_skiplist(SkipList lst) {
    for (int i = lst.size() - 1; i >= 0; i--) {
        std::cout << i << ":  ";
        print_layer(lst[i]);
    }
}


int main() {
    SkipList lst;
    lst.push_back(nullptr);
    std::string str;
    int num;

    while (true) {
        std::cout << "\nEnter command: ";
        std::cin >> str;

        if (str == "stop") break;


        if (str == "add") {
            std::cout << "value: ";
            std::cin >> num;
            add_node_to_skiplist(lst, num);
            continue;
        }

        if (str == "print_list") {
            print_skiplist(lst);
            continue;
        }

        if (str == "print_layer") {
            do {
                std::cout << "Layer: ";
                std::cin >> num;
            } while ((num < 0) || (num > lst.size() - 1));
            print_layer(lst[num]);
            continue;
        }

        if (str == "help") {
            std::cout << " - stop\n" << " - add\n" << " - print_list\n" << " - print_layer\n" << " - find\n" << " - demo\n";
            continue;
        }

        std::cout << "Enter correct command (help)\n";
    }

    return 0;
}