#ifndef INVESTMENT_H
#define INVESTMENT_H

#include <vector>

// YearEndSummary struct stores a year number, the balance at year-end, and interest earned during that year.
struct YearEndSummary {
    int year;
    double yearEndBalance;
    double yearEndInterestEarned;
};

// InvestmentAccount models an investment with optional monthly deposits and provides
// methods to calculate year-end summaries with and without monthly deposits.
class InvestmentAccount {
public:
    InvestmentAccount(double initialInvestment, double monthlyDeposit, double annualInterestRate, int numberOfYears);

    // Calculate year-end summaries for scenario with monthly deposits.
    void calculateYearlyReportWithDeposits();

    // Calculate year-end summaries for scenario without monthly deposits.
    void calculateYearlyReportWithoutDeposits();

    // Accessors
    const std::vector<YearEndSummary>& getYearEndSummariesWithDeposits() const;
    const std::vector<YearEndSummary>& getYearEndSummariesWithoutDeposits() const;

private:
    double initialInvestment_;
    double monthlyDeposit_;
    double annualInterestRate_; // percent, e.g., 5.0 for 5%
    int numberOfYears_;

    std::vector<YearEndSummary> summariesWithDeposits_;
    std::vector<YearEndSummary> summariesWithoutDeposits_;
};

#endif // INVESTMENT_H
#pragma once
