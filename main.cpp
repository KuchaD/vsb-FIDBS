#include <iostream>
#include <chrono>
#include "Tables/cHeapTable.h"
#include "Tables/cHashTable.h"
#include "Tables/cRecordTable.h"

#define TKey int
#define TData int

void memoryTest();
void test2();
void test1();
void hashTableTest(const int rowCount, cMemory* wMemory, bool withoutRecursion);
float GetThroughput(int opsCount, float period,int unit = 1e6);

using namespace std;
using namespace std::chrono;

int main()
{
    int const RowCount = 10000000;
    memoryTest();

    printf("\n===========HEAP TABLE============\n");
    test1();
    printf("\n===========RECORD TABLE============\n");
    test2();
    printf("\n===========HASH TABLE============\n");
    hashTableTest(10000000, NULL,false);

    printf("\n===========HASH TABLE Memory============\n");
    auto c = new cMemory((RowCount + 1) * sizeof (cHashTableNode<TKey, TData>));
    hashTableTest(RowCount, c,false);

    printf("\n===========HASH TABLE Recusive============\n");
    c = new cMemory((RowCount + 1) * sizeof (cHashTableNode<TKey, TData>));
    hashTableTest(RowCount, c, true);

    printf("\n===========HASH TABLE withoutRecusive memory============\n");
    c = new cMemory((RowCount + 1) * sizeof (cHashTableNode<TKey, TData>));
    hashTableTest(RowCount,c,true);

    return 0;
}

void test2(){
    int const RowCount = 10000000;

    cRecordTable<TKey, TData> *table = new cRecordTable<TKey, TData>(RowCount);

    TKey key;
    TData data;

    // start insert
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < RowCount; i++)
    {
        key = data = i;
        if (!table->Add(key, data))
        {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());

    // start scan
    t1 = high_resolution_clock::now();

    for (int i = 0; i < RowCount; i++)
    {
        bool ret = table->Get(i, key, data);
        if (!ret || key != i || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());


    TData datax;
    t1 = high_resolution_clock::now();
    auto findkey = RowCount;
    bool find = table->Find(findkey, datax);
    if (!find ) {
        printf("Critical Error: Record key %d not found!\n", findkey);
    }else{
        printf("Record key %d found!\n", findkey);
    }
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table find done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());

    //printf("\nSize of %d", sizeof(table));
    delete table;
}

void test1(){
    int const RowCount = 10000000;

    cHeapTable<TKey, TData> *table = new cHeapTable<TKey, TData>(RowCount);

    TKey key;
    TData data;

    // start insert
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < RowCount; i++)
    {
        key = data = i;
        if (!table->Add(key, data))
        {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());

    // start scan
    t1 = high_resolution_clock::now();

    for (int i = 0; i < RowCount; i++)
    {
        bool ret = table->Get(i, key, data);
        if (!ret || key != i || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());


    TData datax;
    t1 = high_resolution_clock::now();
    auto findkey = RowCount;
    bool find = table->Find(findkey, datax);
    if (!find ) {
        printf("Critical Error: Record key %d not found!\n", findkey);
    }else{
        printf("Record key %d found!\n", findkey);
    }
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table find done. Time: %.2fs, Throughput: %.2f op/s.\n", time_span.count(), (float)RowCount / time_span.count());

    //printf("\nSize of %d", sizeof(table));
    delete table;

}

float GetThroughput(int opsCount, float period, int unit)
{
    return ((float)opsCount / unit) / period;
}

void hashTableTest(const int rowCount,cMemory* wMemory, bool withoutRecursion)
{
    cHashTable<TKey, TData> *hashTable = new cHashTable<TKey, TData>(rowCount,wMemory,withoutRecursion);

    TKey key;
    TData data;

    // start insert hash table
    auto t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++) {
        key = data = i;
        if (!hashTable->Add(key, data)) {
            printf("Critical Error: Record %d insertion failed!\n", i);
        }

        // for testing only
        /*for (int j = 0; j <= i; j++) {
        bool ret = hashTable->Find(j, data);
        if (!ret || data != j) {
        printf("Critical Error: Record %d not found!\n", i);
        return 0;
        }
        }*/

        if (i % 10000 == 0) {
            printf("#Record inserted: %d   \r", i);
        }
    }

    auto t2 = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Records insertion done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    // start scan hash table
    t1 = high_resolution_clock::now();

    for (int i = 0; i < rowCount; i++)
    {
        bool ret = hashTable->Find(i, data);
        if (!ret || data != i) {
            printf("Critical Error: Record %d not found!\n", i);
        }
        if (i % 10000 == 0)
        {
            printf("#Records retrieved: %d   \r", i);
        }
    }

    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    printf("Table scan done, HashTable. Time: %.2fs, Throughput: %.2f mil. op/s.\n", time_span.count(), GetThroughput(rowCount, time_span.count()));

    hashTable->PrintStat();

    delete hashTable;
}

void memoryTest() {
    int len = 1000000;
    int *data = new int[len];
    long sum = 0;
    srand(10);

    printf("\n===========Serial access memory============\n");
    printf("Data size: %d ", len);
    auto timeStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < len; ++i) {
        data[i] = rand() % len;
        sum += data[i];
    }
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto timeDuration = timeEnd - timeStart;
    auto timeMilis = std::chrono::duration_cast<std::chrono::milliseconds>(timeDuration).count();
    printf("Time: %d ms", timeMilis);
    printf("\n===========Random access memory============\n");
    printf("Data size: %d ", len);
    timeStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < len; ++i) {
        int j = rand() % len;
        data[j] = 1;
        sum += data[j];
    }
    timeEnd = std::chrono::high_resolution_clock::now();
    timeDuration = timeEnd - timeStart;
    timeMilis = std::chrono::duration_cast<std::chrono::milliseconds>(timeDuration).count();
    printf("Time: %.d ms", timeMilis);
    delete [] data;
}
