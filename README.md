Theater-Booking-System

Description
This project simulates a multi-threaded seat reservation system using pthreads in C. Multiple customers (threads) attempt to reserve seats in different zones of a venue, while interacting with a call center and cashiers. The system uses mutexes and condition variables to synchronize thread operations, ensuring mutual exclusion and proper thread communication.

Files
p3190049-p3190307-p3190347-res.h: This header file contains global variables related to the configuration of the reservation system, such as the number of cashiers, seats, and probability parameters.
p3190049-p3190307-p3190347-res.c: This file contains the main logic of the seat reservation system, including thread creation, seat allocation, payment processing, and synchronization mechanisms.

Functionality (from .c)

Main Flow:
The system initializes a 2D array representing the seating layout (split between Zone A and Zone B) and creates multiple customer threads.
Each customer goes through the process of choosing a zone, selecting seats, and making a payment.

Reservation Process:
Each customer thread checks seat availability in the desired zone.
If seats are available, the thread reserves them; otherwise, it reports an error.
After seat reservation, the thread proceeds to payment. The payment can either succeed or fail, depending on a random number and the defined probability of successful transactions.

Synchronization:
The system uses several mutexes and condition variables to handle critical sections and coordinate threads:
Mutexes for seat reservation, payment processing, and statistics collection.
Condition variables to wait when telephone operators or cashiers are busy.

Final Output:
The system calculates and prints various statistics after all customers are served:
Total revenue from seat reservations.
Percentage of successful transactions, card failures, and failed seat searches.
Average wait times for telephone operators and cashiers.
Average total time taken per transaction.
