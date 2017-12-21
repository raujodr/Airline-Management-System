#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>

using namespace std;

class Flight{
public:
    int flightnumber;
    string departure;
    string destination;
    int flighttime;
};

vector<int> flightnumberforairport(multimap<string, int> m, string s){
    vector<int> res;
    multimap<string, int>::iterator begin = m.lower_bound(s);
    multimap<string, int>::iterator end = m.upper_bound(s);
    while (begin != end)
        res.push_back((*begin++).second);
    return res;
}

void swapped(Flight *a, Flight *b){
    Flight temp = *a;
    *a = *b;
    *b = temp;
}

void selectionsort(vector<Flight> v, int size){
    for (int i = 0; i < size - 1; i++){
        int min_index = i;
        for (int j = i + 1; j < size; j++)
            if (v[j].flighttime < v[i].flighttime)
                min_index = j;
        swapped(&v[i], &v[min_index]);
    }
}

void merged(vector<Flight> v, int low, int med, int high){
    int n1 = med - low + 1, n2 = high - med;
    vector<Flight> v2(v.begin(), v.begin() + n1), v3(v.end() - n2, v.end());
    int i = 0, j = 0, k = low;
    
    while (i < n1 && j < n2) {
        if (v2[i].flighttime < v3[j].flighttime)
            v[k++] = v2[i++];
        else
            v[k++] = v3[j++];
    }
    while (i < n1)
        v[k++] = v2[i++];
    while (j < n2)
        v[k++] = v3[j++];
}

void mergesort(vector<Flight> v, int low, int high){
    if (low < high){
        int med = low + (high - low) / 2;

        mergesort(v, low, med);
        mergesort(v, med + 1, high);
        merged(v, low, med, high);
    }
}

int partitioned(vector<Flight> v, int low, int high){
    int pivot = v[high].flighttime;
    int i = low - 1;
    for (int j = 0; j < high - 1; j++)
        if (v[j].flighttime < pivot)
            swapped(&v[++i], &v[j]);
    swapped(&v[++i], &v[high]);
    return i;
}

void quicksort(vector<Flight> v, int low, int high){
    if (low < high){
        int pi = partitioned(v, low, high);
        quicksort(v, low, pi - 1);
        quicksort(v, pi + 1, high);
    }
}

void insertsort(vector<Flight> v, int size){
    for (int i = 1; i < size; i++) {
        auto temp = v[i].flighttime;
        int j = i - 1;
        while (j >= 0)
            if (v[j].flighttime > temp){
                v[j + 1] = v[j];
                j--;
            }
        v[++j] = v[i];
    }
}

void bubblesort(vector<Flight> v, int size){
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (v[j].flighttime > v[j + 1].flighttime)
                swapped(&v[j], &v[j + 1]);
}

int main(){
    ifstream file("HW4Data.txt");
    
    map<int, string> flightnumber_to_data;
    multimap<string, int> departure_to_flightnumber;
    multimap<string, int> destination_to_flightnumber;
    vector<Flight> v;
    
    while (!file.eof()) {
        Flight data;
        file >> data.flightnumber >> data.departure >> data.departure >> data.flighttime;
        flightnumber_to_data[data.flightnumber] = data.departure + " " + data.destination + " " + to_string(data.flighttime);
        departure_to_flightnumber.insert(pair<string, int>(data.departure, data.flightnumber));
        destination_to_flightnumber.insert(make_pair(data.destination, data.flightnumber));
        v.push_back(data);
    }
    file.close();
    int size = (int)v.size();
    
    while (1) {
        cout << "Please choose the option from the menu.\n" << "(A) Find associated flight number with the departure airport\n" << "(B) Find associated flight number with the destination airport\n" << "(C) Exit\n";
        char option;
        cin >> option;
        switch (option) {
            case 'a':
            case 'A':
            {
                cout << "Please enter the departure airport: ";
                string s;
                cin >> s;
                vector<int> res = flightnumberforairport(departure_to_flightnumber, s);
                for (auto i: res)
                    cout << i << " ";
                cout << "\n";
            }
                break;
            
            case 'b':
            case 'B':
            {
                cout << "Please enter the destination airport: ";
                string s;
                cin >> s;
                vector<int> res = flightnumberforairport(departure_to_flightnumber, s);
                for (auto i: res)
                    cout << i << " ";
            }
                break;
            
            case 'c':
            case 'C':
            {
                vector<Flight> v2 = v;
                selectionsort(v2, size);
                
                v2 = v;
                mergesort(v2, 0, size - 1);
                
                v2 = v;
                quicksort(v2, 0, size - 1);
                
                v2 = v;
                insertsort(v2, size);
                
                v2 = v;
                bubblesort(v2, size);
            }
                break;
            
            case 'd':
            case 'D':
                return 0;
                
            default:
                cout << "Please re-enter the correct option.\n";
        }
    }
}