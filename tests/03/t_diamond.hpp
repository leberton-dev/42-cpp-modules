#ifndef T_DIAMOND_HPP
#define T_DIAMOND_HPP

#include "DiamondTrap.hpp"
#include "t_common.hpp"

inline void test_diamond() {
	// ---- chaining: ClapTrap built ONCE, then Scav, Frag, Diamond; destroyed in reverse ----
	{
		chk::Capture c;
		{ DiamondTrap d("Bob"); }
		std::string o = CLEAN(c);
		CHECK("DiamondTrap: ctor order Clap, Scav, Frag, Diamond then dtor Diamond, Frag, Scav, Clap", seq(o) == "CSFDDFSC");
		CHECK("DiamondTrap: ClapTrap constructed exactly once", chk::linesWith(o, "ClapTrap", "constructor", "destructor") == 1);
		CHECK("DiamondTrap: ClapTrap destroyed exactly once", chk::linesWith(o, "ClapTrap", "destructor") == 1);
		CHECK("DiamondTrap: 8 lines total (4 ctor + 4 dtor)", chk::lineCount(o) == 8);
		CHECK("DiamondTrap: messages end with newline", !o.empty() && o[o.size() - 1] == '\n');
	}
	{
		chk::Capture c;
		{ DiamondTrap d; }
		std::string o = CLEAN(c);
		CHECK("DiamondTrap: default ctor chain, ClapTrap once", seq(o) == "CSFDDFSC");
	}
	// ---- names ----
	{
		DiamondTrap d("Bob");
		chk::Capture c; d.whoAmI(); std::string o = CLEAN(c);
		CHECK("whoAmI prints the DiamondTrap name", chk::has(o, "Bob"));
		CHECK("whoAmI prints the ClapTrap name Bob_clap_name", chk::has(o, "Bob_clap_name"));
		CHECK("whoAmI: 2 lines (both names)", chk::lineCount(o) == 2);
		chk::Capture c2; d.log(); std::string o2 = CLEAN(c2);
		CHECK("ClapTrap::name is 'Bob_clap_name' (seen through log())", chk::has(o2, "Bob_clap_name"));
	}
	{
		DiamondTrap d;
		chk::Capture c; d.whoAmI(); std::string o = CLEAN(c);
		CHECK("default DiamondTrap has a name and a *_clap_name", chk::has(o, "_clap_name") && o.size() > 12);
	}
	// ---- attributes: HP from Frag, EP from Scav, AD from Frag ----
	{
		DiamondTrap d("Bob");
		Stats s = stats(d);
		CHECK("DiamondTrap: hit points 100 (FragTrap)", s.hp == 100);
		CHECK("DiamondTrap: energy points 50 (ScavTrap)", s.ep == 50);
		CHECK("DiamondTrap: attack damage 30 (FragTrap)", s.ad == 30);
		DiamondTrap e;
		Stats t = stats(e);
		CHECK("DiamondTrap default: 100/50/30", t.hp == 100 && t.ep == 50 && t.ad == 30);
	}
	// ---- attack() comes from ScavTrap ----
	{
		DiamondTrap d("Bob");
		chk::Capture c; d.attack("T"); std::string o = CLEAN(c);
		CHECK("attack() is ScavTrap's (message mentions ScavTrap)", chk::has(o, "ScavTrap"));
		CHECK("attack() uses DiamondTrap damage 30", chk::has(o, "attacks T, causing 30 points of damage!"));
		CHECK("attack() costs 1 energy (50 -> 49)", stats(d).ep == 49);
		int n = 1;
		for (int i = 0; i < 60; i++) { chk::Capture c2; d.attack("T"); std::string o2 = CLEAN(c2); if (chk::has(o2, "attacks T")) n++; }
		CHECK("DiamondTrap: exactly 50 attacks possible (ScavTrap energy)", n == 50);
	}
	// ---- special abilities of both parents + own ----
	{
		DiamondTrap d("Bob");
		chk::Capture c; d.guardGate(); std::string o = CLEAN(c);
		CHECK("guardGate inherited from ScavTrap", chk::has(chk::lower(o), "gate"));
		chk::Capture c2; d.highFivesGuys(); std::string o2 = CLEAN(c2);
		CHECK("highFivesGuys inherited from FragTrap", chk::has(chk::lower(o2), "high") && chk::has(chk::lower(o2), "five"));
	}
	{
		DiamondTrap d("Bob");
		{ chk::Capture c; d.takeDamage(30); c.stop(); }
		CHECK("takeDamage (unambiguous ClapTrap): 100 -> 70", stats(d).hp == 70);
		{ chk::Capture c; d.beRepaired(20); c.stop(); }
		CHECK("beRepaired: 70 -> 90, energy 49", stats(d).hp == 90 && stats(d).ep == 49);
		{ chk::Capture c; d.takeDamage(4294967295u); c.stop(); }
		CHECK("takeDamage(UINT_MAX) -> 0", stats(d).hp == 0);
		chk::Capture c; d.attack("x"); std::string o = CLEAN(c);
		CHECK("dead DiamondTrap cannot attack", !chk::has(o, "attacks x"));
	}
	// ---- exactly one ClapTrap sub-object (virtual inheritance) ----
	{
		DiamondTrap d("Bob");
		ScavTrap *s = &d;
		FragTrap *f = &d;
		ClapTrap *cs = s;
		ClapTrap *cf = f;
		CHECK("ScavTrap and FragTrap share the SAME ClapTrap sub-object", cs == cf);
		chk::Capture c; s->takeDamage(10); c.stop();
		CHECK("damage through the ScavTrap view is visible through the FragTrap view", stats(*f).hp == 90);
	}
	// ---- copy ----
	{
		DiamondTrap a("A");
		{ chk::Capture c; a.attack("x"); a.takeDamage(10); c.stop(); }
		chk::Capture c;
		{ DiamondTrap b(a); }
		std::string o = CLEAN(c);
		CHECK("copy ctor: ClapTrap copied once (chain C,S,F,D then D,F,S,C)", seq(o) == "CSFDDFSC");
		CHECK("copy ctor: exactly one ClapTrap copy/ctor line", chk::linesWith(o, "ClapTrap", "constructor", "destructor") == 1);
		DiamondTrap b(a);
		Stats s = stats(b);
		CHECK("copy ctor keeps hp/ep/ad (90/49/30)", s.hp == 90 && s.ep == 49 && s.ad == 30);
		chk::Capture c2; b.whoAmI(); std::string o2 = CLEAN(c2);
		CHECK("copy ctor keeps both names", chk::has(o2, "A_clap_name") && chk::has(o2, "A"));
		{ chk::Capture c3; b.takeDamage(20); c3.stop(); }
		CHECK("copy is independent", stats(a).hp == 90 && stats(b).hp == 70);
	}
	{
		DiamondTrap a("Alpha"), b("Zed");
		{ chk::Capture c; a.attack("x"); a.takeDamage(10); c.stop(); }
		{ chk::Capture c; b = a; std::string o = CLEAN(c); CHECK("assignment prints a message", chk::has(chk::lower(o), "assign")); }
		Stats s = stats(b);
		CHECK("assignment copies hp/ep/ad", s.hp == 90 && s.ep == 49 && s.ad == 30);
		chk::Capture c2; b.whoAmI(); std::string o2 = CLEAN(c2);
		CHECK("assignment copies DiamondTrap::name AND ClapTrap::name", chk::has(o2, "Alpha_clap_name") && !chk::has(o2, "Zed"));
		DiamondTrap &self = a;
		{ chk::Capture c; a = self; c.stop(); }
		CHECK("self assignment keeps values", stats(a).hp == 90);
		DiamondTrap e("E"), f("F");
		{ chk::Capture c; e = f = a; c.stop(); }
		CHECK("chained assignment", stats(e).hp == 90 && stats(f).hp == 90);
	}
	{
		DiamondTrap a("A"), b("B");
		{ chk::Capture c; a.takeDamage(40); c.stop(); }
		CHECK("two DiamondTraps have independent state", stats(b).hp == 100 && stats(a).hp == 60);
	}
	// ---- temporaries / by-value return (rule of three sanity, checked by ASan) ----
	{
		chk::Capture c;
		DiamondTrap d = DiamondTrap("Tmp");
		DiamondTrap e(d);
		e = d;
		c.stop();
		CHECK("copy-init from temporary works", stats(d).hp == 100);
	}
}

#endif
