#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

#include "runner_subscription.h"
#include "file_reader.h"
#include "constants.h"

// Ïðîòîòèïû ôóíêöèé
void bubble_sort(runner_subscription* array[], int size,
    int (*compare)(runner_subscription*, runner_subscription*));
void quick_sort(runner_subscription* array[], int left, int right,
    int (*compare)(runner_subscription*, runner_subscription*));
int compare_by_time(runner_subscription* a, runner_subscription* b);
int compare_by_club_and_name(runner_subscription* a, runner_subscription* b);
void print_runners(runner_subscription* array[], int size);

// Ôóíêöèÿ äëÿ íîðìàëèçàöèè ñòðîêè (óäàëåíèå êàâû÷åê è ïðîáåëîâ)
string normalize_string(const string& str) {
    string result = str;
    // Óäàëÿåì êàâû÷êè
    result.erase(remove(result.begin(), result.end(), '\"'), result.end());
    // Óäàëÿåì ïðîáåëû ïî êðàÿì
    result.erase(0, result.find_first_not_of(" \t\n\r\f\v"));
    result.erase(result.find_last_not_of(" \t\n\r\f\v") + 1);
    return result;
}

// Ôèëüòð 1: ó÷àñòíèêè èç êëóáà "Ñïàðòàê"
bool is_spartak_runner(runner_subscription* element) {
    return normalize_string(element->club) == "Ñïàðòàê";
}

// Ôèëüòð 2: ó÷àñòíèêè, ðåçóëüòàò êîòîðûõ ëó÷øå 2:50:00
bool is_fast_runner(runner_subscription* element) {
    int finish_time = element->finish.hour * 3600 + element->finish.minute * 60 + element->finish.second;
    int start_time = element->start.hour * 3600 + element->start.minute * 60 + element->start.second;
    return (finish_time - start_time) < (2 * 3600 + 50 * 60);
}

// Ôóíêöèÿ ôèëüòðàöèè
runner_subscription** filter_subscriptions(
    runner_subscription* array[],
    int size,
    bool (*check)(runner_subscription*),
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

// Ôóíêöèè ñðàâíåíèÿ äëÿ ñîðòèðîâêè
int compare_by_time(runner_subscription* a, runner_subscription* b) {
    int time_a = (a->finish.hour * 3600 + a->finish.minute * 60 + a->finish.second) -
        (a->start.hour * 3600 + a->start.minute * 60 + a->start.second);
    int time_b = (b->finish.hour * 3600 + b->finish.minute * 60 + b->finish.second) -
        (b->start.hour * 3600 + b->start.minute * 60 + b->start.second);
    return time_a - time_b;
}

int compare_by_club_and_name(runner_subscription* a, runner_subscription* b) {
    // Ïðåîáðàçóåì char* â string ïåðåä íîðìàëèçàöèåé
    string clubA = normalize_string(string(a->club));
    string clubB = normalize_string(string(b->club));

    if (clubA != clubB) {
        return clubA.compare(clubB);
    }
    return string(a->runner.last_name).compare(string(b->runner.last_name));
}

// Àëãîðèòìû ñîðòèðîâêè
void bubble_sort(runner_subscription* array[], int size,
    int (*compare)(runner_subscription*, runner_subscription*)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(array[j], array[j + 1]) > 0) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void quick_sort(runner_subscription* array[], int left, int right,
    int (*compare)(runner_subscription*, runner_subscription*)) {
    if (left >= right) return;

    int i = left, j = right;
    runner_subscription* pivot = array[(left + right) / 2];

    while (i <= j) {
        while (compare(array[i], pivot) < 0) i++;
        while (compare(array[j], pivot) > 0) j--;
        if (i <= j) {
            swap(array[i], array[j]);
            i++;
            j--;
        }
    }

    quick_sort(array, left, j, compare);
    quick_sort(array, i, right, compare);
}

// Ôóíêöèÿ âûâîäà ðåçóëüòàòîâ
void print_runners(runner_subscription* array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "Áåãóí...........: "
            << array[i]->runner.last_name << " "
            << array[i]->runner.first_name << " "
            << array[i]->runner.middle_name << '\n';
        cout << "Êëóá............: " << array[i]->club << '\n';

        cout << "Âðåìÿ ñòàðòà....: "
            << setw(2) << setfill('0') << array[i]->start.hour << ':'
            << setw(2) << setfill('0') << array[i]->start.minute << ':'
            << setw(2) << setfill('0') << array[i]->start.second << '\n';

        cout << "Âðåìÿ ôèíèøà....: "
            << setw(2) << setfill('0') << array[i]->finish.hour << ':'
            << setw(2) << setfill('0') << array[i]->finish.minute << ':'
            << setw(2) << setfill('0') << array[i]->finish.second << "\n\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Ëàáîðàòîðíàÿ ðàáîòà ¹8. GIT\n";
    cout << "variant 5155. Ðåçóëüòàò ìàðàôîíà\n";
    cout << "Àâòîð: Ïè÷åâ Âëàäèñëàâ\n\n";
    cout << "Ãðóïïà: 24ÈÑèÒ1ä\n";

    runner_subscription* subscriptions[MAX_FILE_ROWS_COUNT];
    int size;

    try {
        read("data.txt", subscriptions, size);

        while (true) {
            cout << "\nÂûáåðèòå äåéñòâèå:\n";
            cout << "1 - Ôèëüòðàöèÿ ðåçóëüòàòîâ\n";
            cout << "2 - Ñîðòèðîâêà ðåçóëüòàòîâ\n";
            cout << "3 - Âûõîä\n";
            cout << "Âàø âûáîð: ";

            int main_choice;
            cin >> main_choice;

            if (main_choice == 1) {
                // Ôèëüòðàöèÿ
                cout << "\nÂûáåðèòå êðèòåðèé îòáîðà:\n";
                cout << "1 - Ó÷àñòíèêè èç êëóáà \"Ñïàðòàê\"\n";
                cout << "2 - Ó÷àñòíèêè, ïðîáåæàâøèå áûñòðåå 2:50:00\n";
                cout << "Âàø âûáîð: ";

                int filter_choice;
                cin >> filter_choice;

                if (filter_choice < 1 || filter_choice > 2) {
                    cout << "Íåâåðíûé âûáîð!\n";
                    continue;
                }

                int filtered_size;
                runner_subscription** filtered = nullptr;
                string filter_name;

                if (filter_choice == 1) {
                    filtered = filter_subscriptions(subscriptions, size, is_spartak_runner, filtered_size);
                    filter_name = "èç êëóáà \"Ñïàðòàê\"";
                }
                else {
                    filtered = filter_subscriptions(subscriptions, size, is_fast_runner, filtered_size);
                    filter_name = "ñ ðåçóëüòàòîì ëó÷øå 2:50:00";
                }

                if (filtered_size == 0) {
                    cout << "\nÍåò ó÷àñòíèêîâ " << filter_name << "\n";
                }
                else {
                    cout << "\n***** Íàéäåíî " << filtered_size << " ó÷àñòíèêîâ " << filter_name << " *****\n\n";
                    print_runners(filtered, filtered_size);
                }

                delete[] filtered;
            }
            else if (main_choice == 2) {
                // Ñîðòèðîâêà
                cout << "\nÂûáåðèòå ìåòîä ñîðòèðîâêè:\n";
                cout << "1 - Bubble Sort\n";
                cout << "2 - Quick Sort\n";
                cout << "Âàø âûáîð: ";

                int sort_choice;
                cin >> sort_choice;

                cout << "\nÂûáåðèòå êðèòåðèé ñîðòèðîâêè:\n";
                cout << "1 - Ïî âðåìåíè çàáåãà\n";
                cout << "2 - Ïî êëóáó è ôàìèëèè\n";
                cout << "Âàø âûáîð: ";

                int compare_choice;
                cin >> compare_choice;

                if ((sort_choice < 1 || sort_choice > 2) || (compare_choice < 1 || compare_choice > 2)) {
                    cout << "Íåâåðíûé âûáîð!\n";
                    continue;
                }

                if (sort_choice == 1) {
                    bubble_sort(subscriptions, size,
                        (compare_choice == 1) ? compare_by_time : compare_by_club_and_name);
                }
                else {
                    quick_sort(subscriptions, 0, size - 1,
                        (compare_choice == 1) ? compare_by_time : compare_by_club_and_name);
                }

                cout << "\n***** Îòñîðòèðîâàííûå ðåçóëüòàòû *****\n\n";
                print_runners(subscriptions, size);
            }
            else if (main_choice == 3) {
                break;
            }
            else {

                cout << "Íåâåðíûé âûáîð!\n";

                cout << "Íåâåðíûé âûáîð!!\n";
            }
        }

        // Îñâîáîæäåíèå ïàìÿòè
        for (int i = 0; i < size; i++) {
            delete subscriptions[i];
        }
    }
    catch (const char* error) {
        cout << "Îøèáêà: " << error << '\n';
    }

    return 0;
}
