/*
 * @file Tickets.cpp
 * @author Hussein Ahmad (hussein.ahmad@studerande.movant.se)
 * brief This program will generate flight-ticktes. 
 * @date 2022-11-06
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;



struct flightList
{
string time;
string date;
string destination;
string departure;

int flight_number;
int first_class;
int busniess_class;
int economy_class;
};
	

struct bookingList
{
string firstName;
string lastName;
string time;
string date;
string destination;
string departure;
string seat_class;

int booking_number;
int row;
int seat;
};

// reads in flights.csv and save the information in a vector
void flights_list(string file, vector<flightList*>* list)
{
ifstream flight_info(file);
string file_information;
if (flight_info.is_open())
{
while (getline(flight_info, file_information) && !file_information.empty())
{
flightList* New = new flightList;
stringstream info(file_information);
string new_string ;
getline(info, new_string, ',');
New->flight_number = atol(new_string.c_str());
	
getline(info, New->departure, ',');
getline(info, New->destination, ',');
getline(info, New->date, ',');
getline(info, New->time, ',');
	
getline(info, new_string, ',');
New->first_class = atol(new_string.c_str());
	
getline(info, new_string, ',');
New->busniess_class = atol(new_string.c_str());
	
getline(info, new_string, ',');
New->economy_class = atol(new_string.c_str());
	
list->push_back(New); // puts in the information in the end of the vector
	
if (!info)
break;
}
}
}


// reads in bookings.csv and save the information in a vector
void booking_list(string file, vector<bookingList*>* list)
{
ifstream booking_info(file);
string file_information;
if (booking_info.is_open())
{
while (getline(booking_info, file_information) && !file_information.empty())
{
bookingList* New = new bookingList;
stringstream info(file_information);
string new_string;
getline(info, new_string, ',');
New->booking_number = atol(new_string.c_str());
	
getline(info, New->date, ',');
getline(info, New->time, ',');
	
getline(info, New->departure, ',');
getline(info, New->destination, ',');
	
getline(info, New->seat_class, ',');
getline(info, New->firstName, ',');
getline(info, New->lastName, ',');
list->push_back(New); // puts in the information in the end of the vector
	
if (!info)
break;
}
}
}

// create templetclass flights and bookings
template <class flights, class bookings>
// Function that crate tickets for the bookings
void createTickets(vector<flights>& Flight_List, vector<bookings>& Booking_List)
{

for (auto & flightList : Flight_List)
{
int first_class = 1;
int first_class_row = 1;
	
int business_class = 1;
int business_class_row = flightList->first_class / 7 + 1;
	
int economy_class = 1;
int economy_class_row = (flightList->first_class + flightList->busniess_class) / 7 + 1;
for (auto & bookingList : Booking_List)
{

if ((flightList->time == bookingList->time) && (flightList->date == bookingList->date) && (flightList->departure == bookingList->departure) && (flightList->destination == bookingList->destination))
{
if (bookingList->seat_class == "first")
{
bookingList->seat = first_class;
bookingList->row = first_class_row;
first_class++;
	
if (first_class > 7)
{
first_class = 1;
first_class_row++;
}
}
else if (bookingList->seat_class == "business")
{
bookingList->seat = business_class;
bookingList->row = business_class_row;
business_class++;
	
if (business_class > 7)
{
business_class = 1;
business_class_row++;
}
}
else if (bookingList->seat_class == "economy")
{
bookingList->seat = economy_class;
bookingList->row = economy_class_row;
economy_class++;
	
if (economy_class > 7)
{
economy_class = 1;
economy_class_row++;
}
}

// prints out tickets whit the right information	
ostringstream string_stream;
string_stream << "ticket-" << bookingList->booking_number << ".txt";
ofstream ticketFile(string_stream.str());
string_stream.str("Clear"); // clear the string in ostringstream

string_stream<< "BOOKING: " << bookingList->booking_number << "\nFLIGHT: " << flightList->flight_number << " DEPARTURE: " << flightList->departure << " DESTINATION: " << flightList->destination << " " << bookingList->date << " " << bookingList->time <<"\nPASSENGER: " << bookingList->firstName << " " << bookingList->lastName << "\n" << "CLASS: " << bookingList->seat_class << "\n" << "ROW: " << bookingList->row << " SEAT: " << bookingList->seat;
ticketFile << string_stream.str();	
ticketFile.close();
}
}
}
}

	int main()
{
	
	vector<flightList*> flights;
	vector<bookingList*> bookings;

	flights_list("flights.csv", &flights);
    booking_list("bookings.csv", &bookings);
	createTickets<flightList*, bookingList*>(flights, bookings);
	return 0;
}
