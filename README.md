# cisco_style_CLI
cisco style command line interface

- init & test c - enum / initialize map vector class
- add various example of map with user-defined class /struct as a key
- make cisco input method with the same of Argument element
    - test/c.cpp : basic format  map <string , map < string , vector < string , string , type>>>
    - test/d.cpp : advanced format map < argument , map < argument , vector < argument>>>    , argument is <string ,string , type>
    - cli.cpp : make cisco input method with the same of Argument element

- find common string
    - cli.cpp : find common string
    - add example for single command ex) list , help , quit , history
    - automatic completion of module and api name
    - give the hint (recommend) for each argments
    - <CR> means return key.
    - restore the starting status of terminal

- delete function
    - cli.cpp : delete function
    - delete characters through multiple tokens. it can delete old tokens.
    - show 2 lines when we input arguments.
        - one is helping line with arguement name and type
        - the other is just your input.

