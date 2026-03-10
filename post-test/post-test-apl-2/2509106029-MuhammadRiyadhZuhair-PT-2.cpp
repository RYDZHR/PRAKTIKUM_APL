#include <iostream>
#include <iomanip>

using namespace std;

struct update{
    string newUser;
    bool req = false;
};

struct akun{
    string username;
    string password;
    string email;
    string role;
    int id;
    bool acc;
    bool delReq;
    update reqUp;
};

akun db[100];
int jumlahakun = 0;
int urutId = 1001;

int tabel(){
    if (jumlahakun == 0) return 0;

    cout << "\n" << setfill('=') << setw(60) << "=" << endl;
    cout << setfill(' ') << "| " << setw(5) << "ID" << " | " << setw(15) << "Username" 
         << " | " << setw(10) << "Status" << " | " << setw(10) << "Hapus?" << " |" << endl;
    cout << setfill('-') << setw(60) << "-" << endl;

    for (int i = 0; i < jumlahakun; i++){
        cout << setfill(' ') << "| " << setw(5) << db[i].id << " | " << setw(15) << db[i].username 
             << " | " << setw(10) << (db[i].acc ? "Aktif" : "PENDING") 
             << " | " << setw(10) << (db[i].delReq ? "YA" : "TIDAK") << " |" << endl;
    }
    cout << setfill('=') << setw(60) << "60" << endl;
    return jumlahakun;
}

int regisSystem(akun database[], int &jumlah, int &idBaru) {
    if (jumlah >= 100) return 0;

    int i = jumlah;
    database[i].id = idBaru++;
    cout << "\n--- Registration system Ver0.1 ---" << endl;
    cout << "Username: "; cin >> database[i].username;
    cout << "Password: "; cin >> database[i].password;
    cout << "Email   : "; cin >> database[i].email;
    
    database[i].role = "user"; 
    database[i].acc = false;
    database[i].delReq = false;
    database[i].reqUp.req = false;

    jumlah++;
    return database[i].id;
    
}

bool hapusAkun(int targetid){
    for (int i = 0; i < jumlahakun; i++) {
        if(db[i].id == targetid) {
            for (int j = i; j < jumlahakun - 1; j++) {
                db[j] = db[j + 1];
            }
            jumlahakun--;
            return true;
        }
    }
    return false;
}

int Adminmenu() {
    string konsole;
    cout << "\n[CONSOLE ADMIN AKTIF] Ketik 'help' untuk bantuan." << endl;
    while (true) {
        cout << "admin@root:~# "; cin >> konsole;
        if (konsole == "ls") {
            if (tabel() == 0) cout << "Kosong. \n"; 
        } 
        else if (konsole == "acc") {
            int target; cout << "ID yang akan di-ACC: "; cin >> target;
            bool ketemu = false;
            for (int i = 0; i < jumlahakun; i++) {
                if (db[i].id == target) {
                    db[i].acc = true;
                    cout << "Akun " << db[i].username << " Berhasil diaktifkan!\n";
                    ketemu = true; break;
                }
            }
            if (!ketemu) cout << "ID tidak ditemukan.\n";
        }
        else if (konsole == "up_acc") {
            bool ada = false;
            for (int i = 0; i < jumlahakun; i++) {
                if (db[i].reqUp.req) {
                    cout << "User " << db[i].username << " ganti ke: " << db[i].reqUp.newUser << " (y/n)? ";
                    char pilih; cin >> pilih;
                    if (pilih == 'y') {
                        db[i].username = db[i].reqUp.newUser;
                        db[i].reqUp.req = false;
                        cout << "Berhasil di-update!\n";
                    } else {
                        db[i].reqUp.req = false;
                        cout << "Request ditolak.\n";
                    }
                    ada = true;
                }
            }
            if (!ada) cout << "Tidak ada request update pending.\n";
        }
        else if (konsole == "delete") {
            int id; cout << "ID yang ingin dihapus: "; cin >> id;
            if (hapusAkun(id)) cout << "Berhasil Dihapus.\n";
            else cout << "ID tidak ditemukan.\n";
        } 
        else if (konsole == "exit") {
            return 0;
        } 
        else if (konsole == "help") {
            cout << "ls, acc, up_acc, delete, exit\n";
        }
    }
}

int Usermenu(int idx) {
    int pilihan;
    while (true) {
        cout << "\n==== Welcome, " << db[idx].username << " ====" << endl;
        if (!db[idx].acc) cout << "[Peringatan: Akun Anda sedang menunggu ACC Admin]" << endl;
        cout << "1. Profil\n2. Request Ganti Nama\n3. Request Hapus Akun\n4. Logout\nPilih: "; cin >> pilihan;

        if (pilihan == 1) {
            cout << "\n--- PROFIL ANDA ---" << endl;
            cout << "ID: " << db[idx].id << "\nEmail: " << db[idx].email << "\nRole: " << db[idx].role << endl;
        } 
        else if (pilihan == 2) {
            cout << "Masukkan Username Baru: "; cin >> db[idx].reqUp.newUser;
            db[idx].reqUp.req = true;
            cout << "Request update terkirim ke admin.\n";
        }
        else if (pilihan == 3) {
            db[idx].delReq = true;
            cout << "Request hapus terkirim, mohon tunggu admin.\n";
        } 
        else if (pilihan == 4) {
            return 0;
        }
    }
}

int Loginsystem(){
    string user, pass;
    int batas = 0;

    while (batas < 3){
        cout << "\nUsername: "; cin >> user;
        cout << "Password: "; cin >> pass;
        for (int i = 0; i < jumlahakun ; i++){
            if (db[i].username == user & db[i].password == pass) return i;
        }
        batas++;
        cout << "Nu'uh, coba lagi " << 3 - batas << endl;
    }
    return -1;
}

int main() {
    db[jumlahakun++] = {"riyadh", "029", "admin@max.com", "admin", 999, true, false};

    while (true) {
        int opsi;
        cout << "\n1. Login\n2. Register\n3. Exit\nPilihan: "; cin >> opsi;

        if (opsi == 1) {
            int statuslogin = Loginsystem();
            if (statuslogin == -1) {
                cout << "GET OUT!!!.\n";
                return 0;
            } else {
                // Cek apakah user sudah di-ACC (Kecuali Admin)
                if (db[statuslogin].role == "admin") {
                    Adminmenu();
                } else {
                    Usermenu(statuslogin);
                }
            }
        } 
        else if (opsi == 2) {
            int idBaru = regisSystem(db, jumlahakun, urutId);
            if (idBaru != 0) cout << "Berhasil! ID Anda: " << idBaru << endl;
            else cout << "Database penuh!\n";
        } 
        else if (opsi == 3) {
            break;
        }
    }
    return 0;
}
