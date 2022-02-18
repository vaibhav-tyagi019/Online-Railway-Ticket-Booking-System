# Online-Railway-Ticket-Booking-System
Description: The project aims to develop a ticket booking system that is user-friendly and
multi- functional. The project should have the following functionalities:
1. All account transactional details and customer information are stored in files.
2. Account holders have to pass through a login system to enter their accounts.
3. The application should possess password-protected administrative access; thus
preventing the whole management system from unauthorized access.
4. Three types of login should be created: normal account, agent account(multiple
simultaneous logins) , administrator;
5. Once you login as administrator, you should be able to add, delete, modify, search
for a specific account and train details.
6. Once the customer connect to the server, you should get login and password
prompt.
After successful login, you should get menu for example: Do you want to:
• Book Ticket
• View Previous Bookings
• Update Booking
• Cancel Booking
7. If you login as an agent account holder, proper file locking should be implemented. If
you want to view the booking details then read lock is to be set else if you want to
book or modify then write lock should be used to protect the critical data section.
8. Use socket programming – Server maintains the data base and service multiple
clients concurrently. Client program can connect to the server and access their
specific account details.
9. Use system calls instead of Library functions wherever it is possible in the project:
Process Management, File Management, File Locking, Multithreading and Inter
Process Communication Mechanisms.
