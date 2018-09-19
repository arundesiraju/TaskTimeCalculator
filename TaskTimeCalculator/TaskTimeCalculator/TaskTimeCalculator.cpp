#include <iostream>
#include <chrono>
#include <string>
#include <map>
#include <Windows.h>
#include <fstream>
#include <vector>

using namespace std;

int InitializeTaskTimer(string uniquetimerName, int *uniquetimerID);
int StartTaskTimer(string uniquetimerName, int uniquetimerID);
int StopTaskTimer(string uniquetimerName, int uniquetimerID);
int CalculateTaskTime(string uniquetimerName, int uniquetimerID);

void TaskA();
void TaskB();
void TaskC();
void SaveCsvFile();

map<string, int> g_timerMap;
map<string, chrono::time_point<chrono::system_clock>> g_start_times;
map<string, chrono::time_point<chrono::system_clock>> g_stop_times;
map<string, std::chrono::duration<double>> g_durations;
map<string, int> g_iterations;
vector<string> g_tasknames;

int g_timerID;

int main()
{
    TaskA();
    
    TaskB();
    
    TaskC();
    
    TaskB();
    
    SaveCsvFile();

    return 0;
}

void TaskA()
{
    int timerID = 0;
    InitializeTaskTimer("TaskA", &timerID);

    StartTaskTimer("TaskA", timerID);

    Sleep(1513);

    StopTaskTimer("TaskA", timerID);
    
    CalculateTaskTime("TaskA", timerID);
}

void TaskB()
{
    int timerID = 0;
    InitializeTaskTimer("TaskB", &timerID);

    StartTaskTimer("TaskB", timerID);

    Sleep(2124);

    StopTaskTimer("TaskB", timerID);
    
    CalculateTaskTime("TaskB", timerID);
}

void TaskC()
{
    int timerID = 0;
    InitializeTaskTimer("TaskC", &timerID);

    StartTaskTimer("TaskC", timerID);

    Sleep(3754);

    StopTaskTimer("TaskC", timerID);
    
    CalculateTaskTime("TaskC", timerID);
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

    if(g_start_times.find(uniquetimerName) != g_start_times.end())
    {
        g_start_times.erase(uniquetimerName);
    }

    g_start_times.insert(pair<string, chrono::time_point<chrono::system_clock>>(uniquetimerName, start_time));

    return 0;
}

int StopTaskTimer (string uniquetimerName, int uniquetimerID)
{
    chrono::time_point<chrono::system_clock> stop_time;

    stop_time = chrono::system_clock::now();

    if(g_stop_times.find(uniquetimerName) != g_stop_times.end())
    {
        g_stop_times.erase(uniquetimerName);
    }

    g_stop_times.insert(pair<string, chrono::time_point<chrono::system_clock>>(uniquetimerName, stop_time));

    return 0;
}

int CalculateTaskTime(string uniquetimerName, int uniquetimerID)
{
    chrono::time_point<chrono::system_clock> diff_start_time = g_start_times.find(uniquetimerName)->second;
    chrono::time_point<chrono::system_clock> diff_stop_time = g_stop_times.find(uniquetimerName)->second;

    std::chrono::duration<double> diff_time = diff_stop_time - diff_start_time;

    int num_iterations = 1;

    if(g_durations.find(uniquetimerName) != g_durations.end())
    {
        diff_time += g_durations.find(uniquetimerName)->second;
        g_durations.erase(uniquetimerName);

        num_iterations++;
        g_iterations.erase(uniquetimerName);
    }

    g_durations.insert(pair<string, std::chrono::duration<double>>(uniquetimerName, diff_time));
    g_iterations.insert(pair<string, int>(uniquetimerName, num_iterations));

    if (std::find(g_tasknames.begin(), g_tasknames.end(),uniquetimerName)==g_tasknames.end())
        g_tasknames.push_back(uniquetimerName);

    return 0;
}

void SaveCsvFile()
{
    const char* fileName = "timerDetails.csv";
    std::ifstream ifile(fileName);
    bool exists = (bool)ifile;

    ofstream myfile;
    myfile.open (fileName, std::fstream::app);

    if(!exists)
    {   
        myfile << "Task Name,Number of Iterations,Time per Iteration,Total Time,Total Percentage"<<endl;
    }
    
    double TotalTime = 0;
    for(std::vector<string>::size_type i = 0; i != g_tasknames.size(); i++)
    {
        TotalTime += g_durations.find(g_tasknames[i])->second.count();
    }

    for(std::vector<string>::size_type i = 0; i != g_tasknames.size(); i++) 
    {
        int Num_iter = g_iterations.find(g_tasknames[i])->second;
        double Duration = g_durations.find(g_tasknames[i])->second.count();
        double TotalPercentage = 100 * (Duration/TotalTime);

        myfile<<g_tasknames[i]<<","<<Num_iter<<","<<(double)Duration/Num_iter<<","<<Duration<<","<<TotalPercentage<<endl;
        
    }

    myfile.close();
}