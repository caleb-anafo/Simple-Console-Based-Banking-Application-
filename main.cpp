#include <iostream>  // For std::cout, std::cin, std::cerr
#include <fstream>   // For std::ifstream, std::ofstream
#include <vector>    // For std::vector
#include <string>    // For std::string, std::getline
#include <limits>    // For std::numeric_limits (used in clearInputBuffer)
#include <algorithm> // For std::max
#include <iomanip>   // For std::fixed, std::setprecision

// --- Account Class Definition ---
class Account {
private:
    int accountNumber;
    std::string name;
    double balance;

public:
    // Constructor
    Account(int accNum, std::string accName, double initialDeposit) {
        accountNumber = accNum;
        name = accName;
        balance = initialDeposit;
    }

    // Getters
    int getAccountNumber() const { return accountNumber; }
    std::string getName() const { return name; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: $" << std::fixed << std::setprecision(2) << amount << "\n";
            std::cout << "New balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
        } else {
            std::cout << "Invalid deposit amount! Amount must be positive.\n";
        }
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Invalid withdrawal amount! Amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "Insufficient balance! Available: $" << std::fixed << std::setprecision(2) << balance << "\n";
            return false;
        }
        balance -= amount;
        std::cout << "Withdrawn: $" << std::fixed << std::setprecision(2) << amount << "\n";
        std::cout << "New balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
        return true;
    }

    // --- MODIFIED: Added std::fixed and std::setprecision for consistent balance display ---
    void display() const {
        std::cout << "Account Number: " << accountNumber
                  << ", Name: " << name
                  << ", Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    // --- MODIFIED: Changed file format to write each piece on a new line ---
    void saveToFile(std::ofstream &outFile) const {
        outFile << accountNumber << "\n";
        outFile << name << "\n"; // Write the full name, including spaces
        outFile << balance << "\n";
    }

    // --- MODIFIED: Adjusted for robust file reading, especially for names with spaces ---
    static bool loadFromFile(std::ifstream &inFile, Account& account) {
        int accNum;
        std::string accName;
        double accBalance;

        // 1. Read account number
        if (!(inFile >> accNum)) {
            return false; // Failed to read account number (e.g., EOF or corrupted data)
        }
        // 2. Consume the rest of the line (the newline character) after reading the number
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // 3. Read the full account name (which might contain spaces)
        if (!std::getline(inFile, accName)) {
            return false; // Failed to read name
        }

        // 4. Read balance
        if (!(inFile >> accBalance)) {
            return false; // Failed to read balance
        }
        // 5. Consume the rest of the line (the newline character) after reading the balance
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // If all reads were successful, create/assign the account
        account = Account(accNum, accName, accBalance);
        return true;
    }
};

// --- BankingApplication Class Definition ---
class BankingApplication {
private:
    std::vector<Account> accounts;
    int nextAccountNumber;

    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int getIntInput(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInputBuffer();
                return value;
            } else {
                std::cout << "Invalid input! Please enter a number.\n";
                clearInputBuffer();
            }
        }
    }

    double getDoubleInput(const std::string& prompt) {
        double value;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                clearInputBuffer();
                return value;
            } else {
                std::cout << "Invalid input! Please enter a number.\n";
                clearInputBuffer();
            }
        }
    }

public:
    BankingApplication() : nextAccountNumber(1) {
        loadAccounts();
    }

    // --- MODIFIED: Added clearInputBuffer() at the beginning ---
    void createAccount() {
        clearInputBuffer(); // Clear any leftover newlines from previous input (e.g., menu choice)

        std::string name;
        double initialDeposit;

        std::cout << "Enter account holder's name: ";
        std::getline(std::cin, name); // Use getline to read full name, including spaces

        initialDeposit = getDoubleInput("Enter initial deposit: $");

        Account newAccount(nextAccountNumber++, name, initialDeposit);
        accounts.push_back(newAccount);
        std::cout << "Account created successfully! Account Number: "
                  << newAccount.getAccountNumber() << "\n";
    }

    Account* findAccount(int accNum) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        return nullptr;
    }

    void deposit() {
        int accNum = getIntInput("Enter account number: ");
        Account* account = findAccount(accNum);

        if (account) {
            double amount = getDoubleInput("Enter amount to deposit: $");
            account->deposit(amount);
        } else {
            std::cout << "Account not found!\n";
        }
    }

    void withdraw() {
        int accNum = getIntInput("Enter account number: ");
        Account* account = findAccount(accNum);

        if (account) {
            double amount = getDoubleInput("Enter amount to withdraw: $");
            account->withdraw(amount);
        } else {
            std::cout << "Account not found!\n";
        }
    }

    // --- MODIFIED: Added std::fixed and std::setprecision for consistent balance display ---
    void checkBalance() {
        int accNum = getIntInput("Enter account number: ");
        Account* account = findAccount(accNum);

        if (account) {
            std::cout << "Current balance: $" << std::fixed << std::setprecision(2) << account->getBalance() << "\n";
        } else {
            std::cout << "Account not found!\n";
        }
    }

    void viewAllAccounts() {
        if (accounts.empty()) {
            std::cout << "No accounts exist!\n";
            return;
        }

        std::cout << "\nAll Accounts:\n";
        for (const auto& account : accounts) {
            account.display();
        }
    }

    void saveAccounts() {
        std::ofstream outFile("accounts.txt");
        if (!outFile) {
            std::cerr << "Error: Could not open file for saving accounts!\n";
            return;
        }

        for (const auto& account : accounts) {
            account.saveToFile(outFile);
        }
        outFile.close();
        std::cout << "Accounts saved successfully!\n"; // Added confirmation message
    }

    // --- MODIFIED: Improved loadAccounts logic for robustness ---
    void loadAccounts() {
        std::ifstream inFile("accounts.txt");
        if (!inFile) {
            // File doesn't exist yet (first run), that's okay. nextAccountNumber remains 1.
            std::cout << "No existing accounts file found. Starting with a fresh slate.\n";
            return;
        }

        accounts.clear(); // Ensure the vector is empty before loading
        int maxAccNum = 0; // Track the highest account number found to set nextAccountNumber correctly

        Account tempAccount(0, "", 0); // Temporary Account object to load data into
        while (Account::loadFromFile(inFile, tempAccount)) {
            accounts.push_back(tempAccount);
            maxAccNum = std::max(maxAccNum, tempAccount.getAccountNumber());
        }
        inFile.close();

        // Set nextAccountNumber based on the highest account number loaded + 1
        nextAccountNumber = maxAccNum + 1;
        std::cout << "Accounts loaded. Next account number will be: " << nextAccountNumber << "\n";
    }

    void run() {
        std::cout << "\n=== Simple Banking Application ===\n";

        while (true) {
            std::cout << "\n--- Main Menu ---\n"; // Added menu title
            std::cout << "1. Create New Account\n"
                      << "2. Deposit Money\n"
                      << "3. Withdraw Money\n"
                      << "4. Check Balance\n"
                      << "5. View All Accounts\n"
                      << "6. Exit\n";

            int choice = getIntInput("Enter your choice: "); // getIntInput handles its own clearBuffer

            switch (choice) {
                case 1: createAccount(); break;
                case 2: deposit(); break;
                case 3: withdraw(); break;
                case 4: checkBalance(); break;
                case 5: viewAllAccounts(); break;
                case 6:
                    saveAccounts();
                    std::cout << "Thank you for using our banking system!\n";
                    return; // Exit the run function and thus main
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};

int main() {
    BankingApplication app;
    app.run();
    return 0;
}
