#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

struct Node {
    ull value;
    struct Node *next;

    Node(ull value) {
        this->value = value;
        this->next = NULL;
    }

    void add_node(Node* node) {
        node->next = this->next;
        this->next = node;
    }

    void insert(vector<Node*> nodes) {
        nodes[nodes.size() - 1]->next = this->next;
        this->next = nodes[0];
    }

    vector<Node*> remove() {
        vector<Node*> pickup = {this->next, this->next->next, this->next->next->next};
        this->next = pickup[pickup.size() - 1]->next;
        return pickup;
    }
};

void play(map<int, Node*> hash, Node* head, int turns) {
    for (int i = 0; i < turns; i++) {
        vector<Node*> nodes = head->remove();
        int dest = head->value - 1;

        auto lambda = [&](Node* node) { return node->value == dest; };
        while (find_if(nodes.begin(), nodes.end(), lambda) != nodes.end() || dest == 0)
            dest = dest ? dest - 1 : hash.size();
        
        hash[dest]->insert(nodes);
        head = head->next;
    }
}

map<int, Node*> build_circular_linked_list(Node* head, string input, int size) {
    map<int, Node*> hash;
    hash[head->value] = head;
    head->next = head;

    for (int i = 1; i < size; i++) {
        head->add_node(new Node(i >= 9 ? i+1 : input[i] - '0'));
        head = head->next;
        hash[head->value] = head;
    }

    head = head->next;
    return hash;
}

ull p2(map<int, Node*> hash, Node* head) {
    play(hash, head, 10000000);
    return hash[1]->next->value * hash[1]->next->next->value;
}

string p1(map<int, Node*> hash, Node* head) {
    string concat = "";
    play(hash, head, 100);

    for (Node* n = hash[1]->next; n->value != 1; n = n->next)
        concat += to_string(n->value);

    return concat;
}

int main() {
    string line;
    getline(cin, line);

    Node* h1 = new Node(line[0] - '0');
    Node* h2 = new Node(line[0] - '0');

    map<int, Node*> m1 = build_circular_linked_list(h1, line, 9);
    map<int, Node*> m2 = build_circular_linked_list(h2, line, 1000000);

    cout << p1(m1, h1) << endl;
    cout << p2(m2, h2) << endl;
}