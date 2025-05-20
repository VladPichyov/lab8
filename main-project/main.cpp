#include <iostream>
#include <iomanip>

using namespace std;

#include "runner_subscription.h"
#include "file_reader.h"
#include "constants.h"

// ���������� ������� �� ��������� ��������
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

// ������ 1: ������, ����������� ������� ����� ��� �� 3 ����
bool is_fast_runner(runner_subscription* element) {
    int finish_time = element->finish.hour * 3600 + element->finish.minute * 60 + element->finish.second;
    int start_time = element->start.hour * 3600 + element->start.minute * 60 + element->start.second;

    return (finish_time - start_time) < 3 * 3600; // ����� 3 �����
}

// ������ 2: ������, ������������ �� 9:00 ����
bool is_morning_runner(runner_subscription* element) {
    return element->start.hour < 9;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "������������ ������ �8. GIT\n";
    cout << "������� �1. ��������� ��������\n";
    cout << "�����: ����� ���������\n\n";
    cout << "������: 24����1�\n";

    runner_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;

    try
    {
        read("data.txt", subscriptions, size);
        cout << "***** ��� ���������� �������� *****\n\n";

        for (int i = 0; i < size; i++)
        {
            cout << "�����...........: ";
            cout << subscriptions[i]->runner.last_name << " ";
            cout << subscriptions[i]->runner.first_name[0] << ". ";
            cout << subscriptions[i]->runner.middle_name[0] << ".\n";

            cout << "����� ������....: ";
            cout << setw(2) << setfill('0') << subscriptions[i]->start.hour << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->start.minute << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->start.second << '\n';

            cout << "����� ������....: ";
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.hour << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.minute << ':';
            cout << setw(2) << setfill('0') << subscriptions[i]->finish.second << '\n';

            cout << '\n';
        }

        // ����� �������� ������
        int choice;
        cout << "�������� �������� ������:\n";
        cout << "1 - ������, ����������� ������� ����� ��� �� 3 ����\n";
        cout << "2 - ������, ������������ �� 9:00 ����\n";
        cout << "��� �����: ";
        cin >> choice;

        bool (*filter_function)(runner_subscription*);
        filter_function = (choice == 1) ? is_fast_runner : is_morning_runner;

        // ���������� ������
        int filtered_size;
        runner_subscription** filtered_runners = filter_subscriptions(subscriptions, size, filter_function, filtered_size);

        cout << "\n***** ��������������� ������ *****\n\n";
        for (int i = 0; i < filtered_size; i++)
        {
            cout << "�����...........: ";
            cout << filtered_runners[i]->runner.last_name << " ";
            cout << filtered_runners[i]->runner.first_name[0] << ". ";
            cout << filtered_runners[i]->runner.middle_name[0] << ".\n";

            cout << "����� ������....: ";
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
