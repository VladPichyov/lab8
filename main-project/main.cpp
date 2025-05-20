#include <iostream>

using namespace std;

#include "runner_subscription.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №1. результат марафона\n";
    cout << "Автор: Пичев Владислав\n";
    runner_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;
    try
    {
        read("data.txt", subscriptions, size);
        for (int i = 0; i < size; i++)
        {
            cout << subscriptions[i]->runner.last_name;
            cout << subscriptions[i]->runner.first_name;
            cout << subscriptions[i]->runner.middle_name << " ";
            cout << subscriptions[i]->start.hour << ' ';
            cout << subscriptions[i]->start.minute << ' ';
            cout << subscriptions[i]->start.second << " ";
            cout << subscriptions[i]->finish.hour << ' ';
            cout << subscriptions[i]->finish.minute << ' ';
            cout << subscriptions[i]->finish.second << " ";
            cout << subscriptions[i]->club << '\n';
            cout << '\n';
        }
        for (int i = 0; i < size; i++)
        {
            delete subscriptions[i];
        }
    }
    catch (const char* error)
    {
        cout << error << '\n';
    }
    return 0;
}