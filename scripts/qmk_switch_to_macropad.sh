#!/usr/bin/env zsh
rm -rf .idea
qmk generate-compilation-database -kb ergohaven/macropad -km s2ler
qmk compile -kb ergohaven/macropad -km s2ler -j 0