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

    vector<Node*> remove(int n) {
        vector<Node*> pickup;
        Node* temp = this->next;

        for (int i = 0; i < n; i++) {
            pickup.push_back(temp);
            temp = temp->next;
        }

        this->next = pickup[pickup.size() - 1]->next;
        return pickup;
    }
};

void play(map<int, Node*> hash, Node* head, int turns) {
    for (int i = 0; i < turns; i++) {
        vector<Node*> nodes = head->remove(3);
        int dest = head->value - 1;

        auto lambda = [&](Node* node) { return node->value == dest; };
        while (find_if(nodes.begin(), nodes.end(), lambda) != nodes.end() || dest == 0)
            dest = dest ? dest - 1 : hash.size();
        
        hash[dest]->insert(nodes);
        head = head->next;
    }
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

    map<int, Node*> m1, m2;

    Node* h1 = new Node(line[0] - '0');
    m1[h1->value] = h1;
    h1->next = h1;

    for (int i = 1; i < line.size(); i++) {
        h1->add_node(new Node(line[i] - '0'));
        h1 = h1->next;
        m1[h1->value] = h1;
    }

    Node* h2 = new Node(line[0] - '0');
    m2[h2->value] = h2;
    h2->next = h2;

    for (int i = 1; i < 1000000; i++) {
        h2->add_node(new Node(i >= 9 ? i+1 : line[i] - '0'));
        h2 = h2->next;
        m2[h2->value] = h2;
    }

    h1 = h1->next;
    cout << p1(m1, h1) << endl;

    h2 = h2->next;
    cout << p2(m2, h2) << endl;
}