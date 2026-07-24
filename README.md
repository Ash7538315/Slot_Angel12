# slot
## Features
- None

## Requirements
- g++ 20 or higher 
- ninja
- cmake

## Build
```
mkdir build
cmake -G "Ninja" -D CMAKE_CXX_COMPILER=g++ -B build
cmake --build build
```

## Memo
git clone --recurse-submodules
cmake .. -DSDL_X11_XSCRNSAVER=OFF

wslgのPulseAudio用API
```
sudo apt install libpulse-dev
sudo apt install libpipewire-0.3-dev
sudo apt install libasound2-dev
```
