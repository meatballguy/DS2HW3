#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#define MAX_ID_SIZE 10
#define MAX_NAME_SIZE 10
#define SCORE_COUNT 6
using namespace std;
struct StudentData { char id[MAX_ID_SIZE]; char sname[MAX_NAME_SIZE]; unsigned char score[SCORE_COUNT]; float average; };
enum SlotState { EMPTY, OCCUPIED };
struct HashEntry { SlotState state = EMPTY; int hvalue; char id[MAX_ID_SIZE]; char sname[MAX_NAME_SIZE]; float averageScore; };

int nextPrime(int n) { while(true) { n++; bool ok=1; for(int i=2; i*i<=n; i++) if(n%i==0) ok=0; if(ok) return n; } }
unsigned long long idToKey(char id[MAX_ID_SIZE]) { unsigned long long key = 1; for (int i = 0; i < MAX_ID_SIZE && id[i] != '\0'; i++) key *= (unsigned char)id[i]; return key; }
int primaryHash(unsigned long long key, int tableSize) { return key % tableSize; }

int main() {
    for (string fileNum : {"301", "302", "303", "304", "305"}) {
        string binName = "input" + fileNum + ".bin";
        ifstream in(binName, ios::binary);
        vector<StudentData> data; StudentData s;
        while(in.read((char*)&s, sizeof(s))) data.push_back(s);
        int tableSize = nextPrime(data.size() * 1.15);
        vector<HashEntry> table(tableSize);
        int inserted = 0;
        int max_loops = (tableSize + 1) / 2; // Let's guess this is the TA's limit
        
        for(auto& st : data) {
            unsigned long long key = idToKey(st.id);
            int primaryPos = primaryHash(key, tableSize);
            int pos = primaryPos;
            int factor = 1, count = 1; // count=1 means we checked primaryPos
            bool success = false;
            while(count <= max_loops) {
                if(table[pos].state == EMPTY) {
                    table[pos].state = OCCUPIED;
                    inserted++;
                    success = true;
                    break;
                }
                pos = (primaryPos + factor * factor) % tableSize;
                factor++; count++;
            }
            if(!success) {
                // cout << "Discarded " << st.id << endl;
            }
        }
        
        long long sum_c = 0;
        for (int i = 0; i < tableSize; i++) {
            int pos = i; int factor = 1; int count = 1;
            while (count <= max_loops && table[pos].state != EMPTY) {
                pos = (i + factor * factor) % tableSize;
                factor++; count++;
            }
            sum_c += count;
        }
        cout << fileNum << ": inserted=" << inserted << " expectedTarget=" << sum_c << endl;
    }
}
