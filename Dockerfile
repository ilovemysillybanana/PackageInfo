FROM ubuntu

RUN apt-get update -y
RUN apt-get install build-essential \
                    libjson-c-dev \
                    libapt-pkg \
                    libapt-pkg-doc \
                    libdpkg-dev -y

RUN mkdir ./packageInfo
RUN mkdir ./packageInfo/src packageInfo/bin
ADD ./src/* ./packageInfo/src/

WORKDIR /packageInfo
RUN gcc -c -o src/deb.o src/deb.c
RUN g++ -c -o src/main.o src/main.cpp
RUN g++ -o ./bin/packageInfo \
        src/main.o \
        src/deb.o \
        -I /usr/local/include/ \
        -L /usr/local/lib/ \
        -ldpkg \
        -std=c++11
