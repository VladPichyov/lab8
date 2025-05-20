#include <iostream>
#include <iomanip>

using namespace std;

#include "runner_subscription.h"
#include "file_reader.h"
#include "constants.h"

// Фильтрация массива по заданному критерию
runner_subscription** filter_subscriptions(
    runner_subscription* array[],
    int size,
    bool (*check)(runner_subscription* element),
    int& result_size
) {
    runner_subscription** filtered = new runner_subscription * [size];
    result_size = 0;

    for (int i = 0; i < size; i++) {
        if (check(array[i])) {
            filtered[result_size++] = array[i];
        }
    }

    return filtered;
}

// Фильтр 1: бегуны, завершившие марафон менее чем за 3 часа
bool is_fast_runner(runner_subscription* element) {
    int finish_time = element->finish.hour * 3600 + element->finish.minute * 60 + element->finish.second;
    int start_time = element->start.hour * 3600 + element->start.minute * 60 + element->start.second;

    return (finish_time - start_time) < 3 * 3600; // менее 3 часов
}

// Фильтр 2: бегуны, стартовавшие до 9:00 утра
bool is_morning_runner(runner_subscription* element) {
    return element->start.hour < 9;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Лабораторная работа №8. GIT\n";
    cout << "Вариант №1. Результат марафона\n";
    cout << "Автор: Пичев Владислав\n\n";
    cout << "Группа: 24ИСиТ1д\n";

    runner_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;

    try
    {
        read("data.txt", subscriptions, size);
        cout << "***** Все результаты марафона *****\n\n";

        for (int i = 0; i < size; i++)
        {
            cout << "Бегун...........: ";
            cout << subscriptions[i]->runner.last_name << " ";
            cout << subscriptions[i]->runner.first_name[0] << ". ";
            cout << subscriptions[i]->runner.middle_name[0] << ".\n";

            cout << "Время старта....: ";
            cout << setw(2) << setfill('0') << subscriptions[i]->start.hour << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->start.minute << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->start.second << '\n';

            cout << "Время финиша....: ";
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.hour << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.minute << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.second << '\n';

            cout << '\n';
        }

        // Выбор критерия отбора
        int choice;
        cout << "Выберите критерий отбора:\n";
        cout << "1 - Бегуны, завершившие марафон менее чем за 3 часа\n";
        cout << "2 - Бегуны, стартовавшие до 9:00 утра\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        bool (*filter_function)(runner_subscription*);
        filter_function = (choice == 1) ? is_fast_runner : is_morning_runner;

        // Фильтрация списка
        int filtered_size;
        runner_subscription** filtered_runners = filter_subscriptions(subscriptions, size, filter_function, filtered_size);

        cout << "\n***** Отфильтрованные бегуны *****\n\n";
        for (int i = 0; i < filtered_size; i++)
        {
            cout << "Бегун...........: ";
            cout << filtered_runners[i]->runner.last_name << " ";
            cout << filtered_runners[i]->runner.first_name[0] << ". ";
            cout << filtered_runners[i]->runner.middle_name[0] << ".\n";

            cout << "Время старта....: ";
            cout << setw(2) << setfill('0') << filtered_runners[i]->start.hour << ':';
            cout << setw(2) << setfill('0') << filtered_runners[i]->start.minute << ':';
            cout << setw(2) << setfill('0') << filtered_runners[i]->start.second << '\n';

            cout << '\n';
        }

        delete[] filtered_runners;

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
