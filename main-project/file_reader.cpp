#include "file_reader.h"
#include "constants.h"

#include <fstream>
#include <cstring>

times convert(char* str)
{
    times result;
    char* context = NULL;
    char* str_number = strtok_s(str, ":", &context);
    result.hour = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.minute = atoi(str_number);
    str_number = strtok_s(NULL, ":", &context);
    result.second = atoi(str_number);
    return result;
}

void read(const char* file_name, runner_subscription* array[], int& size)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        size = 0;
        char tmp_buffer[MAX_STRING_SIZE];
        while (!file.eof())
        {
            runner_subscription* item = new runner_subscription;
            file >> item->number;
            file >> item->runner.last_name;
            file >> item->runner.first_name;
            file >> item->runner.middle_name;
            file >> tmp_buffer;
            item->start = convert(tmp_buffer);
            file >> tmp_buffer;
            item->finish = convert(tmp_buffer);
            file.read(tmp_buffer, 1); // чтения лишнего символа пробела
            file.getline(item->club, MAX_STRING_SIZE);
            int time_finish;
            time_finish = item->finish.hour * 3600 + item->finish.minute * 60 + item->finish.second;
            int time_start;
            time_start = item->start.hour * 3600 + item->start.minute * 60 + item->start.second;
            int time_result;
            time_result = time_finish - time_start;

            item->result.hour = time_result / 3600;
            time_result -= (time_result / 3600) * 3600;

            item->result.minute = time_result / 60;
            time_result -= (time_result / 60) * 60;

            item->result.second = time_result;
            array[size++] = item;
        }
        file.close();
    }
    else
    {
        throw "Ошибка открытия файла";
    }
}