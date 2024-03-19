#include <iostream>
#include <iomanip>
using namespace std;

void inputData(int& recordCount, int maxRecords, int id[], string name[], double price[]) {
    if (recordCount < maxRecords) {
        recordCount++;
        id[recordCount] = recordCount;
        cin.ignore();

        cout << "Input Nama barang: ";
        getline(cin, name[recordCount]);

        string priceInput;
        cout << "Input Harga: ";
        cin >> priceInput;

        try {
            price[recordCount] = stod(priceInput);
        } catch (const invalid_argument& e) {
            cout << "Harga harus berupa bilangan. Coba lagi." << endl;
            recordCount--;
            return;
        }
    }
}

void printDetails(int i, int recordCount, int id[], string name[], double price[]) {
    if (i <= recordCount) {
        cout << id[i] << "         " << name[i] << "      " << fixed << setprecision(2) << price[i] << endl;
        printDetails(i + 1, recordCount, id, name, price);
    }
}

bool editDetails(int& recordCount, int id[], string name[], double price[]) {
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

    // Cek apakah ID ada dalam array
    bool idExists = false;
    for (int i = 1; i <= recordCount; i++) {
        if (id[i] == editId) {
            idExists = true;
            break;
        }
    }

    if (idExists) {
        cin.ignore();
        cout << "Input Nama Baru: ";
        getline(cin, name[editId]);

        string priceInput;
        cout << "Input Harga Baru: ";
        cin >> priceInput;

        try {
            price[editId] = stod(priceInput);
        } catch (const invalid_argument& e) {
            cout << "Harga harus berupa bilangan. Coba lagi." << endl;
            return false;
        }

        char confirm;
        cout << "Apakah Anda ingin mengedit ID lain? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            // Panggil fungsi secara rekursif
            return editDetails(recordCount, id, name, price);
        } else {
            return true;
        }
    } else {
        cout << "ID tidak ditemukan" << endl;
        return false;
    }
}


bool deleteRecord(int& recordCount, int id[], string name[], double price[]) {
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
        // Geser semua catatan setelah ID yang dihapus ke posisi sebelumnya
        for (int i = deleteId; i < recordCount; i++) {
            id[i] = id[i + 1] - 1; // Kurangi ID dengan 1
            name[i] = name[i + 1];
            price[i] = price[i + 1];
        }
        recordCount--;
        cout << "Catatan dengan ID " << deleteId << " berhasil dihapus." << endl;

        char confirm;
        cout << "Apakah Anda ingin menghapus ID lain? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            // Panggil prosedur secara rekursif
            return deleteRecord(recordCount, id, name, price);
        } else {
            return true;
        }
    } else {
        cout << "ID tidak valid. Tidak ada catatan dengan ID tersebut." << endl;
        return false;
    }
}


int main() {
    string nama;
    string nim;
    int kesempatan = 3;

    while (kesempatan > 0) {
        cout << "Masukkan nama Anda: ";
        getline(cin, nama);

        cout << "Masukkan NIM Anda: ";
        cin >> nim;
        cin.ignore();

        if (nama == "Adhitya Fajar Al-Huda" && nim == "2309106027") {
            cout << "Login berhasil. Selamat datang, " << nama << "!" << endl;
            int maxRecords = 300; // Batas maksimum catatan pengeluaran
		    int recordCount = 0; // Jumlah catatan saat ini
		    int id[maxRecords];
		    string name[maxRecords];
		    double price[maxRecords];
            int pilihan;

            while (true) {
	            cout << "Catatan Pengeluaran Uang:" << endl;
	            cout << "1. Tambah data jika ada mengeluarkan uang bulan ini" << endl;
	            cout << "2. Lihat data pengeluaran" << endl;
	            cout << "3. Ganti atau update pengeluaran uang" << endl;
	            cout << "4. Delete data pengeluaran " << endl;
	            cout << "5. Keluar" << endl;
	            cout << "Pilih menu (1-5): ";
	            cin >> pilihan;
	
	            switch (pilihan) {
	                case 1:{
						inputData(recordCount, maxRecords, id, name, price);
        				break;
					}
	            	
					case 2:{
						cout << "ID       Nama        Harga" << endl;
				        printDetails(1, recordCount, id, name, price);
						break;
					}

	            	case 3:{
						if (editDetails(recordCount, id, name, price)) {
				            cout << "Pengeditan berhasil." << endl;
				        } else {
				            cout << "Pengeditan gagal." << endl;
				        }
				        break;
				    }
			    
	            	case 4:{
						if (deleteRecord(recordCount, id, name, price)) {
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
            kesempatan--;
            cout << "Login gagal. Sisa kesempatan: " << kesempatan << endl;
        }
    }

    if (kesempatan == 0) {
        cout << "Anda telah melebihi batas percobaan. Program berakhir." << endl;
    }

    return 0;
}
