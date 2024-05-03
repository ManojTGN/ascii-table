# ASCII TABLE
![asciitable](https://github.com/ManojTGN/ascii-table/assets/42494649/ab86ba7e-6085-464c-9ff2-c76e6aa661e6)

## Overview
AsciiTable shows octal, hexadecimal, and decimal representations of ascii characters. It supports all 8-bit ASCII characters. But 7-bit ASCII characters are prefered to be processed.
![asciitable](https://github.com/ManojTGN/ascii-table/assets/42494649/c140c32a-6315-424a-a4cd-62924970acac)

## Features
- Converts ASCII characters to octal, hexadecimal, and decimal values.
- Simple and lightweight command-line interface.
- Supports the full range of 256 ASCII characters.

## Installation
### Release
Visit [Releases](https://github.com/ManojTGN/ascii-table/releases) And Download The latest `ascii` Binary from it. then add it to the environment variable.

### Build
```bash
git clone https://github.com/ManojTGN/ascii-table.git
cd ascii-table
make
```

## Usage
```bash

ascii [characters...] [..options]

```

#### Available Options:
    `--all`     shows all available ascii codes
    `--digits`  shows all digits ascii codes
    `--alphas`  shows all alphabets ascii codes
    `--specials`shows all special char ascii codes
    `--controls`shows all control ascii codes (non printables)
    
    `--octa`    shows only octa in output table
    `--dec`     shows only dec in output table
    `--hex`     shows only hex in output table
    `--bin`     shows binary in output table
    
    `--asc`     shows output table in ascending order
    `--desc`    shows output table in desending order
    
    `--vt100`   register ansi vt100 escape sequence color to the terminal & terminate

#### Input Types:
    `0000b`  represents 0 in binary  (add b  at last)
    `0d`     represents 0 in decimal (add d  at last)
    `0o`     represents 0 in octal   (add o  at last)
    `0x00`   represents 0 in hexa    (add 0x at first)

#### Examples
```bash
ascii abcd
ascii "manojtgn"
ascii "helloworld"

ascii "make it ascending"  --asc
ascii "make it descending" --desc

ascii 0x78
ascii 0x78 69d
ascii 0x78 15c 69d 01001001b

ascii --alphas
ascii --digits --specials
ascii --digits --alphas --specials --controls
ascii --all

ascii "show octal & decimal" --octa --dec
ascii "show only hex" --hex
ascii "add binary representation" --bin
ascii "show only octa & also bin" --octa --bin

ascii --vt100

ascii
```
