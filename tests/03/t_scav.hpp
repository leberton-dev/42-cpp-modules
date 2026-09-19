#ifndef T_SCAV_HPP
#define T_SCAV_HPP

#include "ScavTrap.hpp"
#include "t_common.hpp"

inline void test_scav() {
	{
		chk::Capture c;
		{ ScavTrap s("Scav"); }
		std::string o = CLEAN(c);
		CHECK("ScavTrap: construction chain is Clap -> Scav, destruction Scav -> Clap", seq(o) == "CSSC");
		CHECK("ScavTrap: exactly 4 lines (2 ctor + 2 dtor)", chk::lineCount(o) == 4);
		CHECK("ScavTrap: own ctor message differs from ClapTrap's",
			chk::linesWith(o, "ScavTrap", "constructor", "destructor") == 1 && chk::linesWith(o, "ClapTrap", "constructor", "destructor") == 1);
		CHECK("ScavTrap: own dtor message present", chk::linesWith(o, "ScavTrap", "destructor") == 1);
		CHECK("ScavTrap: ctor/dtor lines end with newline", !o.empty() && o[o.size() - 1] == '\n');
	}
	{
		chk::Capture c;
		{ ScavTrap s; }
		std::string o = CLEAN(c);
		CHECK("ScavTrap: default ctor chain Clap -> Scav / Scav -> Clap", seq(o) == "CSSC");
	}
	{
		ScavTrap s("Scav");
		Stats st = stats(s);
		CHECK("ScavTrap: hit points 100", st.hp == 100);
		CHECK("ScavTrap: energy points 50", st.ep == 50);
		CHECK("ScavTrap: attack damage 20", st.ad == 20);
		ScavTrap d;
		Stats t = stats(d);
		CHECK("ScavTrap: default ctor also 100/50/20", t.hp == 100 && t.ep == 50 && t.ad == 20);
	}
	{
		ScavTrap s("Scav");
		chk::Capture c; s.attack("Target"); std::string o = CLEAN(c);
		CHECK("ScavTrap::attack prints its own message (mentions ScavTrap)", chk::has(o, "ScavTrap Scav attacks Target, causing 20 points of damage!"));
		CHECK("ScavTrap::attack costs 1 energy", stats(s).ep == 49);
		int n = 1;
		for (int i = 0; i < 60; i++) { chk::Capture c2; s.attack("T"); std::string o2 = CLEAN(c2); if (chk::has(o2, "attacks T")) n++; }
		CHECK("ScavTrap: exactly 50 attacks possible", n == 50);
		CHECK("ScavTrap: energy stops at 0", stats(s).ep == 0);
	}
	{
		ScavTrap s("Scav");
		chk::Capture c; s.guardGate(); std::string o = CLEAN(c);
		CHECK("guardGate: one line mentioning the gate", chk::lineCount(o) == 1 && chk::has(chk::lower(o), "gate"));
		CHECK("guardGate: mentions the robot", chk::has(o, "Scav"));
		CHECK("guardGate: free (no energy)", stats(s).ep == 50);
	}
	{
		ScavTrap s("Scav");
		{ chk::Capture c; s.takeDamage(30); c.stop(); }
		CHECK("inherited takeDamage: 100 -> 70", stats(s).hp == 70);
		{ chk::Capture c; s.beRepaired(10); c.stop(); }
		CHECK("inherited beRepaired: 70 -> 80, ep 49", stats(s).hp == 80 && stats(s).ep == 49);
		{ chk::Capture c; s.takeDamage(4294967295u); c.stop(); }
		CHECK("ScavTrap takeDamage(UINT_MAX): hp 0", stats(s).hp == 0);
		chk::Capture c; s.attack("x"); std::string o = CLEAN(c);
		CHECK("dead ScavTrap cannot attack", !chk::has(o, "attacks x"));
		chk::Capture c2; s.guardGate(); std::string o2 = CLEAN(c2);
		CHECK("dead ScavTrap: guardGate still prints (no crash)", chk::lineCount(o2) >= 1);
	}
	{
		ScavTrap s("Scav");
		{ chk::Capture c; s.attack("x"); s.takeDamage(10); c.stop(); }
		chk::Capture c;
		{ ScavTrap k(s); }
		std::string o = CLEAN(c);
		CHECK("ScavTrap copy ctor: Clap copy -> Scav copy, then Scav dtor -> Clap dtor", seq(o) == "CSSC");
		CHECK("ScavTrap copy ctor mentions copy", chk::has(chk::lower(o), "copy"));
		ScavTrap k2(s);
		Stats st = stats(k2);
		CHECK("ScavTrap copy ctor keeps hp/ep/ad (90/49/20)", st.hp == 90 && st.ep == 49 && st.ad == 20);
		{ chk::Capture c2; k2.attack("x"); c2.stop(); }
		CHECK("ScavTrap copy is independent", stats(s).ep == 49 && stats(k2).ep == 48);
		ScavTrap z("Z");
		{ chk::Capture c2; z = s; std::string o2 = CLEAN(c2); CHECK("ScavTrap assignment prints a message", chk::has(chk::lower(o2), "assign")); }
		CHECK("ScavTrap assignment keeps hp/ep/ad", stats(z).hp == 90 && stats(z).ep == 49 && stats(z).ad == 20);
		ScavTrap &self = s;
		{ chk::Capture c2; s = self; c2.stop(); }
		CHECK("ScavTrap self-assignment", stats(s).hp == 90);
		{
			chk::Capture c2; z.attack("x"); std::string o2 = CLEAN(c2);
			CHECK("assigned ScavTrap keeps its name in messages", chk::has(o2, "Scav"));
		}
	}
	{
		ScavTrap s("Scav");
		ClapTrap &r = s;
		chk::Capture c; r.takeDamage(30); c.stop();
		CHECK("ClapTrap& to a ScavTrap acts on the same object", stats(s).hp == 70);
		ClapTrap sliced(s);
		CHECK("slicing copy into ClapTrap keeps hp/ep/ad", stats(sliced).hp == 70 && stats(sliced).ad == 20);
	}
	{
		// 2 ScavTraps must not share state
		ScavTrap a("A"), b("B");
		{ chk::Capture c; a.attack("x"); a.takeDamage(50); c.stop(); }
		CHECK("two ScavTraps have independent state", stats(b).hp == 100 && stats(b).ep == 50 && stats(a).hp == 50);
	}
}

#endif
