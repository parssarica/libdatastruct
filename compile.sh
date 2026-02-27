#!/bin/bash

gcc -o example example.c libdatastruct.c -g -Wall -Wextra -pedantic -Werror -Wno-error=unused-variable -fsanitize=address -fstack-protector
#gcc -o example example.c libdatastruct.c -g -Wall -Wextra -pedantic -Werror -Wno-error=unused-variable -fstack-protector
