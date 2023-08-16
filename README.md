# Booking-System
This repository contains a C++ project for a booking system that facilitates the management of accommodation and transportation reservations. The system allows users to create, manage, and view reservation requests.

 ## Table of Contents 
 * Introduction
 * Features
 * Getting Started
 * Usage
 * Classes
 * Contributing
 * License
 
## Introduction
This project is designed to streamline the process of making reservation requests for accommodations and transportation. It consists of several C++ classes that work together to handle user input, create reservation objects, and manage them through a call center.

## Features
* Create reservation requests for standard and superior accommodations.
* Choose transportation options: flight, train, or self-travel.
* Calculate and display total reservation prices.
* View and cancel existing reservation requests.

## Getting Started
To get started with the project, follow these steps:

1.  Clone the repository to your local machine using:
    git clone <repository-url>
2.  Compile the C++ code using your preferred compiler. For example, if you are using g++, you can compile the code with:
    g++ -o booking_system main.cpp
3.  Run the compiled executable:
    ./booking_system
   
## Usage
1.  Upon running the executable, you will be presented with a menu of options.
2.  Choose an option to create a new reservation request (standard or superior), view existing reservation requests, or exit the system.
3.  Follow the prompts to input details such as accommodation information and transportation preferences.
4.  After creating a reservation request, you can view all existing requests or select a specific request to view its details.
5.  You can also choose to cancel a reservation request if needed.

## Classes
The project contains the following C++ classes:

* `Date`: Represents a date.
* `Services`: Enumerates different meal service options.
* `Accomodation`: Represents accommodation details and calculates prices.
* `Transport`: Abstract base class for transportation options.
* `SelfTravel`: Subclass of Transport representing self-travel.
* `PublicTransport`: Subclass of Transport representing public transportation options.
* `Flight`: Subclass of PublicTransport representing flight transportation.
* `Train`: Subclass of PublicTransport representing train transportation.
* `Request`: Represents a reservation request with accommodation and transportation details.
* `CallCenter`: Manages reservation requests.

## Contributing
Contributions to the project are welcome! If you find any issues or want to improve the project, feel free to submit a pull request.






