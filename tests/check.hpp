#ifndef CHECK_HPP
#define CHECK_HPP

// tiny C++98 test toolkit used by the harness.cpp of each exercise.
// Results go to stderr as "@@OK\tname" / "@@KO\tname\tdetail" (parsed by run_harness).

#include <iostream>
#include <sstream>
#include <string>

namespace chk {

inline std::string oneLine(const std::string &s) {
	std::string r;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '\n') r += "\\n";
		else if (s[i] == '\t') r += " ";
		else r += s[i];
	}
	return r.size() > 200 ? r.substr(0, 200) + "..." : r;
}

inline void report(bool ok, const std::string &name, const std::string &detail) {
	if (ok) std::cerr << "@@OK\t" << name << std::endl;
	else    std::cerr << "@@KO\t" << name << "\t" << oneLine(detail) << std::endl;
}

template <typename A, typename B>
inline void eq(const std::string &name, const A &a, const B &b) {
	std::ostringstream d;
	d << "got '" << a << "', expected '" << b << "'";
	report(a == b, name, d.str());
}

// capture std::cout while alive
struct Capture {
	std::ostringstream ss; // declared first: must exist before old(...) uses it
	std::streambuf *old;
	Capture() : old(std::cout.rdbuf(ss.rdbuf())) {}
	~Capture() { stop(); }
	std::string stop() {
		if (old) { std::cout.rdbuf(old); old = 0; }
		return ss.str();
	}
};

inline std::string stripAnsi(const std::string &s) {
	std::string r;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == '\033') {
			while (i < s.size() && s[i] != 'm') i++;
		} else r += s[i];
	}
	return r;
}

inline bool has(const std::string &s, const std::string &sub) { return s.find(sub) != std::string::npos; }

inline int count(const std::string &s, const std::string &sub) {
	int n = 0;
	for (size_t p = s.find(sub); p != std::string::npos; p = s.find(sub, p + sub.size())) n++;
	return n;
}

inline int lineCount(const std::string &s) { return count(s, "\n"); }

inline std::string lower(std::string s) {
	for (size_t i = 0; i < s.size(); i++)
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
	return s;
}

// number of lines of s that contain every substring in (a, b) and not `not_`
inline int linesWith(const std::string &s, const std::string &a, const std::string &b = "", const std::string &not_ = "") {
	int n = 0;
	std::istringstream in(s);
	std::string l;
	while (std::getline(in, l)) {
		if (!has(l, a)) continue;
		if (!b.empty() && !has(l, b)) continue;
		if (!not_.empty() && has(l, not_)) continue;
		n++;
	}
	return n;
}

// every line, in order, must appear in s in that order
inline bool inOrder(const std::string &s, const std::string &a, const std::string &b) {
	size_t pa = s.find(a);
	size_t pb = s.find(b);
	return pa != std::string::npos && pb != std::string::npos && pa < pb;
}

} // namespace chk

#define CHECK(name, cond) chk::report((cond), (name), #cond)

#endif
