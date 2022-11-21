#!/bin/bash
SRC_PATH=src
HEADER_PATH=include

SRC_EXT=cpp
HEADER_EXT=hpp



SOURCES=$(find ${SRC_PATH} -name *.${SRC_EXT} | sort -k 1nr | cut -f2-)
HEADERS=$(find ${HEADER_PATH} -name *.${HEADER_EXT} \
-not -path "include/lib/*" \
| sort -k 1nr | cut -f2-)

clang-format --style='{BasedOnStyle: google, IndentWidth: 2}' -i $SOURCES $HEADERS
