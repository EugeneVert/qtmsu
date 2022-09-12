# qtmsu
[TMSU](https://github.com/oniony/TMSU) tag management GUI in QT5

https://user-images.githubusercontent.com/69643766/189655236-f6c70c1f-c825-439f-8c9b-c35e8eb0c24e.mp4

## Usage
Note: `qtmsu` is a wrapper around the TMSU cli.

Inside directory with [TMSU](https://github.com/oniony/TMSU) database:
`qtmsu %file(s)%`

## Compiling from source

### Dependencies
`cmake`>= 3.5, `qt`>=5.12, `kf5-kitemviews`

### Build
```bash
cmake -B build
cmake --build build
```
Builded executable will be located at `./build/qtmsu`

