<h1 align="center">
  <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/Banner.svg" alt="COVET" width="100%">
</h1>

<div align="center">
  
![status](https://img.shields.io/badge/status-pre--alpha-blue)
![license](https://img.shields.io/badge/license-apache_2.0-yellow)
![windows](https://github.com/WindOfXaos/COVET/actions/workflows/windows.yml/badge.svg)
![linux](https://github.com/WindOfXaos/COVET/actions/workflows/linux.yml/badge.svg)
![testing](https://github.com/WindOfXaos/COVET/actions/workflows/testing.yml/badge.svg)

</div>

> Whoso unfetters the fiend reaps the benefit.

## Screenshots
<h3 align="center">
<img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20084741.png" alt="screenshot1"> <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20084841.png" alt="screenshot2"> <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20085024.png" alt="screenshot3"> <img src="https://github.com/WindOfXaos/COVET/blob/main/doc/screenshots/Screenshot%202024-04-11%20085725.png" alt="screenshot4">
</h3>

## Download
[Github Releases](https://github.com/WindOfXaos/COVET/releases)
![version](https://img.shields.io/github/v/release/WindOfXaos/COVET?logo=github
)

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
$ git clone --recursive https://github.com/WindOfXaos/COVET
$ cd COVET
```
### Makefile
Build GLFW
```console
$ make GLFW
```
Build source code
```console
$ make
```
Run project
```console
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
