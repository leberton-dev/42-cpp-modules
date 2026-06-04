#include "Program.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

Program::Program () : _is_running (true) {
}

void Program::run () {
    std::string cmd;

    while (_is_running) {
        _print_commands ();
        cmd = _getField ("Enter a command: ");
        if (!_is_running)
            break;
        _handle_command (cmd);
    }
}


void Program::_print_commands (void) {
    std::cout << "Commands:" << std::endl;
    std::cout << "\t1. ADD" << std::endl;
    std::cout << "\t2. SEARCH" << std::endl;
    std::cout << "\t3. EXIT" << std::endl;
}

void Program::_handle_command (std::string cmd) {
    if (cmd == "ADD")
        _add ();
    else if (cmd == "SEARCH")
        _search ();
    else if (cmd == "EXIT")
        _exit ();
    else
        std::cout << "[ ERROR ] Invalid command, please enter a command ( "
                     "ADD, SEARCH, EXIT )"
                  << std::endl;
}


std::string Program::_getField (const std::string& prompt) {
    std::string field;

    if (!_is_running)
        return ("");
    std::cout << prompt;
    while (!std::getline (std::cin, field) || field.empty ()) {
        if (!std::cin) {
            _is_running = false;
            return ("");
        }
        std::cout << "[ ERROR ] Field cannot be empty" << std::endl;
        std::cout << prompt;
    }

    return (field);
}


std::string Program::_truncate (const std::string& field) {
    if (field.length () <= 10)
        return (field);
    return (field.substr (0, 9) + ".");
}

void Program::_add (void) {
    std::string firstName     = _getField ("Enter your first name: ");
    std::string lastName      = _getField ("Enter your last name: ");
    std::string nickName      = _getField ("Enter your nickname: ");
    std::string phoneNumber   = _getField ("Enter your phone number: ");
    std::string darkestSecret = _getField ("Enter your darkest secret: ");

    if (!_is_running)
        return;

    Contact contact (firstName, lastName, nickName, phoneNumber, darkestSecret);

    if (_phoneBook.addContact (&contact) != 0)
        std::cout
        << "[ ERROR ] Adding new contact. Please inform the student right now."
        << std::endl;
    else
        std::cout << "Added contact successfully." << std::endl;
}

void Program::_displayHeaderShort (void) {
    std::string columns[4] = {
        "Index",
        "First Name",
        "Last Name",
        "Nickname",
    };
    for (int i = 0; i < 4; i++) {
        std::cout << std::setw (10) << std::right << columns[i];
        std::cout << "|";
    }
    std::cout << std::endl;
}

void Program::_displayContactShort (const Contact* contact, int idx) {
    std::cout << std::setw (10) << std::right << idx;
    std::cout << "|";

    std::cout << std::setw (10) << std::right << _truncate (contact->firstName ());
    std::cout << "|";

    std::cout << std::setw (10) << std::right << _truncate (contact->lastName ());
    std::cout << "|";

    std::cout << std::setw (10) << std::right << _truncate (contact->nickName ());
    std::cout << "|" << std::endl;
}

void Program::_displayContactLong (const Contact* contact) {
    std::cout << "First name:\t" << contact->firstName () << std::endl;
    std::cout << "Last name:\t" << contact->lastName () << std::endl;
    std::cout << "Nick name:\t" << contact->nickName () << std::endl;
    std::cout << "Phone number:\t" << contact->phoneNumber () << std::endl;
    std::cout << "Darkest secret:\t" << contact->darkestSecret () << std::endl;
}

void Program::_search (void) {
    if (_phoneBook.count () == 0) {
        std::cout << "[ WARNING ]: Phone book is empty." << std::endl;
        return;
    }

    _displayHeaderShort ();
    for (int i = 0; i < _phoneBook.count (); i++)
        _displayContactShort (_phoneBook.contact (i), i + 1);

    std::string idx;
    std::cout << "Enter index ( 1-" << _phoneBook.count () << " or 'b' to go back ): ";
    if (!std::getline (std::cin, idx)) {
        _is_running = false;
        return;
    }

    bool correct = false;
    while (!correct) {
        correct = true;

        if (idx.empty ())
            correct = false;

        if (idx == "b")
            return;

        if (std::atoi (idx.c_str ()) > _phoneBook.count () || std::atoi (idx.c_str ()) <= 0)
            correct = false;

        if (!correct) {
            std::cout << "[ ERROR ] Index must be an integer between 1 and "
                      << _phoneBook.count () << std::endl;
            std::cout << "Enter index ( 1-" << _phoneBook.count () << " or 'b' to go back ): ";
            if (!std::getline (std::cin, idx)) {
                _is_running = false;
                return;
            }
        }
    }
    _displayContactLong (_phoneBook.contact (std::atoi (idx.c_str ()) - 1));
}

void Program::_exit (void) {
    std::string yn;
    std::cout
    << "[ WARNING ] Closing PhoneBook, all contacts will be deleted forever."
    << std::endl;
    std::cout << "Are you sure about that ? ( y/n ): ";
    if (!std::getline (std::cin, yn)) {
        _is_running = false;
        return;
    }
    while (yn != "y" && yn != "n") {
        std::cout
        << "[ ERROR ] Please choose between 'y' or 'n' and press 'Enter': ";
        if (!std::getline (std::cin, yn)) {
            _is_running = false;
            return;
        }
    }
    if (yn == "n")
        return;
    _is_running = false;
    std::cout << "[ WARNING ] All PhoneBook contacts are now deleted. Good bye."
              << std::endl;
}
