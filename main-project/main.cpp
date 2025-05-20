#include <iostream>
#include <iomanip>

using namespace std;

#include "runner_subscription.h"
#include "file_reader.h"
#include "constants.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №1. Результат марафона\n";
    cout << "Автор: Пичев Владислав\n\n";
    cout << "Группа: 24ИСиТ1д";

    runner_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;

    try
    {
        read("data.txt", subscriptions, size);
        cout << "***** Результаты марафона *****\n\n";

        for (int i = 0; i < size; i++)
        {
            /********** вывод бегуна **********/
            cout << "Бегун...........: ";
            cout << subscriptions[i]->runner.last_name << " ";
            cout << subscriptions[i]->runner.first_name[0] << ". ";
            cout << subscriptions[i]->runner.middle_name[0] << ".\n";

            /********** вывод клуба **********/
            cout << "Клуб............: ";
            cout << subscriptions[i]->club << '\n';

            /********** вывод времени старта **********/
            cout << "Время старта....: ";
            cout << setw(2) << setfill('0') << subscriptions[i]->start.hour << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->start.minute << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->start.second << '\n';

            /********** вывод времени финиша **********/
            cout << "Время финиша....: ";
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.hour << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.minute << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.second << '\n';

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
