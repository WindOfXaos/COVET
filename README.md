<h1 align="center">
  <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/Banner.svg" alt="COVET" width="100%">
</h1>

<div align="center">
  
![status](https://img.shields.io/badge/status-pre--alpha-blue)
![license](https://img.shields.io/badge/license-apache_2.0-yellow)

</div>

> Whoso unfetters the fiend reaps the benefit.

## Screenshots
<h3 align="center">
<img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20084741.png" alt="screenshot1"> <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20084841.png" alt="screenshot2"> <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20085024.png" alt="screenshot3"> <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20085725.png" alt="screenshot4">
</h3>

## Project Structure
```
root
├──bin        // build output and assets
├──build      // intermediate files
├──doc        // documentation
├──include    // public headers
├──lib        // libraries
├──src        // project source code
├──test       // unit tests
└──vendor     // third-party
```

## Building
Clone the repository
```console
$ git clone https://github.com/WindOfXaos/COVET
$ cd COVET
```
### Makefile
Build and run
```console
$ make
$ cd bin
$ ./COVET
```
Unit tests
```console
$ make test
```
Clean
```console
$ make clean
```
