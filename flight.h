#pragma once
#ifndef FLIGHT_H
#define FLIGHT_H

#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <QMessageBox>

typedef unsigned short ushort;
typedef long long llong;
typedef unsigned long long ullong;

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ios;

class Flight
{
public:
    struct Time
    {
        Time();
        Time(const ushort& hour,const ushort& min);
        ushort hour;
        ushort min;
        bool operator < (const Time& other);
        bool operator > (const Time& other);
        bool operator == (const Time& other);
        void operator = (const Time& other);
    };

    explicit Flight();
    explicit Flight(const ushort &number,
        const string &destination,
        const ushort &start_hour,
        const ushort &start_min,
        const ushort &finish_hour,
        const ushort &finish_min);

    ushort number;
    string destination;
    Time start;
    Time finish;
};

void read_timetable(string path, vector<Flight>& timetable);
void write_timetable(string path, vector<Flight>& timetable);
void add_flight(vector<Flight>& timetable, const Flight& flight);
ullong selectionSort(vector<Flight> &timetable);
void quickSort(vector<Flight> &timetable, ullong left, ullong right);
llong binarySearch(vector<Flight> &timetable, llong left, llong right, Flight::Time key);

#endif // FLIGHT_H
