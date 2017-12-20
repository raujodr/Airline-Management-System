#include <iostream>
#include <vector>
#include <map>
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

int main(){
    ifstream file("HW4Data.txt");
    
    map<int, string> flightnumber_to_data;
    multimap<string, int> departure_to_flightnumber;
    multimap<string, int> destination_to_flightnumber;
    

    while (!file.eof()) {
        Flight data;
        file >> data.flightnumber >> data.departure >> data.departure >> data.flighttime;
        flightnumber_to_data[data.flightnumber] = data.departure + " " + data.destination + " " + to_string(data.flighttime);
        departure_to_flightnumber.insert(pair<string, int>(data.departure, data.flightnumber));
        destination_to_flightnumber.insert(make_pair(data.destination, data.flightnumber));
    }
    file.close();
    
    string s;
    cout << "Please enter the departure airport: ";
    cin >> s;
    vector<int> res = flightnumberforairport(departure_to_flightnumber, s);
    for (auto i: res)
        cout << i << " ";
    
    cout << "Please enter the destination airport: ";
    cin >> s;
    res = flightnumberforairport(departure_to_flightnumber, s);
    for (auto i: res)
        cout << i << " ";
    
    return 0;
}
