#!/bin/bash

mkdir build && cd build

echo "Looking for Ninja"
if command -v ninja &> /dev/null; then
	echo "Found Ninja, starting initializing..."
	cmake .. -GNinja
	echo "Starting building..."
	ninja
else
	echo "Ninja not found, fallback to Make."
	if command -v make &> /dev/null; then
		echo "If you want to use Ninja (recommended by Whilnew), after this scripts type 'sudo apt install ninja' (for debian-based) or 'sudo pacman -S ninja' (for arch-based) and hit enter. After that, run this scripts again."
		sleep 1
		cmake ..
		echo "Starting building..."
		make -j${nproc}
	else
		echo "Make not found (too). After this script, type 'sudo apt install ninja' (for debian-based) or 'sudo pacman -S ninja' (for arch-based) and hit enter."
		echo "Error code 1 (no supported build-helper found)"
		exit 1
	fi
fi

build/hne
