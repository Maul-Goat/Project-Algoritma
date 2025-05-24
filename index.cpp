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

    simpanKeFile();
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

// Sort musik title bubble Sort
void urutJudul() {
    if (head == NULL || head->next == NULL) return;
    
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        
        while (current != NULL && current->next != NULL) {
            // Bandingkan judul current dengan next
            int i = 0;
            bool shouldSwap = false;
            
            while (current->data.title[i] != '\0' && current->next->data.title[i] != '\0') {
                if (current->data.title[i] > current->next->data.title[i]) {
                    shouldSwap = true;
                    break;
                } else if (current->data.title[i] < current->next->data.title[i]) {
                    break;
                }
                i++;
            }
            
            // Jika current lebih panjang dari next, swap
            if (!shouldSwap && current->data.title[i] != '\0' && current->next->data.title[i] == '\0') {
                shouldSwap = true;
            }
            
            if (shouldSwap) {
                // Swap data
                Music temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            
            current = current->next;
        }
    } while (swapped);
    
    simpanKeFile(); 
}

// Sort musik rating selection Sort 
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
    simpanKeFile();
}

// Sort musik rating
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
    simpanKeFile(); 
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
        
        switch (option) {
            case 1:
            case 2: {
                cin.ignore();
                char keyword[30];
                cout << "Masukkan keyword pencarian: ";
                cin.getline(keyword, 30);
                
                bool found = false;
                cout << "\nHasil pencarian:\n";
                
                Node* current = head;
                while (current != NULL) {
                    bool match = false;
                    int i = 0;
                    bool isEqual = true;
                    
                    switch (option) {
                        case 1:
                            // Cari berdasarkan judul
                            while (keyword[i] != '\0' && current->data.title[i] != '\0') {
                                if (keyword[i] != current->data.title[i]) {
                                    isEqual = false;
                                    break;
                                }
                                i++;
                            }
                            if (isEqual && keyword[i] == '\0' && current->data.title[i] == '\0') {
                                match = true;
                            }
                            break;
                        case 2:
                            // Cari berdasarkan artis
                            while (keyword[i] != '\0' && current->data.artist[i] != '\0') {
                                if (keyword[i] != current->data.artist[i]) {
                                    isEqual = false;
                                    break;
                                }
                                i++;
                            }
                            if (isEqual && keyword[i] == '\0' && current->data.artist[i] == '\0') {
                                match = true;
                            }
                            break;
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
                break;
            }
            case 3:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "❗ Pilihan tidak valid, coba lagi!\n";
        }
        
    } while (option != 3);
}

// delete musik
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
        
        switch (mode) {
            case 1: {
                char deleteTitle[30];
                cin.ignore();
                cout << "Masukkan judul lagu yang ingin dihapus: ";
                cin.getline(deleteTitle, 30);
                
                bool found = false;
                
                // Check head node
                if (head != NULL) {
                    int i = 0;
                    bool isEqual = true;
                    while (deleteTitle[i] != '\0' && head->data.title[i] != '\0') {
                        if (deleteTitle[i] != head->data.title[i]) {
                            isEqual = false;
                            break;
                        }
                        i++;
                    }
                    if (isEqual && deleteTitle[i] == '\0' && head->data.title[i] == '\0') {
                        Node* temp = head;
                        head = head->next;
                        delete temp;
                        found = true;
                    }
                }
                
                // Check other nodes
                if (!found) {
                    Node* current = head;
                    while (current != NULL && current->next != NULL) {
                        int i = 0;
                        bool isEqual = true;
                        while (deleteTitle[i] != '\0' && current->next->data.title[i] != '\0') {
                            if (deleteTitle[i] != current->next->data.title[i]) {
                                isEqual = false;
                                break;
                            }
                            i++;
                        }
                        if (isEqual && deleteTitle[i] == '\0' && current->next->data.title[i] == '\0') {
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
                    simpanKeFile(); 
                    cout << "Lagu berhasil dihapus.\n";
                } else {
                    cout << "Lagu tidak ditemukan.\n";
                }
                break;
            }
            case 2:
                while (head != NULL) {
                    Node* temp = head;
                    head = head->next;
                    delete temp;
                }
                simpanKeFile(); // Simpan perubahan
                cout << "Semua lagu telah dihapus.\n";
                break;
            case 3:
                cout << "Kembali ke menu utama...\n";
                break;
            default:
                cout << "❗ Pilihan tidak valid, coba lagi!\n";
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
        // Bandingkan string dengan loop
        int i = 0;
        bool isEqual = true;
        while (searchTitle[i] != '\0' && current->data.title[i] != '\0') {
            if (searchTitle[i] != current->data.title[i]) {
                isEqual = false;
                break;
            }
            i++;
        }
        if (isEqual && searchTitle[i] == '\0' && current->data.title[i] == '\0') {
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
        simpanKeFile(); 
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
    
    // bersihkan link list
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
