#include <iostream>
#include <iomanip>

using namespace std;

// ===== STRUKTUR DATA =====
struct UpdateRequest {
    string newUser;
    bool   req = false;
};

struct Akun {
    string        username;
    string        password;
    string        email;
    string        role;
    int           id;
    bool          acc;
    bool          delReq;
    UpdateRequest reqUp;
};

// ===== DATABASE GLOBAL =====
Akun db[100];
int  jumlahAkun = 0;
int  urutId     = 1001;

// ============================================================
//  DEKLARASI FORWARD
// ============================================================
void  tampilkan(Akun database[], int jumlah);          
void  tampilkan(Akun a);                               

int   cariAkun (Akun database[], int jumlah, int id);            
int   cariAkun (Akun database[], int jumlah, string username);   

void  accAkun         (Akun database[], int jumlah, int targetId);
void  prosesUpdate    (Akun database[], int jumlah);
void  hapusAkun       (Akun database[], int &jumlah, int targetId);

void  tampilkanProfil (Akun database[], int idx);
void  requestGantiNama(Akun database[], int idx);
void  requestHapusAkun(Akun database[], int idx);

void  adminMenu(Akun database[], int &jumlah);
void  userMenu (Akun database[], int idx);

int   regisSystem(Akun database[], int &jumlah, int &idBaru);
int   loginSystem(Akun database[], int jumlah, int sisaCoba); 


// ============================================================
//  OVERLOADING — tampilkan
// ============================================================


void tampilkan(Akun database[], int jumlah) {
    if (jumlah == 0) {
        cout << "  (tidak ada akun)\n";
        return;
    }
    cout << "\n" << setfill('=') << setw(62) << "=" << "\n";
    cout << setfill(' ')
         << "| " << setw(5)  << "ID"
         << " | " << setw(16) << "Username"
         << " | " << setw(10) << "Status"
         << " | " << setw(10) << "Del Req"
         << " |\n";
    cout << setfill('-') << setw(62) << "-" << "\n";
    for (int i = 0; i < jumlah; i++) {
        cout << setfill(' ')
             << "| " << setw(5)  << database[i].id
             << " | " << setw(16) << database[i].username
             << " | " << setw(10) << (database[i].acc ? "Aktif" : "PENDING")
             << " | " << setw(10) << (database[i].delReq ? "YA" : "TIDAK")
             << " |\n";
    }
    cout << setfill('=') << setw(62) << "=" << "\n";
}


void tampilkan(Akun a) {
    cout << "\n+------ PROFIL AKUN ------+\n";
    cout << "  ID       : " << a.id       << "\n";
    cout << "  Username : " << a.username << "\n";
    cout << "  Email    : " << a.email    << "\n";
    cout << "  Role     : " << a.role     << "\n";
    cout << "  Status   : " << (a.acc ? "Aktif" : "Menunggu ACC") << "\n";
    cout << "+-------------------------+\n";
}



int cariAkun(Akun database[], int jumlah, int id) {
    for (int i = 0; i < jumlah; i++)
        if (database[i].id == id) return i;
    return -1;
}

int cariAkun(Akun database[], int jumlah, string username) {
    for (int i = 0; i < jumlah; i++)
        if (database[i].username == username) return i;
    return -1;
}


// ============================================================
//  SUB-PROGRAM FITUR ADMIN
// ============================================================


void accAkun(Akun database[], int jumlah, int targetId) {
    int idx = cariAkun(database, jumlah, targetId);
    if (idx == -1) {
        cout << "  [!] ID tidak ditemukan.\n";
        return;
    }
    database[idx].acc = true;
    cout << "  [OK] Akun '" << database[idx].username << "' berhasil diaktifkan!\n";
}


void prosesUpdate(Akun database[], int jumlah) {
    bool ada = false;
    for (int i = 0; i < jumlah; i++) {
        if (!database[i].reqUp.req) continue;
        ada = true;
        cout << "  Request: '" << database[i].username
             << "' -> '" << database[i].reqUp.newUser << "'\n";
        cout << "  Setuju? (y/n): ";
        char pilih; cin >> pilih;
        if (pilih == 'y') {
            database[i].username  = database[i].reqUp.newUser;
            database[i].reqUp.req = false;
            cout << "  [OK] Username diperbarui.\n";
        } else {
            database[i].reqUp.req = false;
            cout << "  [X] Request ditolak.\n";
        }
    }
    if (!ada) cout << "  Tidak ada request pending.\n";
}

void hapusAkun(Akun database[], int &jumlah, int targetId) {
    int idx = cariAkun(database, jumlah, targetId);
    if (idx == -1) {
        cout << "  [!] ID tidak ditemukan.\n";
        return;
    }
    string nama = database[idx].username;
    for (int j = idx; j < jumlah - 1; j++)
        database[j] = database[j + 1];
    jumlah--;
    cout << "  [OK] Akun '" << nama << "' berhasil dihapus.\n";
}

void adminMenu(Akun database[], int &jumlah) {
    string cmd;
    cout << "\n[CONSOLE ADMIN] Ketik 'help' untuk daftar perintah.\n";
    while (true) {
        cout << "admin@root:~# "; cin >> cmd;

        if      (cmd == "ls")     { tampilkan(database, jumlah); }
        else if (cmd == "acc")    { int id; cout << "ID target: "; cin >> id;
                                    accAkun(database, jumlah, id); }
        else if (cmd == "up_acc") { prosesUpdate(database, jumlah); }
        else if (cmd == "delete") { int id; cout << "ID target: "; cin >> id;
                                    hapusAkun(database, jumlah, id); }
        else if (cmd == "exit")   { return; }
        else if (cmd == "help")   { cout << "  Perintah: ls | acc | up_acc | delete | exit\n"; }
        else                      { cout << "  Perintah tidak dikenal.\n"; }
    }
}


// ============================================================
//  SUB-PROGRAM FITUR USER
// ============================================================


void tampilkanProfil(Akun database[], int idx) {
    tampilkan(database[idx]);
}


void requestGantiNama(Akun database[], int idx) {
    cout << "  Username baru: "; cin >> database[idx].reqUp.newUser;
    database[idx].reqUp.req = true;
    cout << "  [OK] Request terkirim, tunggu persetujuan admin.\n";
}


void requestHapusAkun(Akun database[], int idx) {
    database[idx].delReq = true;
    cout << "  [OK] Request hapus akun terkirim, tunggu persetujuan admin.\n";
}


void userMenu(Akun database[], int idx) {
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

        if      (pilihan == 1) tampilkanProfil (database, idx);
        else if (pilihan == 2) requestGantiNama(database, idx);
        else if (pilihan == 3) requestHapusAkun(database, idx);
        else if (pilihan == 4) { cout << "  Sampai jumpa!\n"; return; }
        else                   cout << "  Pilihan tidak valid.\n";
    }
}


// ============================================================
//  REGISTRASI
// ============================================================
int regisSystem(Akun database[], int &jumlah, int &idBaru) {
    if (jumlah >= 100) return 0;

    int i = jumlah;
    database[i].id    = idBaru++;
    database[i].role  = "user";
    database[i].acc   = false;
    database[i].delReq = false;
    database[i].reqUp.req = false;

    cout << "\n--- Registrasi Akun Baru ---\n";
    cout << "  Username : "; cin >> database[i].username;
    cout << "  Password : "; cin >> database[i].password;
    cout << "  Email    : "; cin >> database[i].email;

    jumlah++;
    return database[i].id;
}


// ============================================================
//  LOGIN — REKURSIF

int loginSystem(Akun database[], int jumlah, int sisaCoba) {
    // Base case: kehabisan percobaan
    if (sisaCoba <= 0) {
        cout << "\n  [!!!] Terlalu banyak percobaan. Akses ditolak!\n";
        return -1;
    }

    string user, pass;
    cout << "\n  [Sisa percobaan: " << sisaCoba << "]\n";
    cout << "  Username : "; cin >> user;
    cout << "  Password : "; cin >> pass;


    int idx = cariAkun(database, jumlah, user);
    if (idx != -1 && database[idx].password == pass) {
        cout << "  [OK] Login berhasil!\n";
        return idx;
    }

    cout << "  [X] Username atau password salah.\n";

    return loginSystem(database, jumlah, sisaCoba - 1);
}


// ============================================================
//  MAIN
// ============================================================
int main() {

    db[jumlahAkun++] = {"riyadh", "029", "admin@max.com", "admin", 999, true, false};

    while (true) {
        int opsi;
        cout << "\n==============================\n";
        cout << "   SISTEM MANAJEMEN AKUN\n";
        cout << "==============================\n";
        cout << "  1. Login\n  2. Register\n  3. Keluar\n";
        cout << "  Pilihan: "; cin >> opsi;

        if (opsi == 1) {
            int status = loginSystem(db, jumlahAkun, 3);
            if (status == -1) return 0;
            if (db[status].role == "admin")
                adminMenu(db, jumlahAkun);
            else
                userMenu(db, status);
        }
        else if (opsi == 2) {
            int id = regisSystem(db, jumlahAkun, urutId);
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
