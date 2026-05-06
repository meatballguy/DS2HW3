/*11327146 莊立聖 11327155 黃宇謙*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <iomanip>
#define MAX_ID_SIZE 10
#define MAX_NAME_SIZE 10
#define SCORE_COUNT 6

using namespace std;

struct StudentData {
    char id[MAX_ID_SIZE];
    char sname[MAX_NAME_SIZE];
    unsigned char score[SCORE_COUNT];
    float average;
};

class HashTable {
    private:
        enum SlotState { EMPTY, OCCUPIED, DELETED };

        struct HashEntry {
            SlotState state = EMPTY;
            int hvalue;
            char id[MAX_ID_SIZE];
            char sname[MAX_NAME_SIZE];
            float averageScore;
        };

        vector<HashEntry> table;
        int tableSize;
        int totalItems;
        int dataSize;

        unsigned long long idToKey(char id[MAX_ID_SIZE]) {
            unsigned long long key = 1;
            for (int i = 0; i < MAX_ID_SIZE && id[i] != '\0'; i++) {
                key *= (unsigned char)id[i];
            }
            return key;
        }

        int primaryHash(unsigned long long key) {
            return key % tableSize;
        }

        int secondaryHash(unsigned long long hashValue, int dataSize) { 
            int step = nextPrime(dataSize / 5);
            return step - (hashValue % step);
        }

        int nextPrime(int n) {
            while (true) {
                n++;
                bool isPrime = true;
                for (int i = 2; i * i <= n; i++) {
                    if (n % i == 0) {
                        isPrime = false;
                        break;
                    }
                }
                if (isPrime) return n;
            }
        }

    public:
        HashTable(int dataSize) {
            this->tableSize  = nextPrime(dataSize * 1.15);
            this->dataSize = dataSize;
            table.resize(tableSize);
            totalItems = 0;
        }

        bool insertQuadratic(StudentData& s) {
            unsigned long long key = idToKey(s.id);
            int pos = primaryHash(key);
            int primaryPos = pos;
            int factor = 1;
            int count = 0;
            while (count < tableSize) {
                if (table[pos].state == EMPTY || table[pos].state == DELETED) {
                    table[pos].hvalue = primaryHash(key);
                    strncpy(table[pos].id, s.id, MAX_ID_SIZE);
                    strncpy(table[pos].sname, s.sname, MAX_NAME_SIZE);
                    table[pos].averageScore = s.average;
                    table[pos].state = OCCUPIED;
                    totalItems++;
                    return true;
                } else if (table[pos].state == OCCUPIED && strcmp(table[pos].id, s.id) == 0) {
                    return true;
                }
                pos = (primaryPos + factor * factor) % tableSize;
                factor++;
                count++;
            }
            return false;
        }

        bool insertDouble(StudentData& s) {
            unsigned long long key = idToKey(s.id);
            int pos = primaryHash(key);
            int hash2 = secondaryHash(key, dataSize);
            int stepCount = 0;
            int count = 0;
            while (count < tableSize) {
                if (table[pos].state == EMPTY || table[pos].state == DELETED) {
                    table[pos].hvalue = primaryHash(key);
                    strncpy(table[pos].id, s.id, MAX_ID_SIZE);
                    strncpy(table[pos].sname, s.sname, MAX_NAME_SIZE);
                    table[pos].averageScore = s.average;
                    table[pos].state = OCCUPIED;
                    totalItems++;
                    return true;
                } else if (table[pos].state == OCCUPIED && strcmp(table[pos].id, s.id) == 0) {
                    return true;
                }
                stepCount++;
                pos = (pos + hash2) % tableSize;
                count++;
            }
            return false;
        }

        int quadraticProbeCount(char id[MAX_ID_SIZE]) {
            unsigned long long key = idToKey(id);
            int pos = primaryHash(key);
            int primaryPos = pos;
            int factor = 1;
            int count = 1;
            while (count <= tableSize) {
                if (table[pos].state == EMPTY) {
                    return count;
                } else if (table[pos].state == OCCUPIED && strcmp(table[pos].id, id) == 0) {
                    return count;
                }
                pos = (primaryPos + factor * factor) % tableSize;
                factor++;
                count++;
            }
            return count;
        }

        int doubleHashProbeCount(char id[MAX_ID_SIZE]) {
            unsigned long long key = idToKey(id);
            int pos = primaryHash(key);
            int hash2 = secondaryHash(key, dataSize);
            int stepCount = 1;
            int count = 1;
            while (count <= tableSize) {
                if (table[pos].state == EMPTY) {
                    return count;
                } else if (table[pos].state == OCCUPIED && strcmp(table[pos].id, id) == 0) {
                    return count;
                }
                pos = (pos + hash2) % tableSize;
                stepCount++;
                count++;
            }
            return count;
        }

        pair<double, double> getQuadraticProbeStats() {
            double successSearchCount = 0;
            double unsuccessSearchCount = 0;
            for (auto& entry : table) {
                if (entry.state == OCCUPIED) {
                    successSearchCount += quadraticProbeCount(entry.id);
                }
            }
            
            for (int i = 0; i < tableSize; i++) {
                int pos = i;
                int factor = 1;
                int count = 1;
                while (count <= tableSize && table[pos].state != EMPTY) {
                    pos = (i + factor * factor) % tableSize;
                    factor++;
                    count++;
                }
                unsuccessSearchCount += (count - 1);
            }
            return make_pair(successSearchCount / totalItems, unsuccessSearchCount / tableSize);
        }

        double getDoubleHashProbeStats() {
            double successSearchCount = 0;
            for (auto& entry : table) {
                if (entry.state == OCCUPIED) {
                    successSearchCount += doubleHashProbeCount(entry.id);
                }
            }
            return successSearchCount / totalItems;
        }

        void clear() {
            table.clear();
            totalItems = 0;
        }

        ~HashTable() {
            table.clear();
        }

        void createQuadraticHashFile(string fileNum) {
            string fileName = "quadratic" + fileNum + ".txt";
            ofstream out(fileName);
            out << " --- Hash table created by Quadratic probing ---\n";
            for (int i = 0; i < tableSize; i++) {
                out << "[" << setw(3) << i << "] ";
                if (table[i].state == OCCUPIED) {
                    out << setw(10) << table[i].hvalue << ", "
                        << setw(10) << table[i].id << ", "
                        << setw(10) << table[i].sname << ", "
                        << setw(10) << defaultfloat << table[i].averageScore;
                }
                out << "\n";
            }
            out << " ----------------------------------------------------- \n";
            out.close();
        }

        void createDoubleHashFile(string fileNum) {
            string fileName = "double" + fileNum + ".txt";
            ofstream out(fileName);
            out << " --- Hash table created by Double hashing    ---\n";
            for (int i = 0; i < tableSize; i++) {
                out << "[" << setw(3) << i << "] ";
                if (table[i].state == OCCUPIED) {
                    out << setw(10) << table[i].hvalue << ", "
                        << setw(10) << table[i].id << ", "
                        << setw(10) << table[i].sname << ", "
                        << setw(10) << defaultfloat << table[i].averageScore;
                }
                out << "\n";
            }
            out << " ----------------------------------------------------- \n";
            out.close();
        }
};

class System {
  public:
    void static readBin(string fileNum, vector<StudentData>& data) {
        string binName = "input" + fileNum + ".bin";
        if (!ifstream(binName).good()) {
            return;
        }
        ifstream binIn(binName, ios::in | ios::binary);
        StudentData temp;
        while (binIn.read(reinterpret_cast<char*>(&temp), sizeof(StudentData))) {
            data.push_back(temp);
        }
    }

    void static txtToBin(string fileNum, vector<StudentData>& data) {
        string tinName = "input" + fileNum + ".txt";
        if (!ifstream(tinName).good()) {
            return;
        }
        ifstream tin(tinName);
        string binName = "input" + fileNum + ".bin";
        ofstream outFile(binName, ios::out | ios::binary);
        
        string line;
        while (getline(tin, line)) {
            if (line.empty()) continue;

            StudentData student;
            memset(&student, 0, sizeof(StudentData));

            size_t tab1 = line.find('\t');
            if (tab1 == string::npos) continue;
            string tempID = line.substr(0, tab1);
            
            size_t tab2 = line.find('\t', tab1 + 1);
            if (tab2 == string::npos) continue;
            string tempName = line.substr(tab1 + 1, tab2 - tab1 - 1);
            
            strncpy(student.id, tempID.c_str(), sizeof(student.id) - 1);
            strncpy(student.sname, tempName.c_str(), sizeof(student.sname) - 1);

            stringstream ss(line.substr(tab2 + 1));
            unsigned int tempScore;
            for (int i = 0; i < SCORE_COUNT; ++i) {
                if (ss >> tempScore) {
                    student.score[i] = (unsigned char)tempScore;
                }
            }
            ss >> student.average;
            
            outFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));
        }
        outFile.close();
    }

    void static displayMissionList() {
        cout << endl << "* Data Structures and Algorithms *";
        cout << endl << "************ Hash Table **********";
        cout << endl << "* 0. QUIT                        *";
        cout << endl << "* 1. Quadratic probing           *";
        cout << endl << "* 2. Double hashing              *";
        cout << endl << "**********************************";
        cout << endl << "Input a choice(0, 1, 2): ";
    }

    bool static binaryFileExist(string fileNum) {
        string binName = "input" + fileNum + ".bin";
        return ifstream(binName).good();
    }

    bool static textFileExist(string fileNum) {
        string txtName = "input" + fileNum + ".txt";
        return ifstream(txtName).good();
    }

    bool static getCommand(int& cmd) {
        string input;
        while (input.empty()) getline(cin, input);
        try {
            size_t pos;
            cmd = stoi(input, &pos);
            if (pos != input.size()) {
                cout << "\nCommand does not exist!\n\n";
                return false;
            }
            if (cmd < 0 || cmd > 2)
                throw out_of_range("invalid");
        } catch (...) {
            cout << endl << "Command does not exist!\n" << endl;
            return false;
        }
        return true;
    }
};

int main() {
    vector<StudentData> data;
    string currentFileNum = "";
    while (true) {
        System::displayMissionList();
        int command;
        if(!System::getCommand(command)) continue;
        if (command == 0) break;
        switch (command) {
            case 1: {
                data.clear();
                string fileNum;
                cout << "\nInput a file number ([0] Quit): ";
                cin >> fileNum;
                if (fileNum == "0") {
                    cout << "\n";
                    break;
                }
                currentFileNum = fileNum;
                if (!System::binaryFileExist(fileNum)) {
                    cout << "\n### input" << fileNum << ".bin does not exist! ###\n";
                    if (!System::textFileExist(fileNum)) {
                        cout << "\n### input" << fileNum << ".txt does not exist! ###\n\n";
                        break;
                    }
                    System::txtToBin(fileNum, data);          
                }
                System::readBin(fileNum, data);
                
                HashTable ht(data.size());
                for (auto& st : data) {
                    ht.insertQuadratic(st);
                }
                ht.createQuadraticHashFile(fileNum);
                auto stats = ht.getQuadraticProbeStats();
                cout << "\nHash table has been successfully created by Quadratic probing\n";
                cout << "unsuccessful search: " << fixed << setprecision(4) << stats.second << " comparisons on average\n";
                cout << "successful search: " << fixed << setprecision(4) << stats.first << " comparisons on average\n";
                break;
            }

            case 2: {
                if (data.empty()) {
                    cout << "### Command 1 first. ###\n\n";
                    break;
                }
                string fileNum = currentFileNum;

                HashTable ht(data.size());
                for (auto& st : data) {
                    ht.insertDouble(st);
                }
                ht.createDoubleHashFile(fileNum);
                double stats = ht.getDoubleHashProbeStats();
                cout << "\nHash table has been successfully created by Double hashing   \n";
                cout << "successful search: " << fixed << setprecision(4) << stats << " comparisons on average\n";
                break;
            }
        }
    }
    return 0;
}
