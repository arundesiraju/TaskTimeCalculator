#include <iostream>
#include <time.h>
#include <string>
#include <map>

using namespace std;

int InitializeTaskTimer(string uniquetimerName, int *uniquetimerID);
int StartTaskTimer(int uniquetimerID);
int StopTaskTimer(int uniquetimerID);

void TaskA();
void TaskB();
void TaskC();

map<string, int> g_timerMap;
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

    cout << "TaskA" << endl;
}

void TaskB()
{
    int timerID = 0;
    InitializeTaskTimer("TaskB", &timerID);

    cout << "TaskB" << endl;
}

void TaskC()
{
    int timerID = 0;
    InitializeTaskTimer("TaskC", &timerID);

    cout << "TaskC" << endl;
}

int InitializeTaskTimer(string uniquetimerName, int *uniquetimerID)
{
    if(g_timerMap.find(uniquetimerName) == g_timerMap.end())
    {
        g_timerID++;
        g_timerMap.insert(pair<string, int>(uniquetimerName, g_timerID));
    }
    else
    {
        // do nothing
    }
    
    return 0;
}