#!/bin/bash

gcc -o example example.c libdatastruct.c -g -Wall -Wextra -pedantic -fsanitize=address -fstack-protector -Werror
