## General rules
### Compiling
- Code compiles with **c++** and the flags **-Wall -Wextra -Werror -std=c++98**

### 0
- no `*printf()`, `*alloc()`, `free()`
- no implementation of a function in a header ( except templates )
- include guards obligatory ( no double inclusion )
- headers can be used independently

### -42
- not using `using namespace`, no `friend` keyword
- not **STL** ( Containers / Algorithms ) - only allowed in modules 08 and 09

### Conventions
- classes in `UpperCamelCase`, files named after the class
- each output on `stdout` must end by a `\n`
- no memory leaks ( `new` -> `delete` )
- Orthodox Canonical Form à partir du module 02
- Makefile: `all clean fclean re`, no relinking 
