#include <iostream>
#include <string>
#include "Header.h"
using namespace std;

int main() {
    Train train;


    Train* head = nullptr;  // Initialize the linked list to be empty

    // Add some train details for demonstration
    train.addTrain(head, 3, "Colombo to Galle", "10:00", "10:45", 400);
    train.addTrain(head, 2, "Galle to Matara", "11:00", "12:00", 450);
    train.addTrain(head, 1, "Galle to Kandy", "12:15", "12:45", 550);
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t DATE : " << __DATE__ << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t TIME : " << __TIME__ << endl;
    cout << "\t\t\t================================================" << endl;
    cout << "\t\t\t*** WELCOME TO THE RAILWAY MANAGEMENT SYSTEM ***" << endl;;
    cout << "\t\t\t================================================\n" << endl;

    train.mainMenu(head);
}
