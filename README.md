# Simple-Console-Based-Banking-Application-
A C++ console application simulating basic banking operations with file persistence for account data.



Overview
This is a straightforward console-based banking application developed in C++. It simulates basic banking operations, allowing users to create accounts, deposit funds, withdraw money, check balances, and view all existing accounts. The application also includes a file persistence mechanism, ensuring that all account data is saved to a text file (accounts.txt) upon exit and loaded automatically when the application starts.

This project was developed as part of my learning journey in C++ programming, focusing on core concepts such as Object-Oriented Programming (OOP), file input/output (I/O), and robust user input handling.

Features
Create New Account: Users can open new bank accounts with a unique auto-generated account number, account holder's name, and an initial deposit.

Deposit Money: Deposit funds into an existing account using its account number.

Withdraw Money: Withdraw funds from an account, with checks for sufficient balance.

Check Balance: View the current balance of any account.

View All Accounts: Display a list of all existing accounts with their details.

Data Persistence: All account data is automatically saved to accounts.txt upon application exit and loaded at startup. This ensures that account information is not lost between sessions.

Robust Input Handling: Implements custom functions (getIntInput, getDoubleInput) to validate user input and prevent common errors like entering text instead of numbers, enhancing user experience and application stability.

How to Compile and Run
This project is a console application and can be compiled using a C++ compiler like G++.

Save the Code:
Save the entire code (from banking_app.cpp if you kept it as one file) into a single file named main.cpp (or banking_app.cpp).

Open Terminal/Command Prompt:
Navigate to the directory where you saved the main.cpp file using your terminal or command prompt.

Compile the Program:
Use the G++ compiler (or your preferred C++ compiler) to compile the source code.

Bash

g++ main.cpp -o BankingApp
-o BankingApp specifies the name of the executable output file. You can choose any name.

Run the Application:
Execute the compiled program from your terminal:

Bash

./BankingApp
(On Windows, you might just type BankingApp.exe or BankingApp)

Technologies Used
C++: The core programming language.

C++ Standard Library:

iostream for console input/output.

fstream for file operations (reading/writing accounts.txt).

vector for dynamic array management (storing Account objects).

string for handling text data (account names).

limits for robust input validation (std::numeric_limits).

algorithm for utility functions (std::max).

iomanip for input/output formatting (e.g., setting decimal precision for currency).

Future Enhancements (Ideas for further development)
Error Logging: Implement a system to log errors (e.g., file open failures, invalid transactions) to a separate log file.

Search Account: Add a feature to search for accounts by name or other criteria.

Account Deletion: Implement functionality to close/delete accounts.

Transaction History: Store and display a history of deposits and withdrawals for each account.

User Authentication: Add a login system for different users/bank staff.

More Account Types: Introduce different account types (e.g., Savings, Checking) with varying rules.

GUI Interface: Convert the console application into a graphical user interface (GUI) using libraries like Qt or wxWidgets.

Author
Caleb Anafo

www.linkedin.com/in/
caleb-anafo-4878b22a8





License
This project is licensed under the  MIT License
