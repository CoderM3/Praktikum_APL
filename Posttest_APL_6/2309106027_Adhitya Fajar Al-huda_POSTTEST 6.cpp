#include <iostream>
#include <iomanip>
#include <limits>
#include <ios>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

struct Pengeluaran {
    int id;
    string name;
    double price;
};


void readDataFromCSV(int& recordCount, Pengeluaran pengeluaran[]) {
    ifstream inFile("data.csv");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, price;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, price, ',');
        recordCount = stoi(id);
        pengeluaran[recordCount].id = recordCount;
        pengeluaran[recordCount].name = name;
        pengeluaran[recordCount].price = stod(price);
    }
    inFile.close();
}


void inputData(int& recordCount, int maxRecords, Pengeluaran pengeluaran[]) {
	readDataFromCSV(recordCount, pengeluaran);
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

        ofstream outFile("data.csv", ios::app);
        outFile << recordCount << "," << pengeluaran[recordCount].name << "," << pengeluaran[recordCount].price << "\n";
        outFile.close();
    }
}

void insertionSort(int recordCount, Pengeluaran pengeluaran[]) {
    readDataFromCSV(recordCount, pengeluaran);
    for (int i = 1; i < recordCount; i++) {
        Pengeluaran key = pengeluaran[i];
        int j = i - 1;
        while (j >= 0 && pengeluaran[j].id > key.id) {
            pengeluaran[j + 1] = pengeluaran[j];
            j = j - 1;
        }
        pengeluaran[j + 1] = key;
    }
}


void sortByName(int& recordCount, Pengeluaran pengeluaran[]) {
    readDataFromCSV(recordCount, pengeluaran);
    for (int i = 0; i < recordCount - 1; i++) {
        for (int j = 0; j < recordCount - i - 1; j++) {
            if (pengeluaran[j].name > pengeluaran[j + 1].name) {
                swap(pengeluaran[j], pengeluaran[j + 1]);
            }
        }
    }
}

void sortByID(int& recordCount, Pengeluaran pengeluaran[]) {
    readDataFromCSV(recordCount, pengeluaran);
    for (int i = 0; i < recordCount - 1; i++) {
        for (int j = 0; j < recordCount - i - 1; j++) {
            if (pengeluaran[j].id < pengeluaran[j + 1].id) {
                swap(pengeluaran[j], pengeluaran[j + 1]);
            }
        }
    }
}


void printDetails(int i, int recordCount, Pengeluaran pengeluaran[]) {
    readDataFromCSV(recordCount, pengeluaran);
	if (i <= recordCount) {
        cout << pengeluaran[i].id << "         " << pengeluaran[i].name << "      " << fixed << setprecision(2) << pengeluaran[i].price << endl;
        printDetails(i + 1, recordCount, pengeluaran);
    }
}

bool editDetails(int& recordCount, Pengeluaran pengeluaran[]) {
    readDataFromCSV(recordCount, pengeluaran);
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

        ofstream outFile("data.csv");
        for (int i = 1; i <= recordCount; i++) {
            outFile << pengeluaran[i].id << "," << pengeluaran[i].name << "," << pengeluaran[i].price << "\n";
        }
        outFile.close();

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
    readDataFromCSV(recordCount, pengeluaran);
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

        ofstream outFile("data.csv");
        for (int i = 1; i <= recordCount; i++) {
            outFile << pengeluaran[i].id << "," << pengeluaran[i].name << "," << pengeluaran[i].price << "\n";
        }
        outFile.close();

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
	            cout << "2. Lihat data pengeluaran berdasarkan nama" << endl;
				cout << "3. Lihat data pengeluaran berdasarkan ID (descending)" << endl;
				cout << "4. Lihat data pengeluaran" << endl;
	            cout << "5. Ganti atau update pengeluaran uang" << endl;
	            cout << "6. Delete data pengeluaran " << endl;
	            cout << "7. Keluar" << endl;
				do {
				    cout << "Pilih menu (1-7): ";
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
                        sortByName(recordCount, user.pengeluaran);
                        cout << "ID       Nama        Harga" << endl;
                        printDetails(1, recordCount, user.pengeluaran);
                        break;
                    }
                    
                    case 3:{
                    	sortByID(recordCount, user.pengeluaran);
                    	cout<< "ID       Nama        Harga" << endl;
                    	printDetails(1, recordCount, user.pengeluaran);
						break;
					}
					
					case 4:{
						insertionSort(recordCount, user.pengeluaran);
						cout<< "ID       Nama        Harga" << endl;
                    	printDetails(1, recordCount, user.pengeluaran);
						break;
					}

                    case 5:{
                        if (editDetails(recordCount, user.pengeluaran)) {
                            cout << "Pengeditan berhasil." << endl;
                        } else {
                            cout << "Pengeditan gagal." << endl;
                        }
                        break;
                    }
                
                    case 6:{
                        if (deleteRecord(recordCount, user.pengeluaran)) {
                            cout << "Penghapusan berhasil." << endl;
                        } else {
                            cout << "Penghapusan gagal." << endl;
                        }
                        break;
                    }
                    

                    case 7:
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