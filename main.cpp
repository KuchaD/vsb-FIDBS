#include <iostream>
#include "cHeapTable.h"
#include "cRecordTable.h"

#define TKey int
#define TData int

void test2();
void test1();

using namespace std;
using namespace std::chrono;

int main()
{
    test1();
    printf("\n=======================");
    test2();
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

    printf("\nSize of %d", sizeof(table));
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

    printf("\nSize of %d", sizeof(table));
    delete table;

}

