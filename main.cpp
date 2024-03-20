#include <iostream>
#include <cstring>
using namespace std;

struct Event {
    char name[50];
    int availableTickets;
};

struct Booking {
    int bookingID, numTickets, ticketNumber, seatNumber;
    char eventName[50], bookingName[50];
};

void displayEvent(const Event *event) {
    cout << event->name << "\nAvailable Tickets: " << event->availableTickets << endl;
}

void displayEvents(const Event events[], int numEvents) {
    cout << "Available Events:\n";
    for (int i = 0; i < numEvents; ++i) {
        displayEvent(&events[i]);
        cout << "------------------------" << endl;
    }
}

int bookTickets(Event events[], int numEvents, Booking *booking, int *ticketCounter, int *seatCounter, int *bookingIDCounter) {
    for (int i = 0; i < numEvents; ++i) {
        if (strcmp(events[i].name, booking->eventName) == 0) {
            if (events[i].availableTickets >= booking->numTickets) {
                cout << "Tickets booked for " << booking->eventName << " by " << booking->bookingName << ": " << booking->numTickets << endl;

                for (int j = 0; j < booking->numTickets; ++j) {
                    booking->bookingID = *bookingIDCounter;
                    booking->ticketNumber = *ticketCounter;
                    booking->seatNumber = *seatCounter;
                    cout << "Booking ID: " << booking->bookingID << ", Ticket Number: " << booking->ticketNumber << ", Seat Number: " << booking->seatNumber << endl;
                    (*ticketCounter)++;
                    (*seatCounter)++;
                }

                events[i].availableTickets -= booking->numTickets;
                (*bookingIDCounter)++;
                return 1;
            } else {
                cout << "Not enough tickets available for " << booking->eventName << endl;
                return 0;
            }
        }
    }
    cout << "Event not found: " << booking->eventName << endl;
    return 0;
}

void displayTicketDetails(const Booking bookings[], int numBookings) {
    cout << "Ticket Details:\n";
    for (int i = 0; i < numBookings; ++i) {
        cout << "Booking ID: " << bookings[i].bookingID << ", Ticket Number: " << bookings[i].ticketNumber << ", Seat Number: " << bookings[i].seatNumber << endl;
        cout << "Event: " << bookings[i].eventName << "\nBooking Name: " << bookings[i].bookingName << "\nNumber of Tickets: " << bookings[i].numTickets << endl;
        cout << "------------------------" << endl;
    }
}

void generateReceipt(const Booking *booking) {
    cout << "\nBilling Receipt:\n";
    cout << "Booking ID: " << booking->bookingID << "\nEvent: " << booking->eventName << "\nBooking Name: " << booking->bookingName << "\nNumber of Tickets: " << booking->numTickets << endl;
    cout << "Seat Numbers:";

    for (int i = 0; i < booking->numTickets; ++i) {
        if (i > 0) {
            cout << " ";
        }
        cout << booking->seatNumber + i + 1;
    }

    cout << "\nTotal Cost: ₹" << booking->numTickets * 200 << "\n------------------------" << endl;
}

int main() {
    Event events[10];
    Booking bookings[10];
    int numEvents = 0, numBookings = 0, ticketCounter = 1, seatCounter = 1, bookingIDCounter = 1, choice;

    strcpy(events[numEvents].name, "Concert");
    events[numEvents].availableTickets = 100;
    numEvents++;

    strcpy(events[numEvents].name, "Theater Show");
    events[numEvents].availableTickets = 50;
    numEvents++;

    strcpy(events[numEvents].name, "Movie");
    events[numEvents].availableTickets = 100;
    numEvents++;

    do {
        cout << "\nMenu:\n";
        cout << "1. Display available events\n";
        cout << "2. Book tickets\n";
        cout << "3. Display ticket details\n";
        cout << "4. Generate billing receipt\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayEvents(events, numEvents);
                break;
            case 2:
                Booking booking;
                cout << "Enter your name for the booking: ";
                cin >> booking.bookingName;
                cout << "Enter the event name: ";
                cin >> booking.eventName;
                cout << "Enter the number of tickets to book: ";
                cin >> booking.numTickets;

                if (bookTickets(events, numEvents, &booking, &ticketCounter, &seatCounter, &bookingIDCounter)) {
                    bookings[numBookings] = booking;
                    numBookings++;
                }
                break;
            case 3:
                displayTicketDetails(bookings, numBookings);
                break;
            case 4:
                if (numBookings > 0) {
                    int receiptChoice;
                    cout << "Enter the booking ID for which you want to generate the receipt: ";
                    cin >> receiptChoice;
                    int found = 0;
                    for (int i = 0; i < numBookings; ++i) {
                        if (bookings[i].bookingID == receiptChoice) {
                            generateReceipt(&bookings[i]);
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        cout << "Invalid booking ID." << endl;
                    }
                } else {
                    cout << "No bookings to generate a receipt." << endl;
                }
                break;
            case 5:
                cout<<"Thank You!";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}
