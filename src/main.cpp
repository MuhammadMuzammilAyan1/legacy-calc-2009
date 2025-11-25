#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Loan.h"

using namespace std;

int main()
{
    const string infile = "config.txt";

    ifstream fin(infile.c_str());
    if (!fin.is_open())
    {
        cerr << "Error: cannot open input file '" << infile << "'\n";
        return 1;
    }

    vector<Loan> loans;
    string line;
    int lineno = 0;
    while (std::getline(fin, line))
    {
        ++lineno;
        if (line.empty())
            continue;

        istringstream iss(line);
        long double p = 0.0L;
        long double r = 0.0L;
        int y = 0;

        if (!(iss >> p >> r >> y))
        {
            cerr << "Skipping malformed line " << lineno << ": \"" << line << "\"\n";
            continue;
        }

        Loan L(p, r, y);
        loans.push_back(L);
    }
    fin.close();

    if (loans.empty())
    {
        cout << "No loan entries found in " << infile << "\n";
        return 0;
    }

    cout << fixed << setprecision(2);

    for (size_t i = 0; i < loans.size(); ++i)
    {
        Loan &L = loans[i];
        int code = L.validate();
        cout << "Loan #" << (i + 1) << ":\n";
        cout << "  Principal: " << (double)L.getPrincipal() << "\n";
        cout << "  Annual Rate (%): " << (double)L.getAnnualRatePercent() << "\n";
        cout << "  Years: " << L.getYears() << "\n";

        if (code == Loan::VALID_OK)
        {
            long double total = L.calculateSimpleTotal();
            long double monthlySimple = L.calculateMonthlySimple();
            long double emi = L.calculateEMI();

            cout << "  Is Valid: Yes\n";
            cout << "  Simple total: " << (double)total << "\n";
            cout << "  Monthly (simple): " << (double)monthlySimple << "\n";
            cout << "  EMI: " << (double)emi << "\n";
        }
        else if (code == Loan::VALID_NEGATIVE_OR_ZERO)
        {
            cout << "  Is Valid: No, NEGATIVE/ZERO input detected\n";
        }
        else
        {
            cout << "  Is Valid: No, OVERFLOW-LIKE / INVALID input detected\n";
        }

        cout << "---------------------------------\n";
    }

    cout << "Processing complete.\n";
    return 0;
}
