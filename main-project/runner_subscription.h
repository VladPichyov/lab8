#ifndef RUNNER_SUBSCRIPTION_H
#define RUNNER_SUBSCRIPTION_H

#include "constants.h"

struct times
{
	int hour;
	int minute;
	int second;
};

struct person
{
	char first_name[MAX_STRING_SIZE];
	char middle_name[MAX_STRING_SIZE];
	char last_name[MAX_STRING_SIZE];
};

struct runner_subscription
{
	int number;
	person runner;
	times start;
	times finish;
	char club[MAX_STRING_SIZE];
	times result;
};

#endif
#pragma once
