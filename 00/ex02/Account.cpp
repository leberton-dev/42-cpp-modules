#include "Account.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>

int Account::_nbAccounts         = 0;
int Account::_totalAmount        = 0;
int Account::_totalNbDeposits    = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts (void) {
    return (_nbAccounts);
}

int Account::getTotalAmount (void) {
    return (_totalAmount);
}

int Account::getNbDeposits (void) {
    return (_totalNbDeposits);
}

int Account::getNbWithdrawals (void) {
    return (_totalNbWithdrawals);
}

void Account::displayAccountsInfos (void) {
    _displayTimestamp ();
    std::cout << "accounts:" << _nbAccounts << ";total:" << _totalAmount
              << ";deposits:" << _totalNbDeposits
              << ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

Account::Account (int initial_deposit)
: _accountIndex (_nbAccounts), _amount (initial_deposit), _nbDeposits (0),
  _nbWithdrawals (0) {
    _displayTimestamp ();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount
              << ";created" << std::endl;
    _nbAccounts += 1;
    _totalAmount += initial_deposit;
}
Account::~Account (void) {
    _displayTimestamp ();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed"
              << std::endl;
}

void Account::makeDeposit (int deposit) {
    _totalNbDeposits++;
    _nbDeposits++;
    _amount += deposit;
    _totalAmount += deposit;
    _displayTimestamp ();
    std::cout << "index:" << _accountIndex << ";p_amount:" << _amount - deposit
              << ";deposit:" << deposit << ";amount:" << _amount
              << ";nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal (int withdrawal) {
    _displayTimestamp ();
    if (_amount - withdrawal < 0) {
        std::cout << "index:" << _accountIndex << ";p_amount:" << _amount
                  << ";withdrawal:refused" << std::endl;
        return (false);
    }
    _amount -= withdrawal;
    _totalAmount -= withdrawal;
    _nbWithdrawals++;
    _totalNbWithdrawals++;
    std::cout << "index:" << _accountIndex << ";p_amount:" << _amount + withdrawal
              << ";withdrawal:" << withdrawal << ";amount:" << _amount
              << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
    return (true);
}

int Account::checkAmount (void) const {
    return (_amount);
}

void Account::displayStatus (void) const {
    _displayTimestamp ();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount
              << ";deposits:" << _nbDeposits
              << ";withdrawals:" << _nbWithdrawals << std::endl;
}

void Account::_displayTimestamp (void) {
    time_t time                = std::time (NULL);
    struct tm* broke_down_time = std::localtime (&time);
    std::cout << "[" << std::setfill ('0') << broke_down_time->tm_year + 1900
              << std::setw (2) << broke_down_time->tm_mon + 1 << std::setw (2)
              << broke_down_time->tm_mday << "_" << std::setw (2)
              << broke_down_time->tm_hour << std::setw (2) << broke_down_time->tm_min
              << std::setw (2) << broke_down_time->tm_sec << "] ";
}
