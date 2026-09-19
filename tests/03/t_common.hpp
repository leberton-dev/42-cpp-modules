#ifndef T_COMMON_HPP
#define T_COMMON_HPP

#include "check.hpp"
#include <cstdlib>
#include <cstring>
#include <climits>
#include <string>

// helpers shared by the ClapTrap/ScavTrap/FragTrap/DiamondTrap test suites.
// They rely on the student's public ClapTrap::log() to read hit/energy/attack points.

struct Stats { int hp, ep, ad; };

inline int field(const std::string &o, const char *key) {
	size_t p = o.find(key);
	if (p == std::string::npos) return -999999;
	return std::atoi(o.c_str() + p + std::strlen(key));
}

template <class T> inline Stats stats(T &t) {
	chk::Capture c;
	t.log();
	std::string o = c.stop();
	Stats s;
	s.hp = field(o, "-HP: ");
	s.ep = field(o, "-EP: ");
	s.ad = field(o, "-AD: ");
	return s;
}

inline std::string num(long n) { std::ostringstream o; o << n; return o.str(); }

// sequence of classes mentioned in the lines of `o` ("C"lap "S"cav "F"rag "D"iamond), first class of each line
inline std::string seq(const std::string &o) {
	std::string r;
	std::istringstream in(o);
	std::string l;
	while (std::getline(in, l)) {
		const char *names[] = {"ClapTrap", "ScavTrap", "FragTrap", "DiamondTrap"};
		const char code[] = {'C', 'S', 'F', 'D'};
		size_t best = std::string::npos;
		char b = 0;
		for (int i = 0; i < 4; i++) {
			size_t p = l.find(names[i]);
			if (p != std::string::npos && p < best) { best = p; b = code[i]; }
		}
		if (b) r += b;
	}
	return r;
}

#define CLEAN(cap) chk::stripAnsi((cap).stop())

#endif
