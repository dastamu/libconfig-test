# libconfig-test
> Simple example using 'libconfig' with C++

## Deps
```sh
#git submodule add git@github.com:hyperrealm/libconfig.git

git clone --recursive git@github.com:dastamu/libconfig-test.git

#or
git clone git@github.com:dastamu/libconfig-test.git
cd libconfig-test
git submodule update --init --recursive

#update submodule
git submodule update --remote libconfig
```

## Build
```sh
mkdir build && cd build
cmake ..
cmake --build .
```

## Run
```sh
./main
```