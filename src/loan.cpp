#include "Loan.h"
#include <cmath>
#include <limits>

using std::pow;

const long double Loan::MAX_PRINCIPAL = 1e15L;
const long double Loan::MAX_ANNUAL_RATE = 1e6L;
const int Loan::MAX_YEARS = 10000;

Loan::Loan()
    : principal(0.0L), annualRatePercent(0.0L), years(0)
    {}

Loan::Loan(long double principal_, long double annualRatePercent_, int years_)
    : principal(principal_), annualRatePercent(annualRatePercent_), years(years_)
    {}

void Loan::setPrincipal(long double p) { principal = p; }
void Loan::setAnnualRatePercent(long double r) { annualRatePercent = r; }
void Loan::setYears(int y) { years = y; }

long double Loan::getPrincipal() const { return principal; }
long double Loan::getAnnualRatePercent() const { return annualRatePercent; }
int Loan::getYears() const { return years; }

// Validation Checks
int Loan::validate() const
{

    if (!(principal > 0.0L) || !(annualRatePercent >= 0.0L) || !(years > 0))
    {

        return VALID_NEGATIVE_OR_ZERO;
    }

    if (principal > MAX_PRINCIPAL || fabsl(annualRatePercent) > MAX_ANNUAL_RATE || years > MAX_YEARS)
    {
        return VALID_OVERFLOW_LIKE;
    }

    if (!std::isfinite((double)principal) || !std::isfinite((double)annualRatePercent))
    {
        return VALID_OVERFLOW_LIKE;
    }

    return VALID_OK;
}

long double Loan::calculateSimpleTotal() const
{
    long double y = (long double)years;
    long double total = (y * principal) + (y * principal * (annualRatePercent / 100.0L));
    return total;
}

long double Loan::calculateMonthlySimple() const
{
    long double total = calculateSimpleTotal();
    long double months = (long double)(years * 12);
    if (months <= 0.0L)
        return 0.0L;
    return total / months;
}

long double Loan::calculateEMI() const
{
    int n = years * 12;
    if (n <= 0)
        return 0.0L;

    long double P = principal;
    long double r_month = (annualRatePercent / 100.0L) / 12.0L;

    if (fabsl(r_month) < 1e-18L)
    {
        return P / (long double)n;
    }

    long double base = 1.0L + r_month;
    long double powTerm = powl(base, (long double)n);

    long double denom = powTerm - 1.0L;
    if (fabsl(denom) < 1e-18L)
    {
        return P / (long double)n;
    }

    long double emi = P * r_month * powTerm / denom;
    return emi;
}
