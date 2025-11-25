#include <iostream>
#include <fstream>
#include <limits>
#include "Loan.h"

using namespace std;

// Function to get validated double input
double getValidatedDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive number.\n";
        } else {
            break;
        }
    }
    return value;
}

// Function to get validated int input
int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a positive integer.\n";
        } else {
            break;
        }
    }
    return value;
}

// Function to process loan calculation
void processLoan(double principal, double rate, int months) {
    // Simple overflow warning
    if (principal > 1e12 || months > 1e5) {
        cout << "Warning: values are very large, calculation may overflow.\n";
    }

    Loan loan(principal, rate, months); // Using your Loan class
    double emi = loan.calculateEMI();

    cout << "Monthly EMI = " << emi << "\n";
}

int main() {
    char choice = 'y';
    char inputChoice;

    cout << "==== Normal EMI Calculator ====\n";
    cout << "Do you want to read input from a file? (y/n): ";
    cin >> inputChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (inputChoice == 'y' || inputChoice == 'Y') {
        string filename;
        cout << "Enter filename: ";
        getline(cin, filename);

        ifstream fin(filename);
        if (!fin) {
            cerr << "Error: Cannot open file " << filename << "\n";
            return 1;
        }

        double principal, rate;
        int months;
        while (fin >> principal >> rate >> months) {
            cout << "\nProcessing loan from file:\n";
            processLoan(principal, rate, months);
        }

        fin.close();
        cout << "File processing complete.\n";
        return 0;
    }

    // User input loop
    while (choice == 'y' || choice == 'Y') {
        double principal = getValidatedDouble("Enter principal amount: ");
        double rate = getValidatedDouble("Enter annual interest rate (in %): ");
        int months = getValidatedInt("Enter tenure (in months): ");

        processLoan(principal, rate, months);

        cout << "Do you want to calculate EMI for another loan? (y/n): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Thank you for using Normal EMI Calculator.\n";
    return 0;
}
