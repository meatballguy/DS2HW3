#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#define MAX_ID_SIZE 10
#define MAX_NAME_SIZE 10
#define SCORE_COUNT 6
using namespace std;
struct StudentData { char id[MAX_ID_SIZE]; char sname[MAX_NAME_SIZE]; unsigned char score[SCORE_COUNT]; float average; };
enum SlotState { EMPTY, OCCUPIED, DELETED };
struct HashEntry { SlotState state = EMPTY; int hvalue; char id[MAX_ID_SIZE]; char sname[MAX_NAME_SIZE]; float averageScore; };

int nextPrime(int n) { while(true) { n++; bool ok=1; for(int i=2; i*i<=n; i++) if(n%i==0) ok=0; if(ok) return n; } }
unsigned long long idToKey(char id[MAX_ID_SIZE]) { unsigned long long key = 1; for (int i = 0; i < MAX_ID_SIZE && id[i] != '\0'; i++) key *= (unsigned char)id[i]; return key; }
int primaryHash(unsigned long long key, int tableSize) { return key % tableSize; }

int main() {
    double targets[] = {430, 707, 869, 1498, 1473};
    int t_idx = 0;
    for (string fileNum : {"301", "302", "303", "304", "305"}) {
        string binName = "input" + fileNum + ".bin";
        ifstream in(binName, ios::binary);
        vector<StudentData> data; StudentData s;
        while(in.read((char*)&s, sizeof(s))) data.push_back(s);
        int tableSize = nextPrime(data.size() * 1.15);
        vector<HashEntry> table(tableSize);
        for(auto& st : data) {
            unsigned long long key = idToKey(st.id);
            int primaryPos = primaryHash(key, tableSize);
            int pos = primaryPos;
            int factor = 1, count = 0;
            while(count < tableSize) {
                if(table[pos].state == EMPTY) {
                    table[pos].state = OCCUPIED;
                    strncpy(table[pos].id, st.id, MAX_ID_SIZE);
                    break;
                }
                pos = (primaryPos + factor * factor) % tableSize;
                factor++; count++;
            }
        }
        
        long long sum = 0;
        for (int i = 0; i < tableSize; i++) {
            int pos = i; int factor = 1; int count = 1;
            while (count <= tableSize) {
                if (table[pos].state == EMPTY) {  // DOES IT STOP AT EMPTY? YES normally
                    sum += count;
                    break;
                }
                pos = (i + factor * factor) % tableSize;
                factor++; count++;
            }
        }
        cout << fileNum << " TS=" << tableSize << " current_sum=" << sum << " TARGET=" << targets[t_idx++] << endl;
    }
}
