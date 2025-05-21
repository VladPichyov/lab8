#include "processing.h"

using namespace std;
char turn_into_char(int num)
{
	switch (num)
	{
	case 1:
		return '1';
		break;
	case 2:
		return '2';
		break;
	case 3:
		return '3';
		break;
	case 4:
		return '4';
		break;
	case 5:
		return '5';
		break;
	case 6:
		return '6';
		break;
	case 7:
		return '7';
		break;
	case 8:
		return '8';
		break;
	case 9:
		return '9';
		break;
	case 0:
		return '0';
		break;
	}
}
char* process(runner_subscription* array[], int size)
{
	char* result_return = new char[9];

	int* best_result = new int[3] {array[0]->result.hour, array[0]->result.minute, array[0]->result.second};

	for (int i = 1; i < size; i++)
	{
		if (best_result[0] > array[i]->result.hour)
		{
			best_result[0] = array[i]->result.hour;
			best_result[1] = array[i]->result.minute;
			best_result[2] = array[i]->result.second;
		}
		else if (best_result[0] == array[i]->result.hour && best_result[1] > array[i]->result.minute)
		{
			best_result[0] = array[i]->result.hour;
			best_result[1] = array[i]->result.minute;
			best_result[2] = array[i]->result.second;
		}
		else if (best_result[0] == array[i]->result.hour && best_result[1] == array[i]->result.minute && best_result[2] > array[i]->result.second)
		{
			best_result[0] = array[i]->result.hour;
			best_result[1] = array[i]->result.minute;
			best_result[2] = array[i]->result.second;
		}
	}

	result_return[0] = turn_into_char(best_result[0] / 10);
	result_return[1] = turn_into_char(best_result[0] % 10);
	result_return[2] = ':';
	result_return[3] = turn_into_char(best_result[1] / 10);
	result_return[4] = turn_into_char(best_result[1] % 10);
	result_return[5] = ':';
	result_return[6] = turn_into_char(best_result[2] / 10);
	result_return[7] = turn_into_char(best_result[2] % 10);
	result_return[8] = '\0';

	return result_return;
}