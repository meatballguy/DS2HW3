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

using namespace std;

struct StudentData {
    char id[10];
    char sname[10];
    unsigned char score[6];
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
        int primaryHash(string key) const;

        // 二次雜湊函數 (Double Hashing 專用)
        int secondaryHash(int key) const;

        // 尋找下一個質數 (用於設定 tableSize)
        int nextPrime(int n) const;

public:
        // 建構子：根據資料量計算適合的 Table Size (通常取資料量 1.5~2 倍後的質數)
        HashTable(int dataSize);

        // --- 核心功能 ---

        // 方法一：二次探測法 (Quadratic Probing)
        // 邏輯：pos = (hash + i^2) % tableSize
        bool insertQuadratic(const StudentData& s);

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

class IO {
  public:
    bool static readBin(string fileNum, vector<StudentData>& data) {
        // return false if bin don't exsist, then create bin file
        ifstream bin; // binary input
        string binName = "input" + fileNum + ".bin";
        ifstream binIn(binName, ios::in | ios::binary);
        if (!bin.is_open()) {
            cout << "\n###" << binName << " does not exist! ###\n";
            return false;
        }
        StudentData temp;
        // 3. 循環讀取直到檔案結束
        // read() 會回傳檔案流狀態，讀不到資料時會自動結束迴圈
        while (binIn.read(reinterpret_cast<char*>(&temp), sizeof(StudentData))) {
            data.push_back(temp);
        }
        return true;
    }

    bool static TxtToBin(string fileNum, vector<StudentData>& data) {
        ifstream tin; // text input
        string tinName = "input" + fileNum + ".txt";
        tin.open(tinName);
        if (!tin.is_open()) {
            // no file exsist
            cout << "\n###" << tinName << " does not exist! ###\n";
            return false;
        }

        // create a binary file, 
        string binName = "input" + fileNum + ".bin";
        ofstream outFile(binName, ios::out | ios::binary); // out means this file is for writing, binary means use binary mode to address this file
        if (!outFile) {
            cerr << "無法開啟檔案進行寫入！" << endl;
            return false;
        }
        // transform .txt to .bin
        string line;
        // 使用 getline 逐行讀取文字檔
        while (getline(tin, line)) {
            if (line.empty()) continue;

            StudentData student;
            // 初始化結構，避免殘留髒資料
            memset(&student, 0, sizeof(StudentData));

            stringstream ss(line);
            string tempID, tempName, part;

            // 1. 讀取學號與姓名
            ss >> tempID;
            ss >> tempName;
            
            // 複製到結構中的 char 陣列，確保不會溢位
            strncpy(student.id, tempID.c_str(), sizeof(student.id) - 1);
            strncpy(student.sname, tempName.c_str(), sizeof(student.sname) - 1);

            unsigned int tempScore;
            for (int i = 0; i < 6; ++i) {
                if (ss >> tempScore) {
                    student.score[i] = (unsigned char)tempScore;
                }
            }

            ss >> student.average;
            outFile.write(reinterpret_cast<const char*>(&student), sizeof(StudentData));
            data.push_back(student);
        }

        readBin(fileNum, data);
        return true;
    }
};


int main(void) {
    int command = -1;
    vector<StudentData> data;
    while (true) {
        cout << endl << "* Data Structures and Algorithms *";
        cout << endl << "************ Hash Table **********";
        cout << endl << "* 0. QUIT                        *";
        cout << endl << "* 1. Quadratic probing           *";
        cout << endl << "* 2. Double hashing              *";
        cout << endl << "**********************************";
        cout << endl << "Input a choice(0, 1, 2): ";
        
        string input;
        while (input.empty()) getline(cin, input); // for solving user keep inputting '\n' and related stuff
        try {
            size_t pos = 0;
            command = stoi(input, &pos);
            if (pos != input.size()) { // for solving inputs like 1.0, in this case pos will be 1 and input.size will be 3
                cout << "\nCommand does not exist!\n";
                continue;
            }
            if (command < 0 || command > 2)
                throw out_of_range("invalid");
        } catch (...) {
            cout << endl << "Command does not exist!" << endl;
            continue;
        }
        if (command == 0) break;
        switch (command) {
            case 1: {
                data.clear();
                string fileNum;
                cout << "\nInput a file number ([0] Quit): ";
                if (!(cin >> fileNum) || fileNum == "0") break;
                // try to read bin, no then try to create bin
                if (IO::readBin(fileNum, data) || IO::TxtToBin(fileNum, data)) {
                    // do quadratic probe
                }
                break;
            }
            case 2: {
                if (data.empty()) {
                    cout << "\n### Command 1 first. ###\n\n";
                    break;
                } else{
                    // TODO: do double hashing, output file
                }
            }
            case 3: {

            }
            case 4: {

            }
            default:
            cout << endl << "Command does not exist!" << endl;
            break;
        }
    } 
    return 0;
}