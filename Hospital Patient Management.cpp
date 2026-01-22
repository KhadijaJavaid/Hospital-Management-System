#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* =======================
   Patient Node (Linked List)
   ======================= */
struct Patient {
    int id;
    string name;
    int age;
    string disease;
    Patient* next;

    Patient(int i, string n, int a, string d) {
        id = i;
        name = n;
        age = a;
        disease = d;
        next = NULL;
    }
};

/* =======================
   Linked List
   ======================= */
class PatientList {
private:
    Patient* head;

public:
    PatientList() {
        head = NULL;
    }

    void insert(int id, string name, int age, string disease) {
        Patient* p = new Patient(id, name, age, disease);
        p->next = head;
        head = p;
    }

   void display() {
    if (!head) {
        cout << "No patient records found\n";
        return;
    }

    cout << "\n---------------------------------------------\n";
    cout << "ID\tName\tAge\tDisease\n";
    cout << "---------------------------------------------\n";

    Patient* temp = head;
    while (temp) {
        cout << temp->id << "\t"
             << temp->name << "\t"
             << temp->age << "\t"
             << temp->disease << endl;
        temp = temp->next;
    }

    cout << "---------------------------------------------\n";
}

    void remove(int id) {
        Patient* temp = head;
        Patient* prev = NULL;

        while (temp) {
            if (temp->id == id) {
                if (prev)
                    prev->next = temp->next;
                else
                    head = temp->next;

                delete temp;
                cout << "Patient deleted successfully\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Patient not found\n";
    }

    Patient* getHead() {
        return head;
    }
};

/* =======================
   Queue (Waiting List)
   ======================= */
class PatientQueue {
private:
    int queue[100];
    int front, rear;

public:
    PatientQueue() {
        front = rear = -1;
    }

    void enqueue(int id) {
        if (rear == 99) return;
        if (front == -1) front = 0;
        queue[++rear] = id;
    }

    void display() {
        if (front == -1) {
            cout << "Queue empty\n";
            return;
        }
        for (int i = front; i <= rear; i++)
            cout << queue[i] << " ";
        cout << endl;
    }
};

/* =======================
   Binary Search Tree
   ======================= */
struct BSTNode {
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int i) {
        id = i;
        left = right = NULL;
    }
};

class PatientBST {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, int id) {
        if (!node)
            return new BSTNode(id);
        if (id < node->id)
            node->left = insert(node->left, id);
        else
            node->right = insert(node->right, id);
        return node;
    }

    bool search(BSTNode* node, int id) {
        if (!node) return false;
        if (node->id == id) return true;
        if (id < node->id)
            return search(node->left, id);
        return search(node->right, id);
    }

public:
    PatientBST() {
        root = NULL;
    }

    void insert(int id) {
        root = insert(root, id);
    }

    bool search(int id) {
        return search(root, id);
    }
};

/* =======================
   File Handling
   ======================= */
void saveToFile(PatientList& list) {
    ofstream file("patients.txt");
    Patient* temp = list.getHead();

    while (temp) {
        file << temp->id << ","
             << temp->name << ","
             << temp->age << ","
             << temp->disease << endl;
        temp = temp->next;
    }
    file.close();
}

void loadFromFile(PatientList& list, PatientBST& bst) {
    ifstream file("patients.txt");
    if (!file) return;

    int id, age;
    string name, disease;
    char comma;

    while (file >> id >> comma) {
        getline(file, name, ',');
        file >> age >> comma;
        getline(file, disease);
        list.insert(id, name, age, disease);
        bst.insert(id);
    }
    file.close();
}

/* =======================
   Main Menu
   ======================= */
int main() {
    PatientList plist;
    PatientBST bst;
    PatientQueue queue;

    loadFromFile(plist, bst);

    int choice;
    do {
        cout << "\nHospital Patient Management System\n";
        cout << "1. Add Patient\n";
        cout << "2. Display Patients\n";
        cout << "3. Search Patient\n";
        cout << "4. Delete Patient\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, age;
            string name, disease;

            cout << "Patient ID: ";
            cin >> id;
            cin.ignore();
            cout << "Name: ";
            getline(cin, name);
            cout << "Age: ";
            cin >> age;
            cin.ignore();
            cout << "Disease: ";
            getline(cin, disease);

            plist.insert(id, name, age, disease);
            bst.insert(id);
            queue.enqueue(id);

            cout << "Patient added successfully\n";
        }
        else if (choice == 2) {
            plist.display();
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Patient ID to search: ";
            cin >> id;
            if (bst.search(id))
                cout << "Patient found\n";
            else
                cout << "Patient not found\n";
        }
        else if (choice == 4) {
            int id;
            cout << "Enter Patient ID to delete: ";
            cin >> id;
            plist.remove(id);
        }
        else if (choice == 5) {
            saveToFile(plist);
            cout << "Data saved. Exiting...\n";
        }
        else {
            cout << "Invalid choice\n";
        }

    } while (choice != 5);

    return 0;
}
