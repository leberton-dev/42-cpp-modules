#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
    public:
    Harl ();
    ~Harl ();
    void complain (int start);
    void complainFilter (std::string level);

    private:
    void debug (void);
    void info (void);
    void warning (void);
    void error (void);
};

#endif
