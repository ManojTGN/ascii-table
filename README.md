# ASCII TABLE

## Overview
AsciiTable shows octal, hexadecimal, and decimal representations of ascii characters. It supports all 7-bit ASCII characters.
![Capture](https://github.com/ManojTGN/ascii-table/assets/42494649/bb0fc8f0-6163-4cc9-a1b4-4364950295e2)

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
    `--all`     shows all available ascii codes\
    `--digits`  shows all digits ascii codes\
    `--alphas`  shows all alphabets ascii codes
    
    `--octa`    shows only octa in output table\
    `--dec`     shows only dec in output table\
    `--hex`     shows only hex in output table
    
    `--asc`     shows output table in ascending order\
    `--des`     shows output table in desending order
