#include "Investment.h"
#include <cmath>    // for std::round

// Constructor initializes members
InvestmentAccount::InvestmentAccount(double initialInvestment, double monthlyDeposit,
    double annualInterestRate, int numberOfYears)
    : initialInvestment_(initialInvestment),
    monthlyDeposit_(monthlyDeposit),
    annualInterestRate_(annualInterestRate),
    numberOfYears_(numberOfYears) {
}

// Helper: round to 2 decimal places
static double roundToCents(double value) {
    return std::round(value * 100.0) / 100.0;
}

void InvestmentAccount::calculateYearlyReportWithDeposits() {
    summariesWithDeposits_.clear();
    int months = numberOfYears_ * 12;
    double monthlyInterestRate = (annualInterestRate_ / 100.0) / 12.0;
    double openingBalance = initialInvestment_;
    double accumulatedInterestForYear = 0.0;

    for (int month = 1; month <= months; ++month) {
        double totalBeforeInterest = openingBalance + monthlyDeposit_;
        double interestThisMonth = totalBeforeInterest * monthlyInterestRate;
        double closingBalance = totalBeforeInterest + interestThisMonth;

        accumulatedInterestForYear += interestThisMonth;

        if (month % 12 == 0) {
            YearEndSummary summary;
            summary.year = month / 12;
            summary.yearEndBalance = roundToCents(closingBalance);
            summary.yearEndInterestEarned = roundToCents(accumulatedInterestForYear);
            summariesWithDeposits_.push_back(summary);
            accumulatedInterestForYear = 0.0;
        }
        openingBalance = closingBalance;
    }
}

void InvestmentAccount::calculateYearlyReportWithoutDeposits() {
    summariesWithoutDeposits_.clear();
    int months = numberOfYears_ * 12;
    double monthlyInterestRate = (annualInterestRate_ / 100.0) / 12.0;
    double openingBalance = initialInvestment_;
    double accumulatedInterestForYear = 0.0;

    for (int month = 1; month <= months; ++month) {
        double totalBeforeInterest = openingBalance;
        double interestThisMonth = totalBeforeInterest * monthlyInterestRate;
        double closingBalance = totalBeforeInterest + interestThisMonth;

        accumulatedInterestForYear += interestThisMonth;

        if (month % 12 == 0) {
            YearEndSummary summary;
            summary.year = month / 12;
            summary.yearEndBalance = roundToCents(closingBalance);
            summary.yearEndInterestEarned = roundToCents(accumulatedInterestForYear);
            summariesWithoutDeposits_.push_back(summary);
            accumulatedInterestForYear = 0.0;
        }
        openingBalance = closingBalance;
    }
}

const std::vector<YearEndSummary>& InvestmentAccount::getYearEndSummariesWithDeposits() const {
    return summariesWithDeposits_;
}

const std::vector<YearEndSummary>& InvestmentAccount::getYearEndSummariesWithoutDeposits() const {
    return summariesWithoutDeposits_;
}
