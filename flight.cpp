#include "flight.h"

Flight::Time::Time()
{
}

Flight::Time::Time(const ushort& hour, const ushort& min)
{
    if(hour < 24)
        this->hour = hour;
    if(min < 60)
        this->min = min;
}

bool Flight::Time::operator < (const Time& other)
{
    if(this->hour == other.hour)
        return this->min < other.min;
    else return this->hour < other.hour;
}

bool Flight::Time::operator > (const Time& other)
{
    if(this->hour == other.hour)
        return  this->min > other.min;
    else return this->hour > other.hour;
}

bool Flight::Time::operator == (const Time& other)
{
    if (this->min != other.min)
        return false;
    else return this->hour == other.hour;
}

 void Flight::Time::operator = (const Time& other)
 {
     this->hour = other.hour;
     this->min = other.min;
 }

Flight:: Flight( const ushort &number,
                 const string &destination,
                 const ushort &start_hour,
                 const ushort &start_min,
                 const ushort &finish_hour,
                 const ushort &finish_min) : start(start_hour, start_min), finish (finish_hour, finish_min)
{
    this->number = number;
    this->destination = destination;
}
Flight::Flight()
{
}

void read_timetable(string path, vector<Flight> &timetable)
{
    ifstream fin (path, ios::binary);
    if(!fin.is_open())
    {
       throw "error of reading file";
    }
    else
    {
        Flight temp;
        while(fin.read((char *)&temp, sizeof(Flight)))
        {
              timetable.emplace_back(temp);
        }
    }
    fin.close();
}

void write_timetable(string path, vector<Flight>& timetable)
{
    ofstream fout(path, ios::binary);
    if(!fout.is_open())
    {
        throw "error of reading file";
    }
    else
    {
        for(size_t i = 0; i < timetable.size(); i++)
            fout.write((char *)&timetable[i], sizeof (Flight));
        fout.close();
    }
}

void add_flight(vector<Flight>& timetable, const Flight& flight)
{
    timetable.emplace_back(flight);
}

ullong selectionSort(vector<Flight> &timetable)
{
    unsigned long long min;
    Flight temp;
    ullong last = 0;
    for(size_t i = 0; i<timetable.size()-1; i++)
    {
        min = i;
        for(size_t j = i+1; j < timetable.size(); j++)
        {
            if(timetable[j].finish < timetable[min].finish)
            {
                min = j;
                last++;
            }
        }
        temp = timetable[i];
        timetable[i] = timetable[min];
        timetable[min] = temp;
    }
    return last;
}

void quickSort(vector<Flight> &timetable,  ullong left, ullong right)
{
    ullong i = left, j = right;
    Flight temp;
    Flight middle = timetable[(left+right)/2];

    while(i<=j)
    {
        while (timetable[i].finish < middle.finish)
            i++;
        while (timetable[i].finish > middle.finish)
            j--;

        if(i<=j)
        {
            temp = timetable[i];
            timetable[i] = timetable[j];
            timetable[j] = temp;
            i++;
            j--;
        }
    };

if (left < j)
    quickSort(timetable, left, j);
if (i < right)
    quickSort(timetable, i, right);
}

llong binarySearch(vector<Flight> &timetable, llong left, llong right, Flight::Time key)
{
    llong middle = 0;
    while(true)
    {
        if(key < timetable[middle].finish)
            right = middle - 1;
        else if (key > timetable[middle].finish)
            left = middle + 1;
        else
            return middle;

        if (left > right)
            return -1;
    }
}
