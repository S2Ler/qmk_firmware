#!/usr/bin/env sh

rm -rf .idea
qmk generate-compilation-database -kb crkbd -km s2ler
qmk compile -kb crkbd -km s2ler -j 0