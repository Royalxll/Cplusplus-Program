#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include "Investment.h"

// Helpers
double promptForPositiveDouble(const std::string& prompt);
int promptForPositiveInt(const std::string& prompt);
bool promptYesNo(const std::string& prompt);
void displayReportHeader(const std::string& title);
void displayYearEndRow(const YearEndSummary& summary);
void displayReport(const std::vector<YearEndSummary>& summaries, const std::string& title);

int main() {
    std::cout << "Welcome to the Airgead Banking Investment Simulator\n\n";

    bool keepRunning = true;
    while (keepRunning) {
        double initialInvestment = promptForPositiveDouble("Enter Initial Investment Amount: ");
        double monthlyDeposit = promptForPositiveDouble("Enter Monthly Deposit: ");
        double annualInterestRate = promptForPositiveDouble("Enter Annual Interest (%): ");
        int numberOfYears = promptForPositiveInt("Enter Number of Years: ");

        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        InvestmentAccount userInvestment(initialInvestment, monthlyDeposit, annualInterestRate, numberOfYears);

        userInvestment.calculateYearlyReportWithoutDeposits();
        userInvestment.calculateYearlyReportWithDeposits();

        displayReport(userInvestment.getYearEndSummariesWithoutDeposits(),
            "Year-end Balances and Interest (No Monthly Deposits)");
        displayReport(userInvestment.getYearEndSummariesWithDeposits(),
            "Year-end Balances and Interest (With Monthly Deposits)");

        keepRunning = promptYesNo("Would you like to run another simulation? (Y/N): ");
        std::cout << "\n";
    }

    std::cout << "Thank you for using the simulator. Goodbye!\n";
    return 0;
}

// Input validation helpers
double promptForPositiveDouble(const std::string& prompt) {
    double value = -1.0;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value < 0.0) {
            std::cout << "Value must be non-negative.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

int promptForPositiveInt(const std::string& prompt) {
    int value = -1;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (value <= 0) {
            std::cout << "Must be greater than 0.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

bool promptYesNo(const std::string& prompt) {
    std::string response;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, response);
        if (response.empty()) continue;
        char c = std::toupper(response[0]);
        if (c == 'Y') return true;
        if (c == 'N') return false;
        std::cout << "Please answer Y or N.\n";
    }
}

// Output formatting
void displayReportHeader(const std::string& title) {
    std::cout << "\n" << title << "\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::left << std::setw(8) << "Year"
        << std::right << std::setw(20) << "Year End Balance"
        << std::right << std::setw(20) << "Year End Interest\n";
    std::cout << "----------------------------------------------\n";
}

void displayYearEndRow(const YearEndSummary& summary) {
    std::cout << std::left << std::setw(8) << summary.year
        << std::right << std::setw(20) << std::fixed << std::setprecision(2) << summary.yearEndBalance
        << std::right << std::setw(20) << std::fixed << std::setprecision(2) << summary.yearEndInterestEarned
        << "\n";
}

void displayReport(const std::vector<YearEndSummary>& summaries, const std::string& title) {
    displayReportHeader(title);
    for (const auto& s : summaries) {
        displayYearEndRow(s);
    }
}
