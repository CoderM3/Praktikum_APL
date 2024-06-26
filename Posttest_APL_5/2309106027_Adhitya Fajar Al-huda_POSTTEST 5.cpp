#include <iostream>
#include <iomanip>
#include <limits>
#include <ios>
using namespace std;

struct Pengeluaran {
    int id;
    string name;
    double price;
};


void inputData(int& recordCount, int maxRecords, Pengeluaran pengeluaran[]) {
    if (recordCount < maxRecords) {
        recordCount++;
        pengeluaran[recordCount].id = recordCount;
        cin.ignore();

        cout << "Input Nama barang: ";
        getline(cin, pengeluaran[recordCount].name);

        string priceInput;
        cout << "Input Harga: ";
        cin >> priceInput;

        try {
            pengeluaran[recordCount].price = stod(priceInput);
        } catch (const invalid_argument& e) {
            cout << "Harga harus berupa bilangan. Coba lagi." << endl;
            recordCount--;
            return;
        }
    }
}

void printDetails(int i, int recordCount, Pengeluaran pengeluaran[]) {
    if (i <= recordCount) {
        cout << pengeluaran[i].id << "         " << pengeluaran[i].name << "      " << fixed << setprecision(2) << pengeluaran[i].price << endl;
        printDetails(i + 1, recordCount, pengeluaran);
    }
}

bool editDetails(int& recordCount, Pengeluaran pengeluaran[]) {
    string editIdInput;
    int editId;
    cout << "Masukkan ID catatan yang ingin diedit: ";
    cin >> editIdInput;
    try {
        editId = stoi(editIdInput);
    } catch (const invalid_argument& e) {
        cout << "ID harus berupa bilangan bulat. Coba lagi." << endl;
        return false;
    }

    bool idExists = false;
    for (int i = 1; i <= recordCount; i++) {
        if (pengeluaran[i].id == editId) {
            idExists = true;
            break;
        }
    }

    if (idExists) {
        cin.ignore();
        cout << "Input Nama Baru: ";
        getline(cin, pengeluaran[editId].name);

        string priceInput;
        cout << "Input Harga Baru: ";
        cin >> priceInput;

        try {
            pengeluaran[editId].price = stod(priceInput);
        } catch (const invalid_argument& e) {
            cout << "Harga harus berupa bilangan. Coba lagi." << endl;
            return false;
        }

        char confirm;
        cout << "Apakah Anda ingin mengedit ID lain? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            return editDetails(recordCount, pengeluaran);
        } else {
            return true;
        }
    } else {
        cout << "ID tidak ditemukan" << endl;
        return false;
    }
}


bool deleteRecord(int& recordCount, Pengeluaran pengeluaran[]) {
    string deleteIdInput;
    int deleteId;
    cout << "Masukkan ID catatan yang ingin dihapus: ";
    cin >> deleteIdInput;
    try {
        deleteId = stoi(deleteIdInput);
    } catch (const invalid_argument& e) {
        cout << "ID harus berupa bilangan bulat. Coba lagi." << endl;
        return false;
    }

    if (deleteId >= 1 && deleteId <= recordCount) {
        for (int i = deleteId; i < recordCount; i++) {
            pengeluaran[i] = pengeluaran[i + 1];
            pengeluaran[i].id--;
        }
        recordCount--;
        cout << "Catatan dengan ID " << deleteId << " berhasil dihapus." << endl;

        char confirm;
        cout << "Apakah Anda ingin menghapus ID lain? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            return deleteRecord(recordCount, pengeluaran);
        } else {
            return true;
        }
    } else {
        cout << "ID tidak valid. Tidak ada catatan dengan ID tersebut." << endl;
        return false;
    }
}


struct User {
    string nama;
    string nim;
    int kesempatan;
    Pengeluaran pengeluaran[300];
};

bool login(User* users, int numUsers) {
    string inputNama, inputNIM;
    cout << "Masukkan nama Anda: ";
    getline(cin, inputNama);

    cout << "Masukkan NIM Anda: ";
    cin >> inputNIM;
    cin.ignore();

    for (int i = 0; i < numUsers; ++i) {
        if (users[i].nama == inputNama && users[i].nim == inputNIM) {
            cout << "Login berhasil. Selamat datang, " << users[i].nama << "!" << endl;
            return true;
        }
    }

    cout << "Login gagal. Silakan coba lagi." << endl;
	return false;
}

int main() {
    User user;
    user.kesempatan = 3;
    const int maxUsers = 3;
    User users[maxUsers] = {
        {"Adhitya Fajar Al-Huda", "2309106027", 3},
        {"User1", "123456", 3},
        {"User2", "654321", 3}
    };
    int loginAttempts = 0;
	while (loginAttempts < 3){
	if (login(users, maxUsers)) {
			int maxRecords = 300;
            int recordCount = 0;
            int pilihan;

            while (true) {
	            cout << "Catatan Pengeluaran Uang:" << endl;
	            cout << "1. Tambah data jika ada mengeluarkan uang bulan ini" << endl;
	            cout << "2. Lihat data pengeluaran" << endl;
	            cout << "3. Ganti atau update pengeluaran uang" << endl;
	            cout << "4. Delete data pengeluaran " << endl;
	            cout << "5. Keluar" << endl;
				do {
				    cout << "Pilih menu (1-5): ";
				    cin >> pilihan;
				
				    if(cin.fail()) {
				        cin.clear(); // menghapus flag kesalahan sebelumnya
				        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // menghapus 'bad' input
				        cout << "Masukan tidak valid. Silakan masukkan angka.\n";
				    }
				} while (cin.fail());     
	
	            switch (pilihan) {
                    case 1:{
                        inputData(recordCount, maxRecords, user.pengeluaran);
                        break;
                    }
                    
                    case 2:{
                        cout << "ID       Nama        Harga" << endl;
                        printDetails(1, recordCount, user.pengeluaran);
                        break;
                    }

                    case 3:{
                        if (editDetails(recordCount, user.pengeluaran)) {
                            cout << "Pengeditan berhasil." << endl;
                        } else {
                            cout << "Pengeditan gagal." << endl;
                        }
                        break;
                    }
                
                    case 4:{
                        if (deleteRecord(recordCount, user.pengeluaran)) {
                            cout << "Penghapusan berhasil." << endl;
                        } else {
                            cout << "Penghapusan gagal." << endl;
                        }
                        break;
                    }
                    

                    case 5:
                        cout << "Terima kasih telah menggunakan program. Program berakhir." << endl;
                        return 0;

                    default:
                        cout << "Pilihan tidak valid." << endl;
	        	}
            }

			break;
        } else {
            loginAttempts++;
            cout << "Kesempatan tersisa: " << 3 - loginAttempts << endl;
        }
    }

    cout << "Kesempatan habis. Program berakhir." << endl;
    return 0;
}