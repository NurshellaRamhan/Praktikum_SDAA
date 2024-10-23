#include <iostream>
#include <string>
#include <limits>
#include <vector> // Include vector for dynamic arrays
#include <cmath>
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

// Fibonacci Search
int min(int a, int b) {
    return (a < b) ? a : b;
}

int fibonacciSearch(Node* head, int umurDicari) {
    if (head == nullptr) return -1;

    Node* currentNode = head;
    int n = 0; // Menentukan ukuran linked list
    while (currentNode != nullptr) {
        n++;
        currentNode = currentNode->berikutnya;
    }

    // Menggunakan vector untuk array umur yang dinamis
    vector<int> umurArray(n);  // Menginisialisasi vector dengan ukuran n
    currentNode = head;
    for (int i = 0; i < n; i++) {
        umurArray[i] = currentNode->umur;
        currentNode = currentNode->berikutnya;
    }

    int fib2 = 0;  // (m-2)'th Fibonacci No.
    int fib1 = 1;  // (m-1)'th Fibonacci No.
    int fib = fib2 + fib1;  // m'th Fibonacci

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        int i = min(offset + fib2, n - 1);

        if (umurArray[i] < umurDicari) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (umurArray[i] > umurDicari) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return i;
        }
    }

    if (fib1 && umurArray[offset + 1] == umurDicari) {
        return offset + 1;
    }

    return -1;
}

// Jump Search
int jumpSearch(Node* head, int umurDicari) {
    if (head == nullptr) return -1;

    Node* currentNode = head;
    int n = 0;
    while (currentNode != nullptr) {
        n++;
        currentNode = currentNode->berikutnya;
    }

    // Menggunakan vector untuk array umur yang dinamis
    vector<int> umurArray(n);  // Menginisialisasi vector dengan ukuran n
    currentNode = head;
    for (int i = 0; i < n; i++) {
        umurArray[i] = currentNode->umur;
        currentNode = currentNode->berikutnya;
    }

    int step = sqrt(n);
    int prev = 0;

    while (umurArray[min(step, n) - 1] < umurDicari) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    while (umurArray[prev] < umurDicari) {
        prev++;
        if (prev == min(step, n)) return -1;
    }

    if (umurArray[prev] == umurDicari) {
        return prev;
    }

    return -1;
}

// Boyer-Moore Search
#define NO_OF_CHARS 256

void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badchar[(int)str[i]] = i;
    }
}

int boyerMooreSearch(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];
    badCharHeuristic(pat, m, badchar);

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[shift + j]) {
            j--;
        }

        if (j < 0) {
            return shift; 
            shift += (shift + m < n) ? m - badchar[txt[shift + m]] : 1;
        } else {
            shift += max(1, j - badchar[txt[shift + j]]);
        }
    }

    return -1;  // Pattern tidak ditemukan
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
        cout << "|              9. Cari Hewan Berdasarkan Umur (Fibonacci)     |\n";
        cout << "|              10. Cari Hewan Berdasarkan Umur (Jump)         |\n";
        cout << "|              11. Cari Hewan Berdasarkan Nama (Boyer-Moore)  |\n";
        cout << "|              12. Keluar                                     |\n";
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
            case 9: {
                int umurDicari;
                cout << "Masukkan umur hewan yang dicari (Fibonacci Search): ";
                umurDicari = inputInteger();
                if (fibonacciSearch(head, umurDicari) != -1) {
                    cout << "Hewan dengan umur " << umurDicari << " ditemukan.\n";
                } else {
                    cout << "Hewan dengan umur " << umurDicari << " tidak ditemukan.\n";
                }
                break;
            }
            case 10: {
                int umurDicari;
                cout << "Masukkan umur hewan yang dicari (Jump Search): ";
                umurDicari = inputInteger();
                if (jumpSearch(head, umurDicari) != -1) {
                    cout << "Hewan dengan umur " << umurDicari << " ditemukan.\n";
                } else {
                    cout << "Hewan dengan umur " << umurDicari << " tidak ditemukan.\n";
                }
                break;
            }
            case 11: {
                string namaDicari;
                cout << "Masukkan nama hewan yang dicari (Boyer-Moore Search): ";
                cin.ignore();
                getline(cin, namaDicari);
                Node* current = head;
                bool ditemukan = false;
                while (current != nullptr) {
                    if (boyerMooreSearch(current->nama, namaDicari) != -1) {
                        cout << "Hewan dengan nama '" << namaDicari << "' ditemukan.\n";
                        ditemukan = true;
                        break;
                    }
                    current = current->berikutnya;
                }
                if (!ditemukan) {
                    cout << "Hewan dengan nama '" << namaDicari << "' tidak ditemukan.\n";
                }
                break;
            }
            case 12:
                cout << "Terima kasih telah berkunjung.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 12);

    return 0;
}
