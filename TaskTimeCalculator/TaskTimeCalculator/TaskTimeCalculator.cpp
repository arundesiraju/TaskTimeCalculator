#include <iostream>
#include <chrono>
#include <string>
#include <map>
#include <Windows.h>

using namespace std;

int InitializeTaskTimer(string uniquetimerName, int *uniquetimerID);
int StartTaskTimer(string uniquetimerName, int uniquetimerID);
int StopTaskTimer(string uniquetimerName, int uniquetimerID);
std::chrono::duration<double> CalculateTaskTime(string uniquetimerName, int uniquetimerID);

void TaskA();
void TaskB();
void TaskC();

map<string, int> g_timerMap;
map<string, chrono::time_point<chrono::system_clock>> g_start_times;
map<string, chrono::time_point<chrono::system_clock>> g_stop_times;
map<string, std::chrono::duration<double>> g_durations;

int g_timerID;

int main()
{
    TaskA();
    
    TaskB();
    
    TaskC();
    
    TaskB();
    
    return 0;
}

void TaskA()
{
    int timerID = 0;
    InitializeTaskTimer("TaskA", &timerID);

    StartTaskTimer("TaskA", timerID);

    Sleep(1513);

    StopTaskTimer("TaskA", timerID);
    
    std::chrono::duration<double> taskA_time = CalculateTaskTime("TaskA", timerID);
}

void TaskB()
{
    int timerID = 0;
    InitializeTaskTimer("TaskB", &timerID);

    StartTaskTimer("TaskB", timerID);

    Sleep(2124);

    StopTaskTimer("TaskB", timerID);
    
    std::chrono::duration<double> taskA_time = CalculateTaskTime("TaskB", timerID);
}

void TaskC()
{
    int timerID = 0;
    InitializeTaskTimer("TaskC", &timerID);

    StartTaskTimer("TaskC", timerID);

    Sleep(3754);

    StopTaskTimer("TaskC", timerID);
    
    std::chrono::duration<double> taskA_time = CalculateTaskTime("TaskC", timerID);
}


int InitializeTaskTimer(string uniquetimerName, int *uniquetimerID)
{
    if(g_timerMap.find(uniquetimerName) == g_timerMap.end())
    {
        g_timerID++;
        g_timerMap.insert(pair<string, int>(uniquetimerName, g_timerID));

         *uniquetimerID = g_timerID;
    }
    else
    {
       *uniquetimerID = g_timerMap.find(uniquetimerName)->second;
    }
   
    return 0;
}

int StartTaskTimer (string uniquetimerName, int uniquetimerID)
{
    chrono::time_point<chrono::system_clock> start_time;

    start_time = chrono::system_clock::now();

    g_start_times.insert(pair<string, chrono::time_point<chrono::system_clock>>(uniquetimerName, start_time));

    return 0;
}

int StopTaskTimer (string uniquetimerName, int uniquetimerID)
{
    chrono::time_point<chrono::system_clock> stop_time;

    stop_time = chrono::system_clock::now();

    g_stop_times.insert(pair<string, chrono::time_point<chrono::system_clock>>(uniquetimerName, stop_time));

    return 0;
}

std::chrono::duration<double> CalculateTaskTime(string uniquetimerName, int uniquetimerID)
{
    chrono::time_point<chrono::system_clock> diff_start_time = g_start_times.find(uniquetimerName)->second;
    chrono::time_point<chrono::system_clock> diff_stop_time = g_stop_times.find(uniquetimerName)->second;

    std::chrono::duration<double> diff_time = diff_stop_time - diff_start_time;

    g_durations.insert(pair<string, std::chrono::duration<double>>(uniquetimerName, diff_time));

    return diff_time;
}
