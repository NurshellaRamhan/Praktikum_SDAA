#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Node {
    string nama;
    string jenis;
    int umur;
    string pemilik;
    Node* berikutnya; 
};

// Pointer for the head of the linked list
Node* head = nullptr;

// Queue pointers for front and rear
Node* front = nullptr;
Node* rear = nullptr;


int inputInteger() {
    int angka;
    while (true) {
        cin >> angka;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear invalid input
            cout << "Input tidak valid. Masukkan angka: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear remaining input
            return angka;
        }
    }
}

void pushHewan() {
    Node* nodeBaru = new Node;

    cout << "Masukkan nama hewan: ";
    cin.ignore();
    getline(cin, nodeBaru->nama);
    cout << "Masukkan jenis hewan: ";
    getline(cin, nodeBaru->jenis);

    cout << "Masukkan umur hewan (angka): ";
    nodeBaru->umur = inputInteger();

    cout << "Masukkan nama pemilik: ";
    getline(cin, nodeBaru->pemilik);

    nodeBaru->berikutnya = head;
    head = nodeBaru;

    cout << "Data hewan berhasil ditambahkan ke stack.\n";
}


void popHewan() {
    if (head == nullptr) {
        cout << "Stack kosong. Tidak ada hewan yang bisa di-pop.\n";
        return;
    }

    Node* nodeDihapus = head;
    head = head->berikutnya;

    cout << "Data hewan berikut dihapus dari stack:\n";
    cout << "Nama: " << nodeDihapus->nama << "\n";
    cout << "Jenis: " << nodeDihapus->jenis << "\n";
    cout << "Umur: " << nodeDihapus->umur << " tahun\n";
    cout << "Pemilik: " << nodeDihapus->pemilik << "\n";
    delete nodeDihapus;
}


void enqueueHewan() {
    Node* nodeBaru = new Node;

    cout << "Masukkan nama hewan: ";
    cin.ignore();
    getline(cin, nodeBaru->nama);
    cout << "Masukkan jenis hewan: ";
    getline(cin, nodeBaru->jenis);

    cout << "Masukkan umur hewan (angka): ";
    nodeBaru->umur = inputInteger();

    cout << "Masukkan nama pemilik: ";
    getline(cin, nodeBaru->pemilik);

    nodeBaru->berikutnya = nullptr;

    if (rear == nullptr) {
        front = rear = nodeBaru;
    } else {
        rear->berikutnya = nodeBaru;
        rear = nodeBaru;
    }

    cout << "Data hewan berhasil ditambahkan ke queue.\n";
}

void dequeueHewan() {
    if (front == nullptr) {
        cout << "Queue kosong. Tidak ada hewan yang bisa di-dequeue.\n";
        return;
    }

    Node* nodeDihapus = front;
    front = front->berikutnya;

    if (front == nullptr) {
        rear = nullptr;
    }

    cout << "Data hewan berikut dihapus dari queue:\n";
    cout << "Nama: " << nodeDihapus->nama << "\n";
    cout << "Jenis: " << nodeDihapus->jenis << "\n";
    cout << "Umur: " << nodeDihapus->umur << " tahun\n";
    cout << "Pemilik: " << nodeDihapus->pemilik << "\n";
    delete nodeDihapus;
}

// Merge sort helper functions
Node* merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->umur <= right->umur) {
        left->berikutnya = merge(left->berikutnya, right);
        return left;
    } else {
        right->berikutnya = merge(left, right->berikutnya);
        return right;
    }
}

Node* mergeSort(Node* head) {
    if (!head || !head->berikutnya) return head;

    Node* slow = head;
    Node* fast = head->berikutnya;

    while (fast && fast->berikutnya) {
        slow = slow->berikutnya;
        fast = fast->berikutnya->berikutnya;
    }

    Node* mid = slow->berikutnya;
    slow->berikutnya = nullptr;

    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);

    return merge(left, right);
}

// Quick sort helper functions
Node* partition(Node* head, Node** newHead, Node** newEnd) {
    Node* pivot = head;
    Node* prev = nullptr, *cur = head, *tail = pivot;

    while (cur) {
        Node* next = cur->berikutnya;
        if (cur->umur > pivot->umur) { // Descending
            if (*newHead == nullptr) *newHead = cur;
            prev = cur;
        } else {
            if (prev) prev->berikutnya = cur->berikutnya;
            cur->berikutnya = nullptr;
            tail->berikutnya = cur;
            tail = cur;
        }
        cur = next;
    }

    if (*newHead == nullptr) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

Node* quickSortRecur(Node* head, Node* end) {
    if (!head || head == end) return head;

    Node* newHead = nullptr, *newEnd = nullptr;
    Node* pivot = partition(head, &newHead, &newEnd);

    if (newHead != pivot) {
        Node* temp = newHead;
        while (temp->berikutnya != pivot) temp = temp->berikutnya;
        temp->berikutnya = nullptr;

        newHead = quickSortRecur(newHead, temp);
        temp = newHead;
        while (temp->berikutnya) temp = temp->berikutnya;
        temp->berikutnya = pivot;
    }

    pivot->berikutnya = quickSortRecur(pivot->berikutnya, newEnd);
    return newHead;
}

void quickSort() {
    head = quickSortRecur(head, nullptr);
}

void tampilkanHewan(Node* head) {
    if (head == nullptr) {
        cout << "Tidak ada data hewan.\n";
    } else {
        Node* nodeSaatIni = head;
        int nomor = 1;
        while (nodeSaatIni != nullptr) {
            cout << "Hewan ke-" << nomor << ":\n";
            cout << "Nama: " << nodeSaatIni->nama << "\n";
            cout << "Jenis: " << nodeSaatIni->jenis << "\n";
            cout << "Umur: " << nodeSaatIni->umur << " tahun\n";
            cout << "Pemilik: " << nodeSaatIni->pemilik << "\n\n";
            nodeSaatIni = nodeSaatIni->berikutnya;
            nomor++;
        }
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n=============================================================\n";
        cout << "|        Selamat Datang di Penitipan Hewan Peliharaan Berry   |\n";
        cout << "===============================================================\n";
        cout << "|              1. Push Hewan ke Stack                         |\n";
        cout << "|              2. Pop Hewan dari Stack                        |\n";
        cout << "|              3. Enqueue Hewan ke Queue                      |\n";
        cout << "|              4. Dequeue Hewan dari Queue                    |\n";
        cout << "|              5. Tampilkan Hewan di Stack                    |\n";
        cout << "|              6. Tampilkan Hewan di Queue                    |\n";
        cout << "|              7. Urutkan Stack secara Ascending (Merge Sort) |\n";
        cout << "|              8. Urutkan Stack secara Descending (Quick Sort)|\n";
        cout << "|              9. Keluar                                      |\n";
        cout << "===============================================================\n";

        cout << "Masukkan pilihan: ";
        pilihan = inputInteger();

        switch (pilihan) {
            case 1:
                pushHewan();
                break;
            case 2:
                popHewan();
                break;
            case 3:
                enqueueHewan();
                break;
            case 4:
                dequeueHewan();
                break;
            case 5:
                cout << "Daftar hewan di stack:\n";
                tampilkanHewan(head);
                break;
            case 6:
                cout << "Daftar hewan di queue:\n";
                tampilkanHewan(front);
                break;
            case 7:
                head = mergeSort(head);
                cout << "Stack diurutkan secara ascending berdasarkan umur.\n";
                tampilkanHewan(head);
                break;
            case 8:
                quickSort();
                cout << "Stack diurutkan secara descending berdasarkan umur.\n";
                tampilkanHewan(head);
                break;
            case 9:
                cout << "Terima kasih telah berkunjung.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 9);

    return 0;
}
