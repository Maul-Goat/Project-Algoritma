#include <iostream>
#include <cstdio>
using namespace std;

struct Music {
    char title[30];
    char album[30];
    char artist[30];
    char genre[20];
    float rating;
};

struct Node {
    Music data;
    Node* next;
};

Node* head = NULL;

// String utility functions
bool isEqual(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == '\0' && b[i] == '\0';
}

int compareString(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    if (a[i] == '\0') return -1;
    return 1;
}

void simpanKeFile() {
    FILE* file = fopen("musik.dat", "wb");
    if (file == NULL) {
        cout << "Gagal membuka file untuk penyimpanan.\n";
        return;
    }

    Node* current = head;
    while (current != NULL) {
        fwrite(&(current->data), sizeof(Music), 1, file);
        current = current->next;
    }

    fclose(file);
}

void bacaDariFile() {
    FILE* file = fopen("musik.dat", "rb");
    if (file == NULL) {
        return;
    }

    Music m;
    while (fread(&m, sizeof(Music), 1, file) == 1) {
        Node* newNode = new Node;
        newNode->data = m;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            Node* last = head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    fclose(file);
}

void tambahLagu() {
    Music m;
    int jumlah;
    cout << "Ingin menambahkan berapa lagu? ";
    cin >> jumlah;
    cin.ignore();

    for (int i = 0; i < jumlah; i++) {
        cout << "\nLagu ke-" << i + 1 << endl;
        cout << "Judul: "; cin.getline(m.title, 30);
        cout << "Album: "; cin.getline(m.album, 30);
        cout << "Artis: "; cin.getline(m.artist, 30);
        cout << "Genre: "; cin.getline(m.genre, 20);
        cout << "Rating (0.0 - 5.0): "; cin >> m.rating;
        cin.ignore();

        Node* newNode = new Node;
        newNode->data = m;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            Node* last = head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newNode;
        }
    }

    simpanKeFile(); // Simpan perubahan 
    cout << jumlah << " lagu berhasil ditambahkan!\n";
}

void tampilkanLagu() {
    if (head == NULL) {
        cout << "\nDaftar lagu kosong!\n";
        return;
    }
    
    cout << "\nDaftar Semua Lagu:\n";
    Node* current = head;
    int count = 1;
    
    while (current != NULL) {
        cout << "No: " << count++ << endl;
        cout << "Judul: " << current->data.title
             << "\nAlbum: " << current->data.album
             << "\nArtis: " << current->data.artist
             << "\nGenre: " << current->data.genre
             << "\nRating: " << current->data.rating << "\n\n";
        current = current->next;
    }
}

// Sort music title Insertion Sort
void urutJudul() {
    if (head == NULL || head->next == NULL) return;
    
    Node* sorted = NULL;
    Node* current = head;
    
    while (current != NULL) {
        Node* next = current->next;
        
        if (sorted == NULL || compareString(current->data.title, sorted->data.title) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && compareString(current->data.title, temp->next->data.title) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        
        current = next;
    }
    
    head = sorted;
    simpanKeFile(); // Simpan perubahan
}

// Sort music rating  Selection Sort 
void urutRatingTertinggi() {
    if (head == NULL || head->next == NULL) return;
    
    Node* i = head;
    
    while (i != NULL) {
        Node* min = i;
        Node* j = i->next;
        
        while (j != NULL) {
            if (j->data.rating > min->data.rating) {
                min = j;
            }
            j = j->next;
        }
        
        if (min != i) {
            // Swap data instead of nodes
            Music temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
        
        i = i->next;
    }
    simpanKeFile(); // Simpan perubahan 
}

// Sort music rating
void urutRatingTerendah() {
    if (head == NULL || head->next == NULL) return;
    
    Node* i = head;
    
    while (i != NULL) {
        Node* min = i;
        Node* j = i->next;
        
        while (j != NULL) {
            if (j->data.rating < min->data.rating) {
                min = j;
            }
            j = j->next;
        }
        
        if (min != i) {
            // Swap data instead of nodes
            Music temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
        
        i = i->next;
    }
    simpanKeFile(); // Simpan perubahan
}

// sorting options
void urutkanLagu() {
    int option;
    
    do {
        cout << "\n==== URUTKAN LAGU ====\n";
        cout << "1. Urutkan berdasarkan Judul (A-Z)\n";
        cout << "2. Urutkan berdasarkan Rating (Tertinggi)\n";
        cout << "3. Urutkan berdasarkan Rating (Terendah)\n";
        cout << "4. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> option;
        
        switch (option) {
            case 1:
                urutJudul();
                cout << "Lagu berhasil diurutkan berdasarkan judul!\n";
                tampilkanLagu();
                break;
            case 2:
                urutRatingTertinggi();
                cout << "Lagu berhasil diurutkan berdasarkan rating tertinggi!\n";
                tampilkanLagu();
                break;
            case 3:
                urutRatingTerendah();
                cout << "Lagu berhasil diurutkan berdasarkan rating terendah!\n";
                tampilkanLagu();
                break;
            case 4:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "❗ Pilihan tidak valid, coba lagi!\n";
        }
    } while (option != 4);
}

// search for music
void cariLagu() {
    if (head == NULL) {
        cout << "\nDaftar lagu kosong!\n";
        return;
    }
    
    int option;
    do {
        cout << "\n==== CARI LAGU ====\n";
        cout << "1. Cari berdasarkan Judul\n";
        cout << "2. Cari berdasarkan Artis\n";
        cout << "3. Kembali ke menu utama\n";
        cout << "Pilihan: ";
        cin >> option;
        
        if (option == 3) {
            cout << "Kembali ke menu utama...\n";
            break;
        }
        
        cin.ignore();
        
        char keyword[30];
        cout << "Masukkan keyword pencarian: ";
        cin.getline(keyword, 30);
        
        bool found = false;
        cout << "\nHasil pencarian:\n";
        
        Node* current = head;
        while (current != NULL) {
            bool match = false;
            
            switch (option) {
                case 1: match = isEqual(current->data.title, keyword); break;
                case 2: match = isEqual(current->data.artist, keyword); break;
            }
            
            if (match) {
                found = true;
                cout << "Judul: " << current->data.title
                     << "\nAlbum: " << current->data.album
                     << "\nArtis: " << current->data.artist
                     << "\nGenre: " << current->data.genre
                     << "\nRating: " << current->data.rating << "\n\n";
            }
            
            current = current->next;
        }
        
        if (!found) cout << "Tidak ditemukan.\n";
        
    } while (option != 3);
}

// delete music
void hapusLagu() {
    if (head == NULL) {
        cout << "\nDaftar lagu kosong!\n";
        return;
    }
    
    int mode;
    do {
        cout << "\n==== HAPUS LAGU ====\n";
        cout << "1. Hapus berdasarkan judul\n";
        cout << "2. Hapus semua lagu\n";
        cout << "3. Kembali ke menu utama\n";
        cout << "Pilih mode: ";
        cin >> mode;
        
        if (mode == 3) {
            cout << "Kembali ke menu utama...\n";
            break;
        }
        
        if (mode == 2) {
            while (head != NULL) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
            simpanKeFile(); // Simpan perubahan
            cout << "Semua lagu telah dihapus.\n";
            continue;
        }
        
        char deleteTitle[30];
        cin.ignore();
        cout << "Masukkan judul lagu yang ingin dihapus: ";
        cin.getline(deleteTitle, 30);
        
        bool found = false;
        
        if (head != NULL && isEqual(head->data.title, deleteTitle)) {
            Node* temp = head;
            head = head->next;
            delete temp;
            found = true;
        } else {
            Node* current = head;
            while (current != NULL && current->next != NULL) {
                if (isEqual(current->next->data.title, deleteTitle)) {
                    Node* temp = current->next;
                    current->next = current->next->next;
                    delete temp;
                    found = true;
                    break;
                }
                current = current->next;
            }
        }
        
        if (found) {
            simpanKeFile(); // Simpan perubahan
            cout << "Lagu berhasil dihapus.\n";
        } else {
            cout << "Lagu tidak ditemukan.\n";
        }
        
    } while (mode != 3);
}

// update rating
void updateRating() {
    if (head == NULL) {
        cout << "\nDaftar lagu kosong!\n";
        return;
    }
        
        char searchTitle[30];
        cin.ignore();
        cout << "Masukkan judul lagu yang ingin diperbarui: ";
        cin.getline(searchTitle, 30);
        
        bool found = false;
        Node* current = head;
        
        while (current != NULL) {
            if (isEqual(current->data.title, searchTitle)) {
                cout << "Rating sekarang: " << current->data.rating << "\n";
                cout << "Masukkan rating baru (0.0 - 5.0): ";
                float newRating;
                cin >> newRating;
                current->data.rating = newRating;
                found = true;
                break;
            }
            current = current->next;
        }
        
        if (found) {
            simpanKeFile(); // Simpan perubahan ke file
            cout << "Rating berhasil diperbarui.\n";
        } else {
            cout << "Lagu tidak ditemukan.\n";
        } 
}

void tampilkanMenu() {
    cout << "\n====================================\n";
    cout << "|              SPOTIFY             |\n";
    cout << "====================================\n";
    cout << "| 1.  Tambah Lagu                  |\n";
    cout << "| 2.  Tampilkan Semua Lagu         |\n";
    cout << "| 3.  Urutkan Lagu                 |\n";
    cout << "| 4.  Cari Lagu                    |\n";
    cout << "| 5.  Hapus Lagu                   |\n";
    cout << "| 6.  Update Rating Lagu           |\n";
    cout << "| 7.  Keluar                       |\n";
    cout << "====================================\n";
    cout << "Pilih menu [1-7]: ";
}

int main() {
    bacaDariFile();
    
    int choice;
    do {
        tampilkanMenu();
        cin >> choice;

        switch (choice) {
            case 1: tambahLagu(); break;
            case 2: tampilkanLagu(); break;
            case 3: urutkanLagu(); break;
            case 4: cariLagu(); break;
            case 5: hapusLagu(); break;
            case 6: updateRating(); break;
            case 7: cout << "Terima kasih telah menggunakan aplikasi!\n"; break;
            default: cout << "❗ Pilihan tidak valid, coba lagi!\n";
        }
    } while (choice != 7); 

    simpanKeFile();
    
    // Clean up linked list before exiting
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}