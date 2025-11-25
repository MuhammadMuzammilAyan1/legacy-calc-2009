#ifndef LOAN_H
#define LOAN_H

#include <string>

class Loan
{
public:
    static const int VALID_OK = 0;
    static const int VALID_NEGATIVE_OR_ZERO = 1;
    static const int VALID_OVERFLOW_LIKE = 2;

    Loan();
    Loan(long double principal_, long double annualRatePercent_, int years_);

    void setPrincipal(long double p);
    void setAnnualRatePercent(long double r);
    void setYears(int y);

    int validate() const;

    long double calculateSimpleTotal() const;

    long double calculateMonthlySimple() const;

    long double calculateEMI() const;

    long double getPrincipal() const;
    long double getAnnualRatePercent() const;
    int getYears() const;

private:
    long double principal;
    long double annualRatePercent;
    int years;

    static const long double MAX_PRINCIPAL;
    static const long double MAX_ANNUAL_RATE;
    static const int MAX_YEARS;
};

#endif
