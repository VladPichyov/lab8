#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/runner_subscription.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RunnerTests
{
    TEST_CLASS(ProcessFunctionTests)
    {
    public:
        // Вспомогательная функция создания бегуна с заполнением всех полей
        runner_subscription* create_full_runner(
            int number,
            const char* firstName,
            const char* middleName,
            const char* lastName,
            int startH, int startM, int startS,
            int finishH, int finishM, int finishS,
            const char* club,
            int resultH, int resultM, int resultS)
        {
            runner_subscription* runner = new runner_subscription;
            runner->number = number;

            strncpy_s(runner->runner.first_name, firstName, MAX_STRING_SIZE);
            strncpy_s(runner->runner.middle_name, middleName, MAX_STRING_SIZE);
            strncpy_s(runner->runner.last_name, lastName, MAX_STRING_SIZE);

            runner->start.hour = startH;
            runner->start.minute = startM;
            runner->start.second = startS;

            runner->finish.hour = finishH;
            runner->finish.minute = finishM;
            runner->finish.second = finishS;

            strncpy_s(runner->club, club, MAX_STRING_SIZE);

            runner->result.hour = resultH;
            runner->result.minute = resultM;
            runner->result.second = resultS;

            return runner;
        }

        // Упрощенная функция создания (только для тестирования process())
        runner_subscription* create_runner(int resultH, int resultM, int resultS)
        {
            return create_full_runner(
                1, "Test", "Test", "Test",
                0, 0, 0,
                0, 0, 0,
                "TestClub",
                resultH, resultM, resultS);
        }

        void cleanup(runner_subscription* runners[], int count, char* result)
        {
            for (int i = 0; i < count; i++)
                delete runners[i];
            delete[] result;
        }

        TEST_METHOD(TestBasicFunctionality)
        {
            runner_subscription* runners[3] = {
                create_runner(2, 45, 30),
                create_runner(1, 59, 59),
                create_runner(3, 0, 0)
            };

            char* result = process(runners, 3);
            Assert::AreEqual("01:59:59", result);

            cleanup(runners, 3, result);
        }

        TEST_METHOD(TestTimeFormatting)
        {
            runner_subscription* runners[3] = {
                create_runner(0, 5, 9),    // 00:05:09
                create_runner(1, 9, 5),    // 01:09:05
                create_runner(0, 0, 1)     // 00:00:01
            };

            char* result = process(runners, 3);
            Assert::AreEqual("00:00:01", result);

            cleanup(runners, 3, result);
        }

        TEST_METHOD(TestEqualHoursDifferentMinutes)
        {
            runner_subscription* runners[2] = {
                create_runner(2, 45, 30),
                create_runner(2, 30, 45)
            };

            char* result = process(runners, 2);
            Assert::AreEqual("02:30:45", result);

            cleanup(runners, 2, result);
        }

        TEST_METHOD(TestEqualHoursMinutesDifferentSeconds)
        {
            runner_subscription* runners[2] = {
                create_runner(2, 30, 45),
                create_runner(2, 30, 30)
            };

            char* result = process(runners, 2);
            Assert::AreEqual("02:30:30", result);

            cleanup(runners, 2, result);
        }

        TEST_METHOD(TestSingleRunner)
        {
            runner_subscription* runners[1] = {
                create_runner(1, 30, 0)
            };

            char* result = process(runners, 1);
            Assert::AreEqual("01:30:00", result);

            cleanup(runners, 1, result);
        }

        TEST_METHOD(TestFullRunnerData)
        {
            runner_subscription* runners[2] = {
                create_full_runner(
                    101, "Иван", "Иванович", "Иванов",
                    10, 0, 0, 12, 30, 0,
                    "Спартак", 2, 30, 0),
                create_full_runner(
                    102, "Петр", "Петрович", "Петров",
                    10, 0, 0, 11, 45, 30,
                    "Динамо", 1, 45, 30)
            };

            char* result = process(runners);
        }