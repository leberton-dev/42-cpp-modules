# CPP06 / ex00 -- TODO

## getType()
- [x] pseudo-litteraux : nan, nanf, +inf, -inf, +inff, -inff -> FLOAT / DOUBLE;
- [x] char : 1 charactere non-chiffre, ou 'x'
- [x] int : \[signe] chiffres (au moin 1)
- [x] float : \[signe] chiffres . chiffres f ( un seul point ,f en dernier )
- [x] double : \[signe] chiffres . chiffres ( un seul point )
- [x] sinon : ERROR ( aussi chaine vide )
- [x] decider : '42.' et '.5' acceptees ou pas ?

## conversion vers le type
- [ ] strtol / strtod -> verifier errno == ERANGE
- [ ] int hors \[INT_MIN, INT_MAX] -> que faire ?

## static_cast vers les 3 autres formes
- [ ] fromChar / fromInt / fromFloat / fromDouble

## affichage (4 fonctions qui prennent un double)
- [ ] printChar : impossible si nan / <0 / >127, Non displayable si !isprint
- [ ] printInt : impossible si nan / hors, bornes (comparer EN DOUBLE avant le cast)
- [ ] printFloat / printDouble : nan, inf, toujours une decimale (0.0f / 0.0)

## Pieges
- numeric_limits<float>::min() = plus petit POSITIF -> utiliser -max()
- nan != nan -> `d != d` detecte nan

## Tests
0 42 -42 a '*' 2147483647 2147483648 -2147483649
0.0 -4.2 42.0f 4.2f 0.0f 127.0 128.0 -1.0
nan nanf +inf -inf +inff -inff
"" . 1.2.3 42f abc 12abc - + ++1 1.f .5
3.4e39 99999999999.0
