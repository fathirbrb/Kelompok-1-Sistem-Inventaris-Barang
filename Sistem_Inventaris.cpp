#include <iostream>
#include <fstream> // untuk memasukan nama yang ada ketika kita mendaftar
#include <string>
#include <vector> // library struktur data dinamis agar lebih efesien
#include <limits> // untuk manipulasi data input
using namespace std;

// Fungsi untuk mendaftarkan user baru
void registerUser()
{
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ofstream file("userid.txt", ios::app); // untuk memastikan data baru tanpa menghapus yang lain // membuka file userid.txt
    if (file.is_open())                    // jika file userid.txt kebuka maka akan di jalankan code di bawah
    {
        file << username << " " << password << endl;
        file.close();
        cout << "Pendaftaran berhasil!" << endl;
    }
    else // jika filenya error
    {
        cout << "Gagal membuka file!" << endl;
    }
}

bool loginUser() // fungsi untuk login usernya
{
    string username, password;
    cout << "\nLogin" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("userid.txt"); // membaca file userid.txt apakah ada data pengguna di dalamnya
    string fileUser, filePass;
    bool ditemukan = false; // menandai jika file ini berhasil atau tidak

    if (file.is_open()) // jika file userid.txt di buka maka
    {
        while (file >> fileUser >> filePass) // membaca file baris demi baris dipisah menjadi fileuser dan filepass
        {
            if (fileUser == username && filePass == password) // jika dalam file userid.txt cocok atau true maka login berhasil
            {
                ditemukan = true;
                break;
            }
        }
        file.close(); // menutup file userid.txt

        if (ditemukan) // jika ditemukan user dan password maka
        {
            cout << "Login berhasil! Selamat datang user: " << username << "!" << endl;
            return true;
        }
        else // jika user dan password tidak di temukan maka
        {
            cout << "Login gagal. Username atau password salah." << endl;
            return false;
        }
    }
    else // jika file gagal di buka
    {
        cout << "Gagal membuka file!" << endl;
        return false;
    }
}
class Barang // mewakili satu barang
{
public: // dibuat public dan memiliki atribut
    int id;
    string nama;
    int jumlah;

    Barang(int id, string nama, int jumlah) // konstruktor untuk membuat objek barang
    {
        this->id = id; // this-> untuk membedakan antara parameter dan atribut class
        this->nama = nama;
        this->jumlah = jumlah;
    }

    void tampilkan() const // menampilkan semua barang dan tidak boleh mengubah data apapun
    {
        cout << "ID     : " << id << endl;
        cout << "Nama   : " << nama << endl;
        cout << "Jumlah : " << jumlah << endl;
        cout << "---------------------\n";
    }
};

class Inventaris // anggapannya database kecil
{
private:
    vector<Barang> daftar; // menyimpan barang secara dinamis atau terurut dan dideklarasikan private agar tidak bisa di akses di luar kelas

public: // metode untuk menambahkan atau memasukan barang baru
    void tambahBarang()
    {
        int id, jumlah;
        string nama;

        cout << "\nMasukkan ID barang (berupa angka)   : ";
        while (!(cin >> id))
        {
            cout << "Input tidak valid. Masukkan angka: "; 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } // digunakan untuk membersihkan kesalahan input.

        cout << "Masukkan nama barang : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nama);

        cout << "Masukkan jumlah      : ";
        while (!(cin >> jumlah))
        {
            cout << "Input tidak valid. Masukkan angka: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Barang b(id, nama, jumlah);
        daftar.push_back(b);// membuat penyimpanan barang
        cout << "Barang berhasil ditambahkan.\n";
    }
void cariBarang() const // metode untuk mencari barang sesuai id yg telah di masukkan
    {
        int id;
        cout << "\nMasukkan ID barang yang ingin dicari: ";
        cin >> id;

        for (const auto &b : daftar) // looping semua barang
        {
            if (b.id == id)
            {
                cout << "\nBarang ditemukan!\n";
                b.tampilkan(); // menampilkan barang
                return;
            }
        }
        cout << "Barang dengan ID " << id << " tidak ditemukan.\n";
    }

    void tampilkanSemua() const // metode untuk menampilkan semua barang
    {
        cout << "\n|Daftar Barang|\n";
        if (daftar.empty())
        {
            cout << "Belum ada barang.\n";
            return;
        }

        for (const auto &b : daftar)
        {
            b.tampilkan(); // menampilkan barang
        }
    }
};
