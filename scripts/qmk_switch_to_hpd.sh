#!/usr/bin/env sh

rm -rf .idea
qmk generate-compilation-database -kb ergohaven/hpd -km s2ler
qmk compile -kb ergohaven/hpd -km s2ler -j 0
