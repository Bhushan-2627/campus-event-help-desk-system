#include <iostream>
#include <string>
#include <tuple>
#include <array>
#include <queue>
#include <stack>
#include <iomanip>
#include <limits>
using namespace std;

// DSA Mini Project: Campus Event Registration & Help Desk System
// Data structures: Array, Tuple, Queue, Stack, Singly Linked List
// Sorting algorithms: Bubble Sort, Insertion Sort, Selection Sort

const int EVENT_COUNT = 5;
using Event = tuple<int, string, string, int>; // ID, event name, category, fee (Rs.)

array<Event, EVENT_COUNT> events = {{
    make_tuple(101, "CodeSprint", "Technical", 150),
    make_tuple(102, "RoboRace", "Technical", 200),
    make_tuple(103, "RhythmNight", "Cultural", 100),
    make_tuple(104, "DesignDash", "Creative", 120),
    make_tuple(105, "SportsMeet", "Sports", 80)
}};

struct Registration {
    int registrationID;
    string studentName;
    int eventID;
    Registration* next;

    Registration(int rid, const string& name, int eid)
        : registrationID(rid), studentName(name), eventID(eid), next(NULL) {}
};

class CampusEventSystem {
private:
    Registration* head;
    Registration* tail;
    int nextRegistrationID;
    queue<string> helpDesk;
    stack<int> recentRegistrations;

    const Event* findEvent(int id) const {
        for (const auto& event : events) {
            if (get<0>(event) == id) return &event;
        }
        return NULL;
    }

    Registration* findRegistration(int id) const {
        Registration* current = head;
        while (current != NULL) {
            if (current->registrationID == id) return current;
            current = current->next;
        }
        return NULL;
    }

    void printEvent(const Event& event) const {
        cout << left << setw(8) << get<0>(event)
             << setw(18) << get<1>(event)
             << setw(14) << get<2>(event)
             << "Rs. " << get<3>(event) << '\n';
    }

public:
    CampusEventSystem() : head(NULL), tail(NULL), nextRegistrationID(1) {}

    ~CampusEventSystem() {
        Registration* current = head;
        while (current != NULL) {
            Registration* next = current->next;
            delete current;
            current = next;
        }
    }

    void displayEvents() const {
        cout << "\n---------------- Available Campus Events ----------------\n";
        cout << left << setw(8) << "ID" << setw(18) << "Event"
             << setw(14) << "Category" << "Fee\n";
        cout << "----------------------------------------------------------\n";
        for (const auto& event : events) printEvent(event);
    }

    void registerStudent() {
        string name;
        int eventID;
        cout << "Enter student name (one word): ";
        cin >> name;
        displayEvents();
        cout << "Enter event ID: ";
        if (!(cin >> eventID)) { invalidInput(); return; }

        if (findEvent(eventID) == NULL) {
            cout << "Invalid event ID. Registration not created.\n";
            return;
        }

        Registration* node = new Registration(nextRegistrationID, name, eventID);
        if (head == NULL) head = tail = node;
        else { tail->next = node; tail = node; }

        recentRegistrations.push(nextRegistrationID);
        cout << "Registration successful!\nRegistration ID: "
             << nextRegistrationID << '\n';
        cout << "Event: " << get<1>(*findEvent(eventID))
             << " | Fee: Rs. " << get<3>(*findEvent(eventID)) << '\n';
        ++nextRegistrationID;
    }

    void displayRegistrations() const {
        if (head == NULL) { cout << "No registrations yet.\n"; return; }
        cout << "\n---------------- Student Registrations ----------------\n";
        Registration* current = head;
        while (current != NULL) {
            const Event* event = findEvent(current->eventID);
            cout << "Registration ID: " << current->registrationID
                 << " | Student: " << current->studentName
                 << " | Event: " << (event ? get<1>(*event) : "Unknown")
                 << " | Event ID: " << current->eventID << '\n';
            current = current->next;
        }
    }

    void searchRegistration() const {
        int id;
        cout << "Enter registration ID: ";
        if (!(cin >> id)) { invalidInput(); return; }
        Registration* record = findRegistration(id);
        if (record == NULL) { cout << "Registration not found.\n"; return; }
        const Event* event = findEvent(record->eventID);
        cout << "Registration ID: " << record->registrationID
             << "\nStudent: " << record->studentName
             << "\nEvent: " << (event ? get<1>(*event) : "Unknown")
             << "\nEvent ID: " << record->eventID << '\n';
    }

    void cancelRegistration() {
        int id;
        cout << "Enter registration ID to cancel: ";
        if (!(cin >> id)) { invalidInput(); return; }

        Registration* current = head;
        Registration* previous = NULL;
        while (current != NULL && current->registrationID != id) {
            previous = current;
            current = current->next;
        }
        if (current == NULL) { cout << "Registration not found.\n"; return; }

        if (previous == NULL) head = current->next;
        else previous->next = current->next;
        if (current == tail) tail = previous;
        delete current;
        cout << "Registration cancelled successfully.\n";
    }

    void showCount() const {
        int count = 0;
        Registration* current = head;
        while (current != NULL) { ++count; current = current->next; }
        cout << "Total active registrations: " << count << '\n';
    }

    void sortEventsByFee() const {
        array<Event, EVENT_COUNT> sorted = events;
        // Bubble sort: ascending fee
        for (int i = 0; i < EVENT_COUNT - 1; ++i) {
            for (int j = 0; j < EVENT_COUNT - i - 1; ++j) {
                if (get<3>(sorted[j]) > get<3>(sorted[j + 1]))
                    swap(sorted[j], sorted[j + 1]);
            }
        }
        cout << "\nEvents sorted by fee (Bubble Sort):\n";
        cout << left << setw(8) << "ID" << setw(18) << "Event"
             << setw(14) << "Category" << "Fee\n";
        for (const auto& event : sorted) printEvent(event);
    }

    void sortEventsByName() const {
        array<Event, EVENT_COUNT> sorted = events;
        // Insertion sort: alphabetical event name
        for (int i = 1; i < EVENT_COUNT; ++i) {
            Event key = sorted[i];
            int j = i - 1;
            while (j >= 0 && get<1>(sorted[j]) > get<1>(key)) {
                sorted[j + 1] = sorted[j];
                --j;
            }
            sorted[j + 1] = key;
        }
        cout << "\nEvents sorted by name (Insertion Sort):\n";
        cout << left << setw(8) << "ID" << setw(18) << "Event"
             << setw(14) << "Category" << "Fee\n";
        for (const auto& event : sorted) printEvent(event);
    }

    void sortEventsByID() const {
        array<Event, EVENT_COUNT> sorted = events;
        // Selection sort: ascending event ID
        for (int i = 0; i < EVENT_COUNT - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < EVENT_COUNT; ++j) {
                if (get<0>(sorted[j]) < get<0>(sorted[minIndex]))
                    minIndex = j;
            }
            if (minIndex != i) swap(sorted[i], sorted[minIndex]);
        }
        cout << "\nEvents sorted by ID (Selection Sort):\n";
        cout << left << setw(8) << "ID" << setw(18) << "Event"
             << setw(14) << "Category" << "Fee\n";
        for (const auto& event : sorted) printEvent(event);
    }

    void addHelpRequest() {
        string request;
        cout << "Enter help-desk request (one word): ";
        cin >> request;
        helpDesk.push(request);
        cout << "Request added to queue. Position: " << helpDesk.size() << '\n';
    }

    void processHelpRequest() {
        if (helpDesk.empty()) { cout << "No help-desk requests waiting.\n"; return; }
        cout << "Processing request: " << helpDesk.front() << '\n';
        helpDesk.pop();
    }

    void showMostRecentRegistration() const {
        if (recentRegistrations.empty()) {
            cout << "No registrations have been created yet.\n";
            return;
        }
        cout << "Most recently created registration ID: "
             << recentRegistrations.top() << '\n';
    }

    static void invalidInput() {
        cout << "Invalid input. Returning to menu.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

int main() {
    CampusEventSystem system;
    int choice;

    do {
        cout << "\n============================================\n";
        cout << "     CAMPUS EVENT & HELP DESK SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Display available events\n";
        cout << "2. Register student for an event\n";
        cout << "3. Display all registrations\n";
        cout << "4. Search registration by ID\n";
        cout << "5. Cancel registration\n";
        cout << "6. Count active registrations\n";
        cout << "7. Sort events by fee (Bubble Sort)\n";
        cout << "8. Sort events by name (Insertion Sort)\n";
        cout << "9. Sort events by ID (Selection Sort)\n";
        cout << "10. Add help-desk request (Queue)\n";
        cout << "11. Process next help-desk request (Queue)\n";
        cout << "12. Show most recent registration ID (Stack)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            CampusEventSystem::invalidInput();
            continue;
        }

        switch (choice) {
            case 1: system.displayEvents(); break;
            case 2: system.registerStudent(); break;
            case 3: system.displayRegistrations(); break;
            case 4: system.searchRegistration(); break;
            case 5: system.cancelRegistration(); break;
            case 6: system.showCount(); break;
            case 7: system.sortEventsByFee(); break;
            case 8: system.sortEventsByName(); break;
            case 9: system.sortEventsByID(); break;
            case 10: system.addHelpRequest(); break;
            case 11: system.processHelpRequest(); break;
            case 12: system.showMostRecentRegistration(); break;
            case 0: cout << "Thank you for using the Campus Event System!\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
