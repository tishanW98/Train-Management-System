#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Passenger {
public:
    string name;
    string phone;
    int quantity;
    Passenger(string n, string p, int q) : name(n), phone(p), quantity(q) {}
};

class Node1
{
public:
    Node1* next;
    Passenger* passenger;
    Node1(Passenger* p) : passenger(p), next(NULL) {}

};


class book
{
public:
    Node1* rear;
    Node1* front;
    int size;

public:

    book() : front(NULL), rear(NULL), size(0) {}

    void enqueue(Passenger* p)
    {
        Node1* temp = new Node1(p);
        if (front == NULL)
        {
            rear = temp;
            front = temp;
        }
        else
        {
            rear->next = temp;
        }
        rear = temp;
        size++;

    }

    Passenger* dequeue()
    {

        if (front == NULL)
        {
            cout << "No booking at the moment" << endl;
            return NULL;
        }
        Passenger* p = front->passenger;
        Node1* temp = front;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }
        delete temp;
        size--;
        return p;
    }

    bool cancelTicket(string phone) {
        Node1* prev = NULL;
        Node1* curr = front;
        while (curr != NULL) {
            if (curr->passenger->phone == phone) {
                if (prev == NULL) {
                    front = curr->next;
                }
                else {
                    prev->next = curr->next;
                }
                if (rear == curr) {
                    rear = prev;
                }
                delete curr;
                size--;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

};
class Booking {
private:
    int carriageNum;
    int seatNum;
public:
    Booking(int carriageNum, int seatNum) {
        this->carriageNum = carriageNum;
        this->seatNum = seatNum;
    }
    int getCarriageNum() {
        return carriageNum;
    }
    int getSeatNum() {
        return seatNum;
    }
};

class Train {
private:

    int availableSeats;
    string departureTime;
    string arrivalTime;
public:
    string route;
    book* queue;
    Train(string r) : route(r), queue(new book()) {}
    Train* next;
    int trainNumber;
    

    Train() {
        trainNumber = 0;
        route = "";
        availableSeats = 0;
        departureTime = "";
        arrivalTime = "";
        next = nullptr;
    }

    Train(int number, string route, string departure, string arrival, int availableSeats) {
        trainNumber = number;
        this->route = route;
        departureTime = departure;
        arrivalTime = arrival;

        next = nullptr;

    }


    void addTrain(Train*& head, int trainNumber, string route, string departureTime, string arrivalTime, int availableSeats) {
        Train* newTrain = new Train(trainNumber, route, departureTime, arrivalTime, availableSeats);
        newTrain->next = head;
        head = newTrain;
    }


    void addNewTrain(Train*& head) {
        int trainNumber;
        string route;
        string departureTime;
        string arrivalTime;

        cout << "\nEnter train number: ";
        cin >> trainNumber;

        // Check if train number already exists
        if (searchTrain(head, trainNumber) != nullptr) {
            cout << "Train number " << trainNumber << " already exists." << endl;
            return;
        }

        cout << "Enter route: ";
        cin.ignore();
        getline(cin, route);

        cout << "Enter departure time: ";
        cin >> departureTime;

        cout << "Enter arrival time: ";
        cin >> arrivalTime;

        Train* newTrain = new Train(trainNumber, route, departureTime, arrivalTime, availableSeats);
        newTrain->next = nullptr;

        if (head == nullptr) {
            head = newTrain;
        }
        else {
            Train* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newTrain;
        }

        cout << "Train " << trainNumber << " added successfully." << endl;
    }


    Train* searchTrain(Train* head, int trainNumber) {
        Train* curr = head;
        while (curr != NULL) {
            if (curr->trainNumber == trainNumber) {
                cout << "Train " << trainNumber << " is available." << endl;
                cout << "Route: " << curr->route << endl;
                cout << "Departure time: " << curr->departureTime << endl;
                cout << "Arrival time: " << curr->arrivalTime << endl;
                return curr;
            }
            curr = curr->next;
        }
        cout << "Train " << trainNumber << " is not available." << endl;
        return nullptr;
    }

    Train* searchBystring(Train* head, string route)
    {
        Train* curr = head;
        while (curr != NULL) {
            if (curr->route == route) {
                cout << "\n" << route << " train is available today." << endl;
                cout << "\nRoute:" << "\t\t\tDeparture time:" << "\t\tArrival time:" << endl;
                cout << curr->route << "\t\t" << curr->departureTime << "\t\t\t" << curr->arrivalTime << endl;
                return 0;
            }
            curr = curr->next;
        }
        cout << "Train from " << route << " is not available." << endl;
        return 0;
    }


    void changeTrainDetails(Train* head, int trainNumber) {
        cout << "\nEnter the train number to edit details: ";
        cin >> trainNumber;
        Train* curr = head;
        while (curr != nullptr) {
            if (curr->trainNumber == trainNumber) {
                cout << "Current route: " << curr->route << endl;
                cout << "Enter the new route: ";
                cin.ignore();
                getline(cin, curr->route);

                cout << "Current departure time: " << curr->departureTime << endl;
                cout << "Enter the new departure time: ";
                cin >> curr->departureTime;

                cout << "Current arrival time: " << curr->arrivalTime << endl;
                cout << "Enter the new arrival time: ";
                cin >> curr->arrivalTime;

                cout << "Train details edited successfully." << endl;
                return;
            }
            curr = curr->next;
        }
        cout << "Train " << trainNumber << " not found." << endl;
    }


    void removeTrain(Train*& head, int trainNumber) {
        Train* curr = head;
        Train* prev = nullptr;

        while (curr != nullptr) {
            if (curr->trainNumber == trainNumber) {
                if (prev == nullptr) {  // If the train to be deleted is the head node
                    head = curr->next;
                }
                else {
                    prev->next = curr->next;
                }
                delete curr;
                cout << "Train " << trainNumber << " removed from schedule." << endl;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        cout << "Train " << trainNumber << " not found in the schedule." << endl;
    }

    void printTrains(Train* head) {
        cout << "\nTrain Schedule: \n" << endl;
        Train* curr = head;
        cout << "Train Number:" << "\t\tDeparture Time:" << "\t\tArrival Time:" << "\t\tRoute:\n" << endl;
        while (curr != nullptr) {
            cout << curr->trainNumber << "\t\t\t" << curr->departureTime << "\t\t\t" << curr->arrivalTime << "\t\t\t" << curr->route << endl;
            curr = curr->next;
        }
    } //DONE

    void deleteAllTrains(Train*& head) {
        Train* curr = head;
        while (curr != nullptr) {
            Train* next = curr->next;
            delete curr;
            curr = next;
        }
        head = nullptr;
    }

    // Administration login
    bool adminLogin() {
        string password;
        cout << "\nEnter the admin password: ";
        cin >> password;
        return password == "admin";
    }

    // Administration part to edit train details
    int logAdmin(Train* head)
    {
        int choice2;
        while (true) {
            cout << "\n" << endl;
            cout << "1. Change Train Details " << endl;
            cout << "2. Add New Train " << endl;
            cout << "3. Remove Train " << endl;
            cout << "4. Display Details " << endl;
            cout << "5. Return the Main Menu " << endl;
            cout << "Enter your choice: ";
            cin >> choice2;
            switch (choice2) {
            case 1:
                changeTrainDetails(head, trainNumber);
                break;
            case 2:
                addNewTrain(head);
                break;
            case 3: {
                int trainNumber;
                cout << "Enter the train number to remove: ";
                cin >> trainNumber;
                removeTrain(head, trainNumber);
                break;
            }
            case 4:
                printTrains(head);

                break;
            case 5:
                mainMenu(head);
                break;
            default:
                cout << "Invalid choice. Please try again.\a\n" << endl;
                break;
            }
        }
        return 0;
    }
    

    void bookTicket1(string name, string phone, int quantity) {
        Passenger* passenger = new Passenger(name, phone, quantity);
        queue->enqueue(passenger);
        cout << "Ticket booked successfully!" << endl;
    }

    void cancelTicket(string phone) {
        if (queue->cancelTicket(phone)) {
            cout << "Ticket cancelled successfully!" << endl;
        }
        else {
            cout << "Ticket not found!" << endl;
        }
    }
    void displayQueue() {
        cout << "Route: " << route << endl;
        cout << "Passenger details:" << endl;
        Node1* curr = queue->front;
        while (curr != NULL) {
            cout << "Name: " << curr->passenger->name << ", Phone: " << curr->passenger->phone << ", Quantity: " << curr->passenger->quantity << endl;
            curr = curr->next;
        }
        cout << "Total tickets booked: " << queue->size << endl;
    }



    void bookTicket(Train* head)
    {
        system("cls");
        int choice6;
        Train* trains[3];
        trains[0] = new Train("Galle to Kandy, 12:15, 12:45");
        trains[1] = new Train("Galle to Matara, 11:00, 12:00");
        trains[0] = new Train("Colombo to Galle,10:00,10 : 45");
        while (true) {
            cout << "  1. Book Ticket\n  2. Cancel Ticket\n  3. Exit" << endl; //3. Display Booking Summary\n

            cout << "\nEnter your choice: ";
            cin >> choice6;
            string passenger_name, phone;
            int quantity, route;

            if (choice6 == 1) {
                cout << "\n\t\t*** Select Train by looking below Train Schedule *** \n\t\t----------------Available Trains-----------------" << endl;
                printTrains(head);
                cout << "Enter passenger name: ";
                cin >> passenger_name;
                cout << "Enter Your Phone Number: ";
                cin >> phone;
                cout << "Enter Number of Tickets: ";
                cin >> quantity;
                cout << "Enter route (1-3): ";
                cin >> route;
                if (route >= 1 && route <= 5) {
                    trains[route - 1]->bookTicket1(passenger_name, phone, quantity);

                }
                else {
                    cout << "Invalid route!" << endl;
                }
            }

            if (choice6 == 2) {

                cout << "\n\t\t*** Select Train by looking below Train Schedule *** \n\t\t----------------Train Schedule-----------------" << endl;
                printTrains(head);

                cout << "Enter Your Phone Number: ";
                cin >> phone;
                cout << "Enter Number of Tickets: ";
                cin >> quantity;
                cout << "Enter route (1-3): ";
                cin >> route;
                if (route >= 1 && route <= 5) {
                    trains[route - 1]->cancelTicket(phone);
                }
                else {
                    cout << "Invalid route!" << endl;
                }
            }
            if (choice6 == 3)
            {
                mainMenu(head);

            }
        }
    }


    int logUser(Train* head)
    {
        string road;
        int choice;
        while (true) {
            cout << "\n" << endl;
            cout << "1. Display Train Schedule" << endl;
            cout << "2. Check Availability" << endl;
            cout << "3. Ticket Booking & Cancellation" << endl;
            cout << "4. Return the Main Menu\n" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                printTrains(head);
                break;
            case 2:
                cin.ignore();
                cout << "Enter train route to check availability: ";
                getline(cin, road);
                searchBystring(head, road);
                break;
            case 3:
                bookTicket(head);
                break;
            case 4:
                mainMenu(head);
                return 0;
            default:
                cout << "Invalid choice. Please try again.\a\n" << endl;
                break;
            }
        }
        return 0;

    }


    int mainMenu(Train* head) {
        int select;
        while (true) {
            cout << "\t\t\t\t------------- Main Menu -------------\n" << endl;
            cout << "1. Admin Mode" << endl;
            cout << "2. User Mode" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> select;
            switch (select) {
            case 1:
                if (adminLogin()) {
                    cout << "\n\t\t\t\t------------- Administration Menu  -------------\n" << endl;

                    logAdmin(head);
                }
                else {
                    cout << "Incorrect password. Access denied.\a\n" << endl;
                }
                break;
            case 2:
                logUser(head);
                break;
            case 3:
                cout << "\n** Press Any Key to Exit ..." << endl;
                return 0;
                break;
            default:
                cout << "Invalid choice. Please try again.\a\n" << endl;
                break;
            }
        }
        return 0;
    }
};
