#ifndef T_CLAP_HPP
#define T_CLAP_HPP

#include "ClapTrap.hpp"
#include "t_common.hpp"

inline void test_clap() {
	// ---- construction / destruction messages ----
	{
		chk::Capture c;
		{ ClapTrap a("Bob"); }
		std::string o = CLEAN(c);
		CHECK("ClapTrap: ctor prints exactly one line with the name", chk::linesWith(o, "Bob", "constructor", "destructor") == 1);
		CHECK("ClapTrap: dtor prints exactly one line with the name", chk::linesWith(o, "Bob", "destructor") == 1);
		CHECK("ClapTrap: ctor line before dtor line", chk::inOrder(o, "constructor", "destructor"));
		CHECK("ClapTrap: messages end with newline", !o.empty() && o[o.size() - 1] == '\n');
	}
	{
		chk::Capture c;
		{ ClapTrap a; }
		std::string o = CLEAN(c);
		CHECK("ClapTrap: default ctor + dtor print 1 line each", chk::lineCount(o) == 2);
	}
	{
		ClapTrap a("Bob");
		chk::Capture c;
		{ ClapTrap b(a); }
		std::string o = CLEAN(c);
		CHECK("ClapTrap: copy ctor prints a message mentioning 'copy'", chk::has(chk::lower(o), "copy"));
	}
	{
		ClapTrap a("A"), b("B");
		chk::Capture c;
		b = a;
		std::string o = CLEAN(c);
		CHECK("ClapTrap: copy assignment prints a message mentioning 'assign'", chk::has(chk::lower(o), "assign"));
	}
	// ---- initial values ----
	{
		ClapTrap a("Bob");
		Stats s = stats(a);
		CHECK("ClapTrap: hit points start at 10", s.hp == 10);
		CHECK("ClapTrap: energy points start at 10", s.ep == 10);
		CHECK("ClapTrap: attack damage starts at 0", s.ad == 0);
		ClapTrap d;
		Stats t = stats(d);
		CHECK("ClapTrap: default ctor also 10/10/0", t.hp == 10 && t.ep == 10 && t.ad == 0);
	}
	// ---- attack ----
	{
		ClapTrap a("Bob");
		chk::Capture c;
		a.attack("Target");
		std::string o = CLEAN(c);
		CHECK("attack: subject wording 'ClapTrap Bob attacks Target, causing 0 points of damage!'",
			chk::has(o, "ClapTrap Bob attacks Target, causing 0 points of damage!"));
		CHECK("attack: exactly one line", chk::lineCount(o) == 1);
		CHECK("attack: costs 1 energy", stats(a).ep == 9);
		CHECK("attack: does not change hit points", stats(a).hp == 10);
	}
	{
		ClapTrap a("Bob");
		int okAtt = 0;
		for (int i = 0; i < 10; i++) {
			chk::Capture c; a.attack("T"); std::string o = CLEAN(c);
			if (chk::has(o, "attacks")) okAtt++;
		}
		CHECK("attack: exactly 10 successful attacks with 10 energy", okAtt == 10);
		CHECK("attack: energy is 0 after 10 attacks", stats(a).ep == 0);
		chk::Capture c; a.attack("T"); std::string o = CLEAN(c);
		CHECK("attack: 11th attack fails (no 'attacks' message)", !chk::has(o, "attacks T"));
		CHECK("attack: failure still prints a line", chk::lineCount(o) == 1);
		CHECK("attack: energy never goes negative", stats(a).ep == 0);
		chk::Capture c2; a.takeDamage(1); std::string o2 = CLEAN(c2);
		CHECK("takeDamage still works with 0 energy", chk::has(o2, "took") && stats(a).hp == 9);
	}
	// ---- takeDamage ----
	{
		ClapTrap a("Bob");
		{ chk::Capture c; a.takeDamage(3); std::string o = CLEAN(c);
		  CHECK("takeDamage(3): hp 7", stats(a).hp == 7);
		  CHECK("takeDamage: message mentions amount", chk::has(o, "3"));
		  CHECK("takeDamage: does not cost energy", stats(a).ep == 10); }
		{ chk::Capture c; a.takeDamage(0); c.stop(); CHECK("takeDamage(0): hp unchanged", stats(a).hp == 7); }
		{ chk::Capture c; a.takeDamage(7); c.stop(); CHECK("takeDamage(exact remaining): hp 0", stats(a).hp == 0); }
		{ chk::Capture c; a.takeDamage(5); std::string o = CLEAN(c);
		  CHECK("takeDamage on a dead robot: hp stays 0 (no negative)", stats(a).hp == 0);
		  CHECK("takeDamage on a dead robot: prints one line", chk::lineCount(o) == 1); }
	}
	{
		ClapTrap a("Bob");
		{ chk::Capture c; a.takeDamage(11); c.stop(); CHECK("takeDamage(11) with 10hp: hp == 0, not -1", stats(a).hp == 0); }
	}
	{
		unsigned int big[] = {2147483647u, 2147483648u, 2147483658u, 4294967295u};
		const char *names[] = {"INT_MAX", "INT_MAX+1", "INT_MAX+11", "UINT_MAX"};
		for (int i = 0; i < 4; i++) {
			ClapTrap a("Bob");
			chk::Capture c; a.takeDamage(big[i]); c.stop();
			CHECK(std::string("takeDamage(") + names[i] + "): hp == 0 (no signed wrap to positive/negative)", stats(a).hp == 0);
		}
	}
	{
		ClapTrap a("Bob");
		chk::Capture c; a.takeDamage(4294967295u); std::string o = CLEAN(c);
		CHECK("takeDamage(UINT_MAX): message prints the real amount 4294967295 (not -1)", chk::has(o, "4294967295"));
	}
	// ---- beRepaired ----
	{
		ClapTrap a("Bob");
		{ chk::Capture c; a.beRepaired(5); std::string o = CLEAN(c);
		  Stats s = stats(a);
		  CHECK("beRepaired(5): hp 15", s.hp == 15);
		  CHECK("beRepaired: costs 1 energy", s.ep == 9);
		  CHECK("beRepaired: message mentions amount", chk::has(o, "5"));
		  CHECK("beRepaired: exactly one line", chk::lineCount(o) == 1); }
		{ chk::Capture c; a.beRepaired(0); c.stop(); Stats s = stats(a);
		  CHECK("beRepaired(0): hp unchanged", s.hp == 15);
		  CHECK("beRepaired(0): still costs energy", s.ep == 8); }
	}
	{
		ClapTrap a("Bob");
		for (int i = 0; i < 10; i++) { chk::Capture c; a.beRepaired(1); c.stop(); }
		CHECK("repair: energy 0 after 10 repairs, hp 20", stats(a).ep == 0 && stats(a).hp == 20);
		chk::Capture c; a.beRepaired(1); std::string o = CLEAN(c);
		CHECK("repair: fails with 0 energy (hp unchanged)", stats(a).hp == 20);
		CHECK("repair: failure prints a line and no 'repairs itself'", chk::lineCount(o) == 1 && !chk::has(o, "repairs itself"));
	}
	{
		ClapTrap a("Bob");
		{ chk::Capture c; a.takeDamage(10); c.stop(); }
		chk::Capture c; a.beRepaired(5); std::string o = CLEAN(c);
		Stats s = stats(a);
		CHECK("repair: dead robot cannot repair (hp stays 0)", s.hp == 0);
		CHECK("repair: dead robot keeps its energy", s.ep == 10);
		CHECK("repair: dead robot -> failure line", chk::lineCount(o) == 1 && !chk::has(o, "repairs itself"));
		chk::Capture c2; a.attack("T"); std::string o2 = CLEAN(c2);
		CHECK("attack: dead robot cannot attack", !chk::has(o2, "attacks T") && stats(a).ep == 10);
	}
	{
		ClapTrap a("Bob");
		chk::Capture c; a.beRepaired(4294967295u); std::string o = CLEAN(c);
		int hp = stats(a).hp;
		CHECK("beRepaired(UINT_MAX): hp does not wrap negative / stay <= 10", hp > 10);
		CHECK("beRepaired(UINT_MAX): message prints the real amount 4294967295 (not -1)", chk::has(o, "4294967295"));
		chk::Capture c2; a.beRepaired(4294967295u); c2.stop();
		CHECK("second huge repair: hp still positive", stats(a).hp > 10);
		chk::Capture c3; a.takeDamage(1); c3.stop();
		CHECK("robot with saturated hp still takes damage", stats(a).hp < hp);
	}
	{
		ClapTrap a("Bob");
		chk::Capture c; a.beRepaired(2147483647u); c.stop();
		CHECK("beRepaired(INT_MAX) from 10hp: no signed overflow, hp > 0", stats(a).hp > 0);
	}
	// ---- copy semantics ----
	{
		ClapTrap a("A");
		{ chk::Capture c; a.attack("x"); a.takeDamage(3); c.stop(); }
		ClapTrap b(a);
		Stats sa = stats(a), sb = stats(b);
		CHECK("copy ctor copies hp/ep/ad", sa.hp == sb.hp && sa.ep == sb.ep && sa.ad == sb.ad && sb.hp == 7 && sb.ep == 9);
		{ chk::Capture c; b.takeDamage(2); c.stop(); }
		CHECK("copy is independent from the original", stats(a).hp == 7 && stats(b).hp == 5);
		ClapTrap d("D");
		d = a;
		CHECK("assignment copies hp/ep/ad", stats(d).hp == 7 && stats(d).ep == 9);
		{ chk::Capture c; d.attack("x"); c.stop(); }
		CHECK("assigned object is independent", stats(a).ep == 9 && stats(d).ep == 8);
		ClapTrap e("E"), f("F");
		e = f = a;
		CHECK("chained assignment", stats(e).hp == 7 && stats(f).hp == 7);
		ClapTrap &self = a;
		{ chk::Capture c; a = self; c.stop(); }
		CHECK("self assignment keeps values", stats(a).hp == 7 && stats(a).ep == 9);
	}
	{
		ClapTrap a("A");
		{ chk::Capture c; a.takeDamage(10); c.stop(); }
		ClapTrap b(a);
		chk::Capture c; b.attack("x"); std::string o = CLEAN(c);
		CHECK("copy of a dead robot is dead too", !chk::has(o, "attacks x"));
	}
	{
		ClapTrap a("Bob");
		ClapTrap b("Bob");
		{ chk::Capture c; a.attack("t"); a.attack("t"); a.takeDamage(4); a.beRepaired(3); c.stop(); }
		Stats s = stats(a);
		CHECK("scripted life: 2 attacks + 4 dmg + 3 repair => hp 9, ep 7", s.hp == 9 && s.ep == 7);
		CHECK("scripted life: other instance untouched", stats(b).hp == 10 && stats(b).ep == 10);
	}
}

#endif
