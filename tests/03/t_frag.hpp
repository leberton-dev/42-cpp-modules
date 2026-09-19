#ifndef T_FRAG_HPP
#define T_FRAG_HPP

#include "FragTrap.hpp"
#include "t_common.hpp"

inline void test_frag() {
	{
		chk::Capture c;
		{ FragTrap s("Frag"); }
		std::string o = CLEAN(c);
		CHECK("FragTrap: construction chain is Clap -> Frag, destruction Frag -> Clap", seq(o) == "CFFC");
		CHECK("FragTrap: exactly 4 lines", chk::lineCount(o) == 4);
		CHECK("FragTrap: own ctor message present", chk::linesWith(o, "FragTrap", "constructor", "destructor") == 1);
		CHECK("FragTrap: own dtor message present", chk::linesWith(o, "FragTrap", "destructor") == 1);
		CHECK("FragTrap: ctor/dtor lines end with newline", !o.empty() && o[o.size() - 1] == '\n');
	}
	{
		chk::Capture c;
		{ FragTrap s; }
		CHECK("FragTrap: default ctor chain", seq(CLEAN(c)) == "CFFC");
	}
	{
		FragTrap s("Frag");
		Stats st = stats(s);
		CHECK("FragTrap: hit points 100", st.hp == 100);
		CHECK("FragTrap: energy points 100", st.ep == 100);
		CHECK("FragTrap: attack damage 30", st.ad == 30);
		FragTrap d;
		Stats t = stats(d);
		CHECK("FragTrap: default ctor also 100/100/30", t.hp == 100 && t.ep == 100 && t.ad == 30);
	}
	{
		FragTrap s("Frag");
		chk::Capture c; s.attack("Target"); std::string o = CLEAN(c);
		CHECK("FragTrap attack: 'attacks Target, causing 30 points of damage!'", chk::has(o, "attacks Target, causing 30 points of damage!"));
		CHECK("FragTrap attack costs 1 energy", stats(s).ep == 99);
		int n = 1;
		for (int i = 0; i < 110; i++) { chk::Capture c2; s.attack("T"); std::string o2 = CLEAN(c2); if (chk::has(o2, "attacks T")) n++; }
		CHECK("FragTrap: exactly 100 attacks possible", n == 100);
	}
	{
		FragTrap s("Frag");
		chk::Capture c; s.highFivesGuys(); std::string o = CLEAN(c);
		CHECK("highFivesGuys: one line, positive high-five request", chk::lineCount(o) == 1 && chk::has(chk::lower(o), "high") && chk::has(chk::lower(o), "five"));
		CHECK("highFivesGuys: free (no energy)", stats(s).ep == 100);
	}
	{
		FragTrap s("Frag");
		{ chk::Capture c; s.takeDamage(30); s.beRepaired(10); c.stop(); }
		CHECK("inherited takeDamage/beRepaired: 100-30+10 = 80, ep 99", stats(s).hp == 80 && stats(s).ep == 99);
		{ chk::Capture c; s.takeDamage(4294967295u); c.stop(); }
		CHECK("FragTrap takeDamage(UINT_MAX): hp 0", stats(s).hp == 0);
		chk::Capture c; s.attack("x"); std::string o = CLEAN(c);
		CHECK("dead FragTrap cannot attack", !chk::has(o, "attacks x"));
	}
	{
		FragTrap s("Frag");
		{ chk::Capture c; s.attack("x"); s.takeDamage(10); c.stop(); }
		chk::Capture c;
		{ FragTrap k(s); }
		std::string o = CLEAN(c);
		CHECK("FragTrap copy ctor chain", seq(o) == "CFFC");
		FragTrap k2(s);
		Stats st = stats(k2);
		CHECK("FragTrap copy keeps hp/ep/ad (90/99/30)", st.hp == 90 && st.ep == 99 && st.ad == 30);
		{ chk::Capture c2; k2.takeDamage(10); c2.stop(); }
		CHECK("FragTrap copy is independent", stats(s).hp == 90 && stats(k2).hp == 80);
		FragTrap z("Z");
		{ chk::Capture c2; z = s; std::string o2 = CLEAN(c2); CHECK("FragTrap assignment prints a message", chk::has(chk::lower(o2), "assign")); }
		CHECK("FragTrap assignment keeps hp/ep/ad", stats(z).hp == 90 && stats(z).ep == 99 && stats(z).ad == 30);
		FragTrap &self = s;
		{ chk::Capture c2; s = self; c2.stop(); }
		CHECK("FragTrap self-assignment", stats(s).hp == 90);
	}
	{
		FragTrap a("A"), b("B");
		{ chk::Capture c; a.attack("x"); a.takeDamage(50); c.stop(); }
		CHECK("two FragTraps have independent state", stats(b).hp == 100 && stats(b).ep == 100 && stats(a).hp == 50);
	}
}

#endif
