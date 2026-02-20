#!/bin/bash

gcc -o example example.c libdatastruct.c -g -Wall -Wextra -pedantic -Werror # -fsanitize=address -fstack-protector
