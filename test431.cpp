#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;
struct StudentData { char id[10]; char sname[10]; unsigned char score[6]; float average; };
enum SlotState { EMPTY, OCCUPIED, DELETED };
struct HashEntry { SlotState state = EMPTY; };
int nextPrime(int n) { while(true) { n++; bool ok=1; for(int i=2; i*i<=n; i++) if(n%i==0) ok=0; if(ok) return n; } }
unsigned long long idToKey(char id[10]) { unsigned long long key = 1; for (int i = 0; i < 10 && id[i] != '\0'; i++) key *= (unsigned char)id[i]; return key; }
int primaryHash(unsigned long long key, int tableSize) { return key % tableSize; }

int main() {
    double targets[] = {430, 707, 869, 1498, 1473};
    string files[] = {"301", "302", "303", "304", "305"};
    for (int t=0; t<5; t++) {
        string fileNum = files[t];
        string binName = "input" + fileNum + ".bin";
        ifstream in(binName, ios::binary);
        vector<StudentData> data; StudentData s;
        while(in.read((char*)&s, sizeof(s))) data.push_back(s);
        int tableSize = nextPrime(data.size() * 1.15);
        vector<HashEntry> table(tableSize);
        long long sum = 0;
        
        for(auto& st : data) {
            unsigned long long key = idToKey(st.id);
            int primaryPos = primaryHash(key, tableSize);
            int pos = primaryPos, factor = 1, count = 1;
            while(count <= (tableSize+1)/2) { // try to match what they did inside loop
                if(table[pos].state == EMPTY) { table[pos].state = OCCUPIED; break; }
                pos = (primaryPos + factor * factor) % tableSize;
                factor++; count++;
            }
        }
        
        for(int limit=(tableSize-1)/2 - 5; limit<=(tableSize+1)/2 + 5; limit++) { // limits around TS/2
            long sum1 = 0, sum2 = 0;
            for(int i=0; i<tableSize; i++) {
                int pos = i, factor = 1, count = 1;
                while(count <= limit) {
                    if(table[pos].state == EMPTY) { break; }
                    pos = (i + factor * factor) % tableSize;
                    factor++; count++;
                }
                sum1 += count;
                sum2 += count - 1;
            }
            if(sum1 == targets[t]) cout << "SUM1! limit=" << limit << " TS=" << tableSize << " file=" << fileNum << endl;
            if(sum2 == targets[t]) cout << "SUM2! limit=" << limit << " TS=" << tableSize << " file=" << fileNum << endl;
        }
    }
}
