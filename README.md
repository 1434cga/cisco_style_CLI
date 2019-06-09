# Developers:wq
- travis-CI [![Build Status](https://travis-ci.com/cheoljoo/cisco_style_CLI.svg?branch=master)](https://travis-ci.com/cheoljoo/cisco_style_CLI)
- codedocs [![Documentation](https://codedocs.xyz/cheoljoo/cisco_style_CLI.svg)](https://codedocs.xyz/cheoljoo/cisco_style_CLI/)
- coverity <a href="https://scan.coverity.com/projects/cheoljoo-cisco_style_cli"> <img alt="Coverity Scan Build Status" src="https://scan.coverity.com/projects/18571/badge.svg"/> </a>

## references
- [Deploying an R Markdown Jekyll site to GitHub Pages](https://selbydavid.com/2017/06/16/rmarkdown-jekyll/)
- [Travis Account](https://travis-ci.com)


# cisco_style_CLI (cisco style command line interface)
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
## features
- if you do not know how to use it ,  press space or tab on prompt.
- you do not need the manual if you use it.
- it supports two mode. (Normal / Privileged)
    - Privileged : you can see all APIs.
    - Normal : you can see APIs except privileged API.

