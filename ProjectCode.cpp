#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Event {
protected:
    int eventID;
    string title;
    string date;
    string venue;

public:
    Event(int id, string t, string d, string v) {
        eventID = id;
        title = t;
        date = d;
        venue = v;
    }

    virtual ~Event() {}

    virtual void displayDetails() = 0;
    virtual void saveToFile() = 0;

    int getID() {
        return eventID;
    }

    string getDate() {
        return date;
    }
                                                                                                                                                
    int getDateNumeric() {  
        if (date.length() < 10) return 0;
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));
        return (year * 10000) + (month * 100) + day;                                     
    }
};


class Hackathon : public Event {
private:
    int prizePool;
    int maxTeamSize;

public:
    Hackathon(int id, string t, string d, string v, int prize, int teamSize) 
        : Event(id, t, d, v) {
        prizePool = prize;
        maxTeamSize = teamSize;
    }

    void displayDetails() override {
        cout << "\n[HACKATHON]" << endl;
        cout << "ID: " << eventID << endl;
        cout << "Title: " << title << endl;
        cout << "Date: " << date << endl;
        cout << "Venue: " << venue << endl;
        cout << "Prize Pool: $" << prizePool << endl;
        cout << "Max Team Size: " << maxTeamSize << endl;
        
    }

    void saveToFile() override {
        ofstream outFile("events.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "H," << eventID << "," << title << "," << date << "," << venue << "," << prizePool << "," << maxTeamSize << endl;
            outFile.close();
        }
    }
};

class ClubEvent : public Event {
private:
    string clubName;
    double entryFee;

public:
    ClubEvent(int id, string t, string d, string v, string club, double fee) 
        : Event(id, t, d, v) {
        clubName = club;
        entryFee = fee;
    }

    void displayDetails() override {
        cout << "\n[CLUB EVENT]" << endl;
        cout << "ID: " << eventID << endl;
        cout << "Title: " << title << endl;
        cout << "Date: " << date << endl;
        cout << "Venue: " << venue << endl;
        cout << "Club Name: " << clubName << endl;
        cout << "Entry Fee: $" << entryFee << endl;
        cout << "----------------------------------------" << endl;
    }

    void saveToFile() override {
        ofstream outFile("events.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "C," << eventID << "," << title << "," << date << "," << venue << "," << clubName << "," << entryFee << endl;
            outFile.close();
        }
    }
};

class EventManager {
private:
    Event* events[100]; 
    int eventCount;

    void merge(Event* arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Event** L = new Event*[n1];
        Event** R = new Event*[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i]->getDateNumeric() <= R[j]->getDateNumeric()) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSort(Event* arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }


    void mergeByID(Event* arr[], int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Event** L = new Event*[n1];
        Event** R = new Event*[n2];

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i]->getID() <= R[j]->getID()) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    void mergeSortByID(Event* arr[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortByID(arr, left, mid);
            mergeSortByID(arr, mid + 1, right);
            mergeByID(arr, left, mid, right);
        }
    }

    void sortEvents() {
        if (eventCount > 1) {
            mergeSort(events, 0, eventCount - 1);
        }
    }

public:
    EventManager() {
        eventCount = 0;
        loadEventsFromFile();
    }

    void addEvent(Event* newEvent, bool save = true) {
        if (eventCount < 100) {
            events[eventCount] = newEvent;
            eventCount++;
            sortEvents(); 
            
            if (save) {
                newEvent->saveToFile();
                cout << "\n[Success] Event added successfully!" << endl;
            }
        } else {
            cout << "\n[Error] Event list is full!" << endl;
        }
    }

    void loadEventsFromFile() {
        ifstream inFile("events.txt");
        if (!inFile.is_open()) return;

        string type;
        int id, prize, teamSize;
        string title, date, venue, club;
        double fee;
        char comma;

        while (inFile >> type) {
            if (type.rfind("H,", 0) == 0) {
                
            }
        }
        inFile.close();
    }

    void displayAllEvents() {
        if (eventCount == 0) {
            cout << "\nNo events found." << endl;
            return;
        }

        cout << "\n=== ALL EVENTS ===" << endl;
        for (int i = 0; i < eventCount; i++) {
            events[i]->displayDetails();
        }
    }

    void searchEvent(int id) {
        if (eventCount == 0) {
            cout << "\n[Error] Event ID " << id << " not found." << endl;
            return;
        }

        Event** temp = new Event*[eventCount];
        for (int i = 0; i < eventCount; i++) {
            temp[i] = events[i];
        }

        mergeSortByID(temp, 0, eventCount - 1);

        int low = 0, high = eventCount - 1;
        int foundIndex = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (temp[mid]->getID() == id) {
                foundIndex = mid;
                break;
            } else if (temp[mid]->getID() < id) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        if (foundIndex != -1) {
            cout << "\n[Found Match]";
            temp[foundIndex]->displayDetails();
        } else {
            cout << "\n[Error] Event ID " << id << " not found." << endl;
        }

        delete[] temp;
    }

    bool eventExists(int id) {
        for (int i = 0; i < eventCount; i++) {
            if (events[i]->getID() == id) return true;
        }
        return false;
    }

    ~EventManager() {
        for (int i = 0; i < eventCount; i++) {
            delete events[i];
        }
    }
};

bool authenticateAdmin() {
    string password;
    cout << "Enter Admin Password (admin123): ";
    cin >> password;
    if (password == "admin123") {
        cout << "\n[Access Granted]" << endl;
        return true;
    }
    cout << "\n[Access Denied] Wrong Password." << endl;
    return false;
}

void registerStudent(string studentID, int eventID) {
    ofstream outFile("registrations.txt", ios::app);
    if (outFile.is_open()) {
        outFile << studentID << "," << eventID << endl;
        outFile.close();
        cout << "\n[Success] Registered for Event ID " << eventID << "!" << endl;
    }
}

void adminMenu(EventManager& manager) {
    int choice;
    do {
        cout << "\n--- ADMIN MENU ---" << endl;
        cout << "1. Add Hackathon" << endl;
        cout << "2. Add Club Event" << endl;
        cout << "3. View All Events" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            int id;
            string title, date, venue;

            cout << "Enter ID: ";
            cin >> id;

            if (manager.eventExists(id)) {
                cout << "ID already exists!" << endl;
                continue;
            }

            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Date (DD/MM/YYYY): ";
            getline(cin, date);
            cout << "Enter Venue: ";
            getline(cin, venue);

            if (choice == 1) {
                int prize, teamSize;
                cout << "Enter Prize Pool: ";
                cin >> prize;
                cout << "Enter Max Team Size: ";
                cin >> teamSize;
                manager.addEvent(new Hackathon(id, title, date, venue, prize, teamSize));
            } else {
                string club;
                double fee;
                cout << "Enter Club Name: ";
                cin >> club;
                cout << "Enter Entry Fee: ";
                cin >> fee;
                manager.addEvent(new ClubEvent(id, title, date, venue, club, fee));
            }
        } else if (choice == 3) {
            manager.displayAllEvents();
        }
    } while (choice != 4);
}

void studentMenu(EventManager& manager) {
    string studentID;
    cout << "Enter your Student ID to login: ";
    cin >> studentID;

    int choice;
    do {
        cout << "\n--- STUDENT MENU ---" << endl;
        cout << "1. View Upcoming Events" << endl;
        cout << "2. Search Event by ID" << endl;
        cout << "3. Register for Event" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            manager.displayAllEvents();
        } else if (choice == 2) {
            int id;
            cout << "Enter Event ID: ";
            cin >> id;
            manager.searchEvent(id);
        } else if (choice == 3) {
            int id;
            cout << "Enter Event ID to register: ";
            cin >> id;
            if (manager.eventExists(id)) {
                registerStudent(studentID, id);
            } else {
                cout << "Event ID not found." << endl;
            }
        }
    } while (choice != 4);
}


int main() {
    EventManager manager;
    int choice;

    do {
        cout << "\n--CAMPUS EVENT PORTAL--" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Student Portal" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (authenticateAdmin()) {
                adminMenu(manager);
            }
        } else if (choice == 2) {
            studentMenu(manager);
        }
    } while (choice != 3);

    return 0;
}