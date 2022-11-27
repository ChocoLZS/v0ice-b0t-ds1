#!/bin/bash
SRC_PATH="server client test"
HEADER_PATH="server client test"

SRC_EXT=cpp
HEADER_EXT=hpp



SOURCES=$(find ${SRC_PATH} -name *.${SRC_EXT} | sort -k 1nr | cut -f2-)
HEADERS=$(find ${HEADER_PATH} -name *.${HEADER_EXT} \
-not -path "thirdparty/*" \
| sort -k 1nr | cut -f2-)

clang-format --style='{BasedOnStyle: google, IndentWidth: 2}' -i $SOURCES $HEADERS
