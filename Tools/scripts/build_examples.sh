#!/bin/bash
# useful script to test the build of all example code
# This helps when doing large merges
# Andrew Tridgell, November 2012

set -e
set -x

export PATH=/usr/lib/ccache:$PATH

TESTS=$(find libraries -name 'Makefile' | xargs -i dirname '{}')

for b in $TESTS; do
    echo "TESTING $b"
    pushd $b
    if [ -r nobuild.txt ]; then
	echo "Skipping build of $b"
    else
	make clean
	make
    fi
    popd
done

echo "All examples built OK"
exit 0
