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
        cout << "\n===========================================================\n";
        cout << "|        Selamat Datang di Penitipan Hewan Peliharaan Berry |\n";
        cout << "=============================================================\n";
        cout << "|              1. Push Hewan ke Stack                       |\n";
        cout << "|              2. Pop Hewan dari Stack                      |\n";
        cout << "|              3. Enqueue Hewan ke Queue                    |\n";
        cout << "|              4. Dequeue Hewan dari Queue                  |\n";
        cout << "|              5. Tampilkan Hewan di Stack                  |\n";
        cout << "|              6. Tampilkan Hewan di Queue                  |\n";
        cout << "|              7. Keluar                                    |\n";
        cout << "=============================================================\n";

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
                cout << "Terima kasih telah berkunjung.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 7);

    return 0;
}
