#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm> 
#include <vector>
#include <cmath>

using namespace std;

// Struktur data untuk produk
struct Product {
    string productName;
    string brand;
    double price;
    int stock;
    string description;
    bool isAvailable;
    string category;
    Product* next;  // Pointer untuk linked list
};

// Riwayat pembelian
struct Purchase {
    string productName;
    int quantity;
    double totalPrice;
    Purchase* next;  // Pointer untuk linked list
};

// Struktur data untuk pengguna (User)
struct User {
    string username;
    string password;
    User* next;
};

// Struktur data untuk admin
struct Admin {
    string username;
    string password;
};

// Pointer ke head linked list produk dan riwayat pembelian
Product* headProduct = nullptr;
Purchase* headPurchase = nullptr;

// Manual stack untuk menyimpan produk terbaru
struct StackNode {
    string productName;
    StackNode* next;
};
StackNode* stackTop = nullptr;

void pushStack(string productName) {
    StackNode* newNode = new StackNode;
    newNode->productName = productName;
    newNode->next = stackTop;
    stackTop = newNode;
}
void popStack() {
    if (stackTop) {
        StackNode* temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
    }
}

string topStack() {
    return stackTop ? stackTop->productName : "Stack kosong";
}

// Manual queue untuk antrian produk yang dibeli
struct QueueNode {
    string productName;
    QueueNode* next;
};
QueueNode* queueFront = nullptr;
QueueNode* queueRear = nullptr;

void enqueueQueue(string productName) {
    QueueNode* newNode = new QueueNode;
    newNode->productName = productName;
    newNode->next = nullptr;
    if (!queueRear) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }
}

void dequeueQueue() {
    if (queueFront) {
        QueueNode* temp = queueFront;
        queueFront = queueFront->next;
        delete temp;
        if (!queueFront) queueRear = nullptr;
    }
}

string frontQueue() {
    return queueFront ? queueFront->productName : "Queue kosong";
}

// Pointer ke linked list pengguna dan admin
User* headUser = nullptr;
Admin admin = {"adakah", "adaterus"};  // Username dan password admin yang sudah ditentukan

// Fungsi untuk menampilkan produk
void displayProduct(Product* product) {
    cout << "Nama Produk: " << product->productName << endl;
    cout << "Merek: " << product->brand << endl;
    cout << "Deskripsi: " << product->description << endl;
    cout << "Harga: Rp. " << fixed << setprecision(2) << product->price << endl;
    cout << "Stok: " << product->stock << endl;
    cout << "Kategori: " << product->category << endl;
    cout << "Status: " << (product->isAvailable ? "Tersedia" : "Tidak Tersedia") << endl;
    cout << "---------------------------------------------" << endl;
}

void mainMenu();

// Fungsi untuk menambahkan pengguna
void registerUser() {
    User* newUser = new User;
    cout << "Masukkan username: ";
    cin >> newUser->username;
    cout << "Masukkan password: ";
    cin >> newUser->password;
    newUser->next = headUser;
    headUser = newUser;
    cout << "Registrasi berhasil! Anda dapat login sekarang." << endl;
    mainMenu(); 
}

// Fungsi untuk login sebagai user
bool loginUser() {
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    User* current = headUser;
    while (current != nullptr) {
        if (current->username == username && current->password == password) {
            cout << "Login berhasil!" << endl;
            return true;
        }
        current = current->next;
    }
    cout << "Username atau password salah!" << endl;
    return false;
}

// Fungsi untuk login sebagai admin
bool loginAdmin() {
    string username, password;
    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admin: ";
    cin >> password;

    if (username == admin.username && password == admin.password) {
        cout << "Login sebagai admin berhasil!" << endl;
        return true;
    } else {
        cout << "Username atau password admin salah!" << endl;
        return false;
    }
}

// Fungsi untuk menampilkan semua produk
void displayAllProducts(bool filterAvailability = false) {
    if (headProduct == nullptr) {
        cout << "Tidak ada produk tersedia." << endl;
        return;
    }

    Product* current = headProduct;
    while (current != nullptr) {
        if (filterAvailability && !current->isAvailable) {
            current = current->next;
            continue;
        }
        displayProduct(current);
        current = current->next;
    }
}

// Fungsi untuk menambah produk ke dalam linked list
void addProduct() {
    Product* newProduct = new Product;

    cout << "Masukkan Nama Produk: ";
    cin.ignore();
    getline(cin, newProduct->productName);

    cout << "Masukkan Merek: ";
    getline(cin, newProduct->brand);

    cout << "Masukkan Deskripsi Produk: ";
    getline(cin, newProduct->description);

    cout << "Masukkan Harga: ";
    cin >> newProduct->price;

    cout << "Masukkan Stok: ";
    cin >> newProduct->stock;

    cout << "Masukkan Kategori: ";
    cin.ignore();
    getline(cin, newProduct->category);

    newProduct->isAvailable = newProduct->stock > 0;
    newProduct->next = nullptr;

    // Menambah produk ke awal linked list
    if (headProduct == nullptr) {
        headProduct = newProduct;
    } else {
        newProduct->next = headProduct;
        headProduct = newProduct;
    }

    // Menambahkan produk ke stack untuk riwayat produk terbaru
    pushStack(newProduct->productName);

    cout << "Produk berhasil ditambahkan!" << endl;
}

// Fungsi untuk mengupdate produk
void updateProduct() {
    string productName;
    cout << "Masukkan Nama Produk yang ingin diupdate: ";
    cin.ignore();
    getline(cin, productName);

    bool found = false;
    Product* current = headProduct;

    while (current != nullptr) {
        if (current->productName == productName) {
            found = true;
            cout << "Produk ditemukan, silakan update informasi:" << endl;

            cout << "Masukkan Nama Produk Baru (kosongkan jika tidak ingin diubah): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) current->productName = newName;

            cout << "Masukkan Merek Baru (kosongkan jika tidak ingin diubah): ";
            string newBrand;
            getline(cin, newBrand);
            if (!newBrand.empty()) current->brand = newBrand;

            cout << "Masukkan Deskripsi Baru (kosongkan jika tidak ingin diubah): ";
            string newDesc;
            getline(cin, newDesc);
            if (!newDesc.empty()) current->description = newDesc;

            cout << "Masukkan Harga Baru (kosongkan jika tidak ingin diubah): ";
            double newPrice;
            string priceInput;
            getline(cin, priceInput);
            if (!priceInput.empty()) {
                newPrice = stod(priceInput);
                current->price = newPrice;
            }

            cout << "Masukkan Stok Baru (kosongkan jika tidak ingin diubah): ";
            string stockInput;
            getline(cin, stockInput);
            if (!stockInput.empty()) {
                int newStock = stoi(stockInput);
                current->stock = newStock;
                current->isAvailable = newStock > 0;
            }

            cout << "Masukkan Kategori Baru (kosongkan jika tidak ingin diubah): ";
            string newCategory;
            getline(cin, newCategory);
            if (!newCategory.empty()) current->category = newCategory;

            cout << "Produk berhasil diupdate!" << endl;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Produk tidak ditemukan!" << endl;
    }
}

// Fungsi untuk menghapus produk
void deleteProduct() {
    string productName;
    cout << "Masukkan Nama Produk yang ingin dihapus: ";
    cin.ignore();
    getline(cin, productName);

    if (headProduct == nullptr) {
        cout << "Tidak ada produk yang dapat dihapus." << endl;
        return;
    }

    if (headProduct->productName == productName) {
        Product* temp = headProduct;
        headProduct = headProduct->next;
        delete temp;
        cout << "Produk berhasil dihapus!" << endl;
        return;
    }

    Product* current = headProduct;
    while (current->next != nullptr) {
        if (current->next->productName == productName) {
            Product* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Produk berhasil dihapus!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Produk tidak ditemukan!" << endl;
}

// Function to display the product list
void viewProducts() {
    if (headProduct == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    Product* current = headProduct;
    cout << "Daftar Produk: " << endl;
    while (current != nullptr) {
        cout << "Nama: " << current->productName << ", Harga: Rp. " << fixed << setprecision(2) << current->price
             << ", Stok: " << current->stock << ", Status: " << (current->isAvailable ? "Tersedia" : "Tidak Tersedia") << endl;
        current = current->next;
    }
}

// Fungsi untuk membeli produk
void buyProduct() {
    string productName;
    cout << "Masukkan Nama Produk yang ingin dibeli: ";
    cin.ignore();
    getline(cin, productName);

    bool found = false;
    Product* current = headProduct;
    while (current != nullptr) {
        if (current->productName == productName) {
            if (current->isAvailable && current->stock > 0) {
                int quantity;
                cout << "Masukkan jumlah yang ingin dibeli: ";
                cin >> quantity;

                if (quantity <= current->stock) {
                    current->stock -= quantity;
                    double totalPrice = quantity * current->price;

                    // Menyimpan riwayat pembelian
                    Purchase* newPurchase = new Purchase;
                    newPurchase->productName = current->productName;
                    newPurchase->quantity = quantity;
                    newPurchase->totalPrice = totalPrice;
                    newPurchase->next = nullptr;

                    // Menambah pembelian ke awal linked list
                    if (headPurchase == nullptr) {
                        headPurchase = newPurchase;
                    } else {
                        newPurchase->next = headPurchase;
                        headPurchase = newPurchase;
                    }

                    // Menambah produk ke queue sebagai antrian pembelian
                    enqueueQueue(current->productName);

                    cout << "Pembelian berhasil! Anda membeli " << quantity << " unit " << current->productName << endl;
                    cout << "Total harga: Rp. " << fixed << setprecision(2) << totalPrice << endl;
                } else {
                    cout << "Stok tidak cukup!" << endl;
                }
            } else {
                cout << "Produk tidak tersedia!" << endl;
            }
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Produk tidak ditemukan!" << endl;
    }
}

// Fungsi untuk menampilkan laporan penjualan
void displaySalesReport() {
    cout << "================= Laporan Penjualan ================" << endl;
    if (headPurchase == nullptr) {
        cout << "Belum ada transaksi pembelian." << endl;
    } else {
        double totalRevenue = 0;
        Purchase* current = headPurchase;
        while (current != nullptr) {
            cout << "Produk: " << current->productName << " | Jumlah: " << current->quantity
                 << " | Total Harga: Rp. " << fixed << setprecision(2) << current->totalPrice << endl;
            totalRevenue += current->totalPrice;
            current = current->next;
        }
        cout << "Pendapatan Total: Rp. " << fixed << setprecision(2) << totalRevenue << endl;
    }
}
Product* merge(Product* left, Product* right) {
    if (!left) return right;
    if (!right) return left;

    if (left->price < right->price) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Product* mergeSort(Product* head) {
    if (!head || !head->next) return head;

    // Finding the middle of the linked list
    Product* slow = head;
    Product* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Product* left = head;
    Product* right = slow->next;
    slow->next = nullptr;

    // Recursively sort both halves
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the sorted halves
    return merge(left, right);
}

// Quick Sort
Product* partition(Product* low, Product* high) {
    double pivot = high->price;
    Product* i = low;
    Product* j = low;

    while (j != high) {
        if (j->price < pivot) {
            swap(i->price, j->price);
            i = i->next;
        }
        j = j->next;
    }

    swap(i->price, high->price);
    return i;
}

void quickSort(Product* low, Product* high) {
    if (low != nullptr && high != nullptr && low != high && low != high->next) {
        Product* pivot = partition(low, high);
        quickSort(low, pivot);
        quickSort(pivot->next, high);
    }
}

int fibonacciSearch(Product* head, double x) {
    // First, count the number of elements in the linked list
    int n = 0;
    Product* current = head;
    while (current != nullptr) {
        n++;
        current = current->next;
    }

    // Initialize Fibonacci numbers
    int fibM_minus2 = 0;    // (m-2)'th Fibonacci Number
    int fibM_minus1 = 1;    // (m-1)'th Fibonacci Number
    int fibM = fibM_minus2 + fibM_minus1; // m'th Fibonacci Number

    while (fibM < n) {
        fibM = fibM_minus1 + fibM_minus2;
        fibM_minus2 = fibM_minus1;
        fibM_minus1 = fibM;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibM_minus2, n - 1);

        // Traverse the linked list until the correct element is found or moved past it
        Product* temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }

        if (temp->price < x) {
            fibM = fibM_minus1;
            fibM_minus1 = fibM_minus2;
            fibM_minus2 = fibM - fibM_minus1;
            offset = i;
        } else if (temp->price > x) {
            fibM = fibM_minus2;
            fibM_minus2 = fibM_minus1 - fibM_minus2;
            fibM_minus1 = fibM - fibM_minus2;
        } else {
            cout << "Produk ditemukan: " << temp->productName << endl;
            return i;
        }
    }

    // Check the last element if we are at the end of the search range
    if (fibM_minus1 && offset + 1 < n) {
        Product* temp = head;
        for (int i = 0; i < offset + 1; i++) {
            temp = temp->next;
        }
        if (temp->price == x) {
            cout << "Produk ditemukan: " << temp->productName << endl;
            return offset + 1;
        }
    }

    cout << "Produk tidak ditemukan!" << endl;
    return -1;
}

int boyerMooreSearch(Product* head, const string& pattern) {
    // Create a list from the linked list of product names
    Product* current = head;
    vector<string> productNames;  // Corrected: Declare vector of strings

    while (current != nullptr) {
        productNames.push_back(current->productName);
        current = current->next;
    }

    int m = pattern.length();
    int n = productNames.size();
    int badChar[256]; // Array for Bad Character Heuristic

    // Preprocess the pattern to fill the bad character array
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        badChar[(int)pattern[i]] = i;
    }

    int s = 0;  // Shift of the pattern with respect to text
    while (s <= n - 1) {  // while s is within the bounds of the productNames
        int j = m - 1;

        // Compare the pattern with the current product name
        while (j >= 0 && pattern[j] == productNames[s][j]) {
            j--;
        }

        if (j < 0) { // Pattern found
            cout << "Produk ditemukan: " << productNames[s] << endl;
            return s;
            // Shift pattern by m or the bad character heuristic
            s += (s + m < n) ? m - badChar[productNames[s + m][0]] : 1;
        } else {
            // Apply Bad Character Heuristic
            s += max(1, j - badChar[productNames[s][j]]);  // Use std::max
        }
    }

    cout << "Produk tidak ditemukan!" << endl;
    return -1;
}

void jumpSearchByCategory(Product* headProduct, const string& targetCategory) {
    if (headProduct == nullptr) {
        cout << "Daftar produk kosong!" << endl;
        return;
    }

// Menghitung panjang linked list
    Product* current = headProduct;
    int length = 0;
    
    while (current != nullptr) {
        length++;
        current = current->next;
    }

    // Menghitung ukuran langkah (step) untuk Jump Search
    int step = sqrt(length);
    int prev = 0;
    current = headProduct;

    // Melakukan lompatan berdasarkan kategori produk
    while (current != nullptr && current->category < targetCategory) {
        prev = step;
        // Melompat ke depan sebanyak step
        for (int i = 0; i < step && current != nullptr; ++i) {
            current = current->next;
        }
        if (current == nullptr || current->category > targetCategory) {
            break;
        }
    }

    // Jika kategori ditemukan, lakukan pencarian linier di dalam blok
    while (current != nullptr && current->category <= targetCategory) {
        if (current->category == targetCategory) {
            cout << "Produk ditemukan dengan kategori: " << current->category << endl;
            cout << "Nama Produk: " << current->productName << endl;
            cout << "Merek: " << current->brand << ", Harga: Rp. " << current->price << endl;
            cout << "Stok: " << current->stock << ", Deskripsi: " << current->description << endl;
            return;
        }
        current = current->next;
    }

    // Jika kategori tidak ditemukan
    cout << "Produk dengan kategori '" << targetCategory << "' tidak ditemukan!" << endl;
}


// Forward declarations of functions
void mainMenu();  // Forward declaration of mainMenu()
void MenuAdmin();  // Forward declaration of MenuAdmin()

// Function to display the admin menu
void MenuAdmin() {
    int pilihan;
    bool kembaliKeMenuUtama = false;

    do {
        cout << "================= Menu Admin ==================" << endl;
        cout << "| 1. Tambah Produk                          |" << endl;
        cout << "| 2. Hapus Produk                           |" << endl;
        cout << "| 3. Update Produk                          |" << endl;
        cout << "| 4. Tampilkan Semua Produk                 |" << endl;
        cout << "| 5. Tampilkan Semua Produk (Tersedia)      |" << endl;
        cout << "| 6. Laporan Penjualan                      |" << endl;
        cout << "| 7. Urutkan Produk Berdasarkan Harga       |" << endl;
        cout << "| 8. Pencarian Produk                       |" << endl;  // Menambahkan pilihan pencarian
        cout << "| 9. Kembali ke Menu Utama                  |" << endl;
        cout << "=============================================" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                addProduct();
                break;
            case 2:
                deleteProduct();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                displayAllProducts();
                break;
            case 5:
                displayAllProducts(true);
                break;
            case 6:
                displaySalesReport();
                break;
            case 7:
                // Pilih untuk pengurutan Merge Sort atau Quick Sort
                cout << "Pilih metode pengurutan:" << endl;
                cout << "1. Merge Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "Masukkan pilihan (1/2): ";
                int sortChoice;
                cin >> sortChoice;
                if (sortChoice == 1) {
                    // Assuming headProduct is a global or passed as a parameter
                    headProduct = mergeSort(headProduct);
                    cout << "Produk berhasil diurutkan menggunakan Merge Sort." << endl;
                } else if (sortChoice == 2) {
                    quickSort(headProduct, nullptr);
                    cout << "Produk berhasil diurutkan menggunakan Quick Sort." << endl;
                }
                break;
            case 8:
                // Pencarian produk
                cout << "Pilih metode pencarian:" << endl;
                cout << "1. Fibonacci Search (Harga)" << endl;
                cout << "2. Boyer-Moore Search (Nama)" << endl;
                cout << "3. Jump Search (Kategori) " << endl;
                int searchChoice;
                cin >> searchChoice;
                if (searchChoice == 1) {
                    double price;
                    cout << "Masukkan harga produk yang dicari: ";
                    cin >> price;
                    fibonacciSearch(headProduct, price);
                } else if (searchChoice == 2) {
                    string name;
                    cout << "Masukkan nama produk yang dicari: ";
                    cin.ignore();  // To ignore any remaining newline characters
                    getline(cin, name);
                    boyerMooreSearch(headProduct, name);
                } else if (searchChoice == 3) {
                    string category;
                    cout << "Masukan kategori produk yang ingin dicari: ";
                    cin.ignore();
                    getline (cin, category);
                    jumpSearchByCategory(headProduct, category);
                }
                break;
            case 9:
                // If 9 is selected, exit the loop and go back to the main menu
                kembaliKeMenuUtama = true;  // Set the flag to true to exit the loop
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
                break;
        }

    } while (!kembaliKeMenuUtama);  // Keep asking for input until option 9 is selected

    // Call mainMenu() when user selects option 9
    mainMenu();  // Go back to the main menu
}

void userMenu() {
    int choice;
    do {
        cout << "====== Menu User ======" << endl;
        cout << "|   1. Lihat Produk   |" << endl;
        cout << "|   2. Beli Produk    |" << endl;
        cout << "|   3. Keluar         |" << endl;
        cout << "=======================" << endl;
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewProducts();
                break;
            case 2:
                buyProduct();
                break;
            case 3:
                cout << "Terima kasih! Sampai jumpa." << endl;
                mainMenu();
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 3);
}


// Main menu function
void mainMenu() {
    int loginChoice;
    cout << "----------------------------------------------" << endl;
    cout << "|Selamat datang di Manajemen Toko Optik Mata!|" << endl;
    cout << "----------------------------------------------" << endl;

    cout << "====== Pilih role Login sebagai: ======" << endl;
    cout << "|       1. User                       |" << endl;
    cout << "|       2. Admin                      |" << endl;
    cout << "|       3. Registrasi sebagai User    |" << endl;
    cout << "|       4. Keluar                     |" << endl;
    cout << "=======================================" << endl;
    cout << "Masukkan pilihan : ";
    cin >> loginChoice;

    switch (loginChoice) {
        case 1:
            if (loginUser()) {
                // User sudah login, lanjutkan ke fungsi beli produk
                userMenu();
            }
            break;
        case 2:
             if (loginAdmin()) {
                // Admin sudah login, tampilkan menu admin
                MenuAdmin();
            }
            break;
        case 3:
            registerUser();
            break;
        case 4:
            return;  
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
    }
}

// Main entry point of the program
int main() {
    mainMenu();  // Start the main menu
    return 0;  // Program ends when mainMenu() completes
}
 