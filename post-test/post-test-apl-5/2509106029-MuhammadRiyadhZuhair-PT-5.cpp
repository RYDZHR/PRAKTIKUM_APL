#include <iostream>
#include <iomanip>

using namespace std;

struct update{
    string userbaru;
    bool req = false;
};

struct akun {
    string username;
    string password;
    string email;
    string role;
    int id;
    bool acc;
    bool deleteReq;
    update reqUp;

};

// Database

akun db[50];
int totalakun = 0;
int urutID = 2;

void tampilan(akun database[], int jumlah);
void tampilan(akun a);

int cari(akun database[], int jumlah, int id);
int cari(akun database[], int jumlah, string username);

void accAkun(akun database[], int jumlah, int targetID);
void uptProcess(akun database[], int jumlah);

void delAkun(akun database[], int *jumlah, int targetID);

void profil(akun database[], int idx);

void gantiUsername(akun *akunAktif);
void reqdelAkun(akun database[], int idx);

void menuAdmin(akun database[], int &jumlah);
void menuUser(akun database[], int idx);

int regis(akun database[], int *jumlah, int *idbaru);
int login(akun database[], int jumlah, int percobaan);



void tampilan(akun database[], int jumlah){
    if (jumlah == 0){
        cout << "Tak ade akun";
        return;
    }

        cout << "\n" << setfill('=') << setw(62) << "=" << "\n";
    cout << setfill(' ')
         << "| " << setw(5)  << "ID"
         << " | " << setw(16) << "Username"
         << " | " << setw(10) << "Status"
         << " | " << setw(10) << "Delete?"
         << " |\n";
    cout << setfill('-') << setw(62) << "-" << "\n";
    for (int i = 0; i < jumlah; i++) {
        cout << setfill(' ')
             << "| " << setw(5)  << database[i].id
             << " | " << setw(16) << database[i].username
             << " | " << setw(10) << (database[i].acc ? "Aktif" : "PENDING")
             << " | " << setw(10) << (database[i].deleteReq ? "YA" : "TIDAK")
             << " |\n";
    }
    cout << setfill('=') << setw(62) << "=" << "\n";
}

void tampilan(akun a){
    cout << "\n+-------- Profil --------+\n";
    cout << " ID        : " << a.id     << "\n";
    cout << " Username  : " << a.username     << "\n";
    cout << " Email     : " << a.email     << "\n";
    cout << " Role      : " << a.role     << "\n";
    cout << " Stat      : " << (a.acc ? "Aktif" : "menunggu")     << "\n";
    cout << "+--------------------------+\n";
}

int cari(akun database[], int jumlah, int id){
    for (int i = 0; i < jumlah; i++)
        if (database[i].id == id) return i;
    return -1;
    
    
}

int cari(akun database[], int jumlah, string username){
    for (int i = 0; i < jumlah; i++)
        if(database[i].username == username) return i;
    return -1;
}

void sortusername(akun database[], int jumlah){
    for (int i = 0; i < jumlah - 1; i++){
        for (int j = 0; i < jumlah - 1; i++) {
            if (database[j].username > database[j + 1].username){
                akun temp = database[j];
                database = &database[j + 1];
                database[j + 1] = temp;
            }
        }
    }
}

void sordID(akun database[], int jumlah){
    for (int i = 0; i < jumlah -1; i++){
        int maxIDX = i;
        for (int j = i + 1; i < jumlah ; j++){
            maxIDX = j;
        }
        akun temp = database[maxIDX];
        database[maxIDX] = database[i];
        database[i] = temp;
    }
}

void sortStatus(akun database[], int jumlah){
    for (int i = 1 ; i < jumlah; i++){
        akun key = database[i];
        int j = i - 1;

        while (j >= 0 && database[j].acc > key.acc){
            database[j + 1] = database[j];
            j--;
        }
        database[j + 1] = key;
    }

}


//Admin

void accAkun(akun database[], int jumlah, int targetID){
    int idx = cari(database, jumlah, targetID);
    if(idx == -1){
        cout << "id tidak ketemu\n";
        return;
    }
    database[idx].acc = true;
    cout <<  " Akun " << database[idx].username << "sudah aktif :)\n";
}

void uptProcess(akun database[], int jumlah){
    bool ada = false;
    for (int i = 0; i < jumlah; i++){
        if (!database[i].reqUp.req) continue;
        ada = true;
        cout << " Request: " << database[i].username
            << " -> " << database[i].reqUp.userbaru << "\n";
        
            cout << "Setuju? (y/n): ";
            char choice;
            cin >> choice;

            if (choice == 'y'){
                database[i].username = database[i].reqUp.userbaru;
                database[i].reqUp.req = false;
                cout << "Halo " << database[i].username;
            }else{
                database[i].reqUp.req = false;
                cout << " Tidak ACC >:( ";
            }
    }
    if (!ada) cout << " Tak ada apa-apa. Santai ;)";

}

void delAkun(akun database[], int *jumlah, int targetID){
    int idx = cari(database, *jumlah, targetID);
    if (idx == -1){
        cout << " id gak ada di sistem ";
        return;
    }
    string nama = database[idx].username;
    for (int j = idx; j < *jumlah - 1; j++)
        database[j] = database[j + 1];
    (*jumlah)--;
    cout << " Sayonara, " << nama << " :( \n";
}

void menuAdmin(akun database[], int &jumlah){
    string command;
    cout << "ketik 'help' untuk munculin list command.\n";
    while (true){
        cout << "admin@root:/# ";
        cin >> command;

        if(command == "ls"){
            tampilan(database, jumlah);
        } else if(command == "acc"){
            int id;
            cout << "ID: "; cin >> id;
            accAkun(database, jumlah, id);
        } else if(command == "update"){
            uptProcess(database, jumlah);
        } else if(command == "delete"){
            int id;
            cout << "ID: ";
            cin >> id;
            delAkun(database, &jumlah, id);
        } else if(command == "exit"){
            return;
        } else if(command == "help"){
            cout << "ls           -melihat list akun\n";
            cout << "acc          -Melakukan Approve untuk akun baru\n";
            cout << "update       -Update username user\n";
            cout << "delete       -menghapus akun user\n";
            cout << "exit         -keluar dari program\n";
            cout << "sort         -Urutkan list\n";
        } else if(command == "sort"){
            cout << "1. Username A-Z\n";
            cout << "2. ID (Descending)\n";
            cout << "3. Pending list\n";
            cout << ": ";
            int pil;
            cin >> pil;
            
            if (pil == 1){
                sortusername(database, jumlah);
            } else if (pil == 2){
                sordID(database, jumlah);
            } else if(pil == 3){
                sortStatus(database, jumlah);
            } else{
                cout << "Pilihan tidak valid";
            }
        }

    }
}

// user

void profil(akun database[], int idx){
    tampilan(database[idx]);
}

void gantiUsername(akun *akunAktif){
    cout << "username baru: ";
    cin >> akunAktif->reqUp.userbaru;
    akunAktif -> reqUp.req = true;

    cout << "Tunggu Di aceceh Admin.\n";

}

void reqdelAkun(akun database[], int idx){
    database[idx].deleteReq = true;
    cout << "Tunggu acc admin. da da ;( \n";

}

void menuUser(akun database[], int idx){
        int pilihan;
    while (true) {
        cout << "\n==== Selamat datang, " << database[idx].username << " ====\n";
        if (!database[idx].acc)
            cout << "  [!] Akun Anda masih menunggu ACC admin.\n";
        cout << "  1. Lihat Profil\n"
             << "  2. Request Ganti Username\n"
             << "  3. Request Hapus Akun\n"
             << "  4. Logout\n"
             << "  Pilih: ";
        cin >> pilihan;
 
        if      (pilihan == 1) profil (database, idx);
        else if (pilihan == 2) gantiUsername(&database[idx]);  // &database[idx] = ambil alamat elemen
        else if (pilihan == 3) reqdelAkun(database, idx);
        else if (pilihan == 4) { cout << "  Sampai jumpa!\n"; return; }
        else                   cout << "  Pilihan tidak valid.\n";
    }
}

int regis(akun database[], int *jumlah, int *idbaru) {
    if (*jumlah >= 100) return 0;
 
    int i = *jumlah;
    database[i].id     = (*idbaru)++;   // dereference idBaru lalu increment
    database[i].role   = "user";
    database[i].acc    = false;
    database[i].deleteReq = false;
    database[i].reqUp.req = false;
 
    cout << "\n--- Registrasi Akun Baru ---\n";
    cout << "  Username : "; cin >> database[i].username;
    cout << "  Password : "; cin >> database[i].password;
    cout << "  Email    : "; cin >> database[i].email;
 
    (*jumlah)++;   // modifikasi nilai asli lewat pointer
    return database[i].id;
}


int login(akun database[], int jumlah, int percobaan) {
    if (percobaan <= 0) {
        cout << "\n  [!!!] Terlalu banyak percobaan. Akses ditolak!\n";
        return -1;
    }
 
    string user, pass;
    cout << "\n  [Sisa percobaan: " << percobaan<< "]\n";
    cout << "  Username : "; cin >> user;
    cout << "  Password : "; cin >> pass;
 
    int idx = cari(database, jumlah, user);
    if (idx != -1 && database[idx].password == pass) {
        cout << "  [OK] Login berhasil!\n";
        return idx;
    }
 
    cout << "  [X] Username atau password salah.\n";
    return login(database, jumlah, percobaan - 1);
}

int main() {
 
    db[totalakun++] = {"riyadh", "029", "admin@max.com", "admin", 1, true, false};
 
    while (true) {
        int opsi;
        cout << "  1. Login\n  2. Register\n  3. Keluar\n";
        cout << "  Pilihan: "; cin >> opsi;
 
        if (opsi == 1) {
            int status = login(db, totalakun, 3);
            if (status == -1) return 0;
            if (db[status].role == "admin")
                menuAdmin(db, totalakun);      // jumlahAkun dikirim sebagai referensi (&)
            else
                menuUser(db, status);
        }
        else if (opsi == 2) {
            // &jumlahAkun dan &urutId → Address-of Operator, kirim alamat ke fungsi pointer
            int id = regis(db, &totalakun, &urutID);
            if (id != 0) cout << "\n  [OK] Registrasi berhasil! ID Anda: " << id << "\n";
            else         cout << "\n  [!] Database penuh.\n";
        }
        else if (opsi == 3) {
            cout << "\n  Keluar. Sampai jumpa!\n";
            break;
        }
        else {
            cout << "\n  Pilihan tidak valid.\n";
        }
    }
    return 0;
}
 