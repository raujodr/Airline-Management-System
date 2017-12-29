#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Flight{
public:
    int flightnumber;
    string departure;
    string destination;
    int flighttime;
};

vector<int> flightnumberforairport(multimap<string, int> m, string s1){
    vector<int> res;
    string s2 = s1;
    for (int i = 0; i < s1.size(); i++)
        s2[i] = toupper(s1[i]);
    cout << "s2 size: " << s2.size() << "\n";
    multimap<string, int>::iterator begin = m.lower_bound(s2);
    multimap<string, int>::iterator end = m.upper_bound(s2);
    while (begin != end){
        res.push_back(begin->second);
        begin++;
    }
    return res;
}

void swapped(Flight *a, Flight *b){
    Flight temp = *a;
    *a = *b;
    *b = temp;
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

void mergesort(vector<Flight> &v, int low, int high){
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

void quicksort(vector<Flight> &v, int low, int high){
    if (low < high){
        int pi = partitioned(v, low, high);
        quicksort(v, low, pi - 1);
        quicksort(v, pi + 1, high);
    }
}

void selectionsort(vector<Flight> &v, int size){
    for (int i = 0; i < size - 1; i++){
        int min_index = i;
        for (int j = i + 1; j < size; j++)
            if (v[j].flighttime < v[i].flighttime)
                min_index = j;
        swapped(&v[i], &v[min_index]);
    }
}

void insertsort(vector<Flight> &v, int size){
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

void bubblesort(vector<Flight> &v, int size){
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (v[j].flighttime > v[j + 1].flighttime)
                swapped(&v[j], &v[j + 1]);
}

void print(vector<Flight> v){
    for (auto i: v)
        cout << "No. " << i.flightnumber << " from " << i.departure << " to " << i.destination << " takes " << i.flighttime << " minutes.\n";
}

int main(){
    ifstream file("Data.txt");
    
    map<int, string> flightnumber_to_data;
    multimap<string, int> departure_to_flightnumber;
    multimap<string, int> destination_to_flightnumber;
    vector<Flight> v;
    Flight data;
    
    while (!file.eof()) {
        file >> data.flightnumber >> data.departure >> data.destination >> data.flighttime;
        v.push_back(data);
        flightnumber_to_data[data.flightnumber] = data.departure + " " + data.destination + " " + to_string(data.flighttime);
        departure_to_flightnumber.insert(pair<string, int>(data.departure, data.flightnumber));
        destination_to_flightnumber.insert(make_pair(data.destination, data.flightnumber));
    }
    file.close();
    int size = (int)v.size();
    
    char option = '0';
    while (tolower(option) != 'd') {
        cout << "Please choose the option from the menu.\n" << "(A) Find associated flight number with the departure airport\n" << "(B) Find associated flight number with the destination airport\n" << "(C) Sort according to flight time\n" << "(D) Exit\n";
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
                char option2 = '0';
                while (option2 != '6'){
                    cout << "Please choose the sorting option.\n" << "(1) Mergesort\n" << "(2) Quicksort\n" << "(3) Selectionsort\n" << "(4) Insertionsort\n" << "(5) Bubblesort\n" << "(6) Back to previous menu\n";
                    cin >> option2;
                    switch (option2) {
                        case '1':
                        {
                            auto start = high_resolution_clock::now();
                            mergesort(v, 0, size - 1);
                            auto end = high_resolution_clock::now();
                            duration<double> elapsed = end - start;
                            print(v);
                            cout << "Elapsed time: " << elapsed.count() << "s.\n";
                        }
                            break;
                        
                        case '2':
                        {
                            auto start = high_resolution_clock::now();
                            quicksort(v, 0, size - 1);
                            auto end = high_resolution_clock::now();
                            duration<double> elapsed = end - start;
                            print(v);
                            cout << "Elapsed time: " << elapsed.count() << "s.\n";
                        }
                            break;
                        
                        case '3':
                        {
                            auto start = chrono::high_resolution_clock::now();
                            selectionsort(v, size);
                            auto end = chrono::high_resolution_clock::now();
                            duration<double> elapsed = end - start;
                            print(v);
                            cout << "Elapsed time: " << elapsed.count() << "s.\n";
                        }
                            break;
                        
                        case '4':
                        {
                            auto start = chrono::high_resolution_clock::now();
                            insertsort(v, size);
                            auto end = chrono::high_resolution_clock::now();
                            duration<double> elapsed = end - start;
                            print(v);
                            cout << "Elapsed time: " << elapsed.count() << "s.\n";
                        }
                            break;
                        
                        case '5':
                        {
                            auto start = chrono::high_resolution_clock::now();
                            bubblesort(v, size);
                            auto end = chrono::high_resolution_clock::now();
                            duration<double> elapsed = end - start;
                            print(v);
                            cout << "Elapsed time: " << elapsed.count() << "s.\n";
                        }
                            break;
                     
                        case '6':
                            break;
                        
                        default:
                            cout << "Please re-enter the correct option.\n";
                    }
                }
            }
                break;
            
            case 'd':
            case 'D':
                break;
                
            default:
                cout << "Please re-enter the correct option.\n";
        }
    }
    return 0;
}