#!/usr/bin/env sh

qmk generate-compilation-database -kb ergohaven/remnant -km s2ler
qmk compile -kb ergohaven/remnant -km s2ler -j 0
