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
        // 定義儲存槽狀態，處理 Quadratic Probing 必備
        enum SlotState { EMPTY, OCCUPIED, DELETED };

        struct HashEntry {
            StudentData data;
            SlotState state = EMPTY;
        };

        vector<HashEntry> table;
        int tableSize;
        int totalItems;

        // --- 私有輔助函式 ---
        
        // 基礎雜湊函數 (將學號字串轉為索引)
        int primaryHash(char key[MAX_ID_SIZE]) {
            unsigned long long hashValue = 1;
            for (int i = 0; i < MAX_ID_SIZE && key[i] != '\0'; i++) {
                hashValue = (hashValue * key[i]) % tableSize;
            }
            return hashValue;
        };

        // 二次雜湊函數 (Double Hashing 專用)
        int secondaryHash(int key) const;

        // 尋找下一個質數 (用於設定 tableSize)
        int nextPrime(int n) const;

public:
        // 建構子：根據資料量計算適合的 Table Size (通常取資料量 1.5~2 倍後的質數)
        HashTable(int dataSize) {
            this->tableSize  = dataSize;
        };

        // --- 核心功能 ---

        // 方法一：二次探測法 (Quadratic Probing)
        // 邏輯：pos = (hash + i^2) % tableSize
        bool insertQuadratic(StudentData& s) {
            int pos = primaryHash(s.id);
            while (true) {

            }
        }

        // 方法二：雙重雜湊法 (Double Hashing)
        // 邏輯：pos = (hash1 + i * hash2) % tableSize
        bool insertDouble(const StudentData& s);

        // 搜尋功能
        int search(string id) const;

        // --- 工具功能 ---

        // 計算目前的成功/失敗平均探測次數 (作業通常會要求輸出)
        void getStats() const;

        // 清空 Table 以供下一個指令重新使用
        void clear();

        // 解構子
        ~HashTable();
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
        // 3. 循環讀取直到檔案結束
        // read() 會回傳檔案流狀態，讀不到資料時會自動結束迴圈
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
        
        if (!outFile) {
            cerr << "Unable to open file for writing: " << binName << endl;
            return;
        }
        
        string line;
        while (getline(tin, line)) {
            if (line.empty()) continue;

            StudentData student;
            // 初始化結構，避免殘留髒資料
            memset(&student, 0, sizeof(StudentData));

            stringstream ss(line);
            string tempID, tempName;

            // 1. 讀取學號與姓名
            ss >> tempID;
            ss >> tempName;
            
            // 複製到結構中的 char 陣列，確保不會溢位
            strncpy(student.id, tempID.c_str(), sizeof(student.id) - 1);
            strncpy(student.sname, tempName.c_str(), sizeof(student.sname) - 1);

            unsigned int tempScore;
            for (int i = 0; i < SCORE_COUNT; ++i) {
                if (ss >> tempScore) {
                    student.score[i] = (unsigned char)tempScore;
                }
            }
            ss >> student.average;
            
            // Write the struct to binary file
            outFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));
            data.push_back(student);
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
        while (input.empty()) getline(cin, input); // for solving user keep inputting '\n' and related stuff
        try {
            size_t pos = 0;
            cmd = stoi(input, &pos);
            if (pos != input.size()) { // for solving inputs like 1.0, in this case pos will be 1 and input.size will be 3
                cout << "\nCommand does not exist!\n";
                return false;
            }
            if (cmd < 0 || cmd > 2)
                throw out_of_range("invalid");
        } catch (...) {
            cout << endl << "Command does not exist!" << endl;
            return false;
        }
        return true;
    }
};

int main() {
    vector<StudentData> data;
    // HashTable hashTable(0);
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
                if (fileNum == "0") break;
                if (!System::binaryFileExist(fileNum)) {
                    cout << "### input" << fileNum << ".bin does not exist! ###\n\n";
                    if (!System::textFileExist(fileNum)) {
                        cout << "### input" << fileNum << ".txt does not exist! ###\n\n";
                        break;
                    }
                    System::txtToBin(fileNum, data);          
                }
                System::readBin(fileNum, data);
                // todo: do quadratic probing
                break;
            }

            case 2: {
                if (data.empty()) {
                    cout << "### Command 1 first. ###\n\n\n";
                    break;
                } else {
                    cout << endl << "Command does not exist!\n\n" << endl;
                }
                // do double hashing
            }
        }
    }
    return 0;
}