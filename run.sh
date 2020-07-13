rm ./packageInfo
echo "Deleted Binary"

g++ ./src/main.cpp \
    -I /usr/local/include/ \
    -L /usr/local/lib/ \
    -o ./packageInfo -ljson-c
./packageInfo 