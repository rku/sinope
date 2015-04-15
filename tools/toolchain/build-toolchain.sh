#!/bin/bash
#
# Simple convenience utility for building a binutils/gcc cross compiler
# toolchain for the given target.
#
# Copyright (c) René Küttner <rene@spaceshore.net>
#
# This script is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This script is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

### BEGIN of configuration
PREFIX="$HOME/cross"
TARGET=i686-elf
PATH="$PREFIX/bin:$PATH"
MAKE_ARGS=-j5
BINUTILS_VERSION="2.25"
BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/"
GCC_VERSION="4.9.2"
GCC_URL="ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/"
### END of configuration

# stop on first error
set -e

# change to build dir
mkdir -p build-${TARGET}
cd build-${TARGET}

# extract binutils
if [ ! -d binutils-${BINUTILS_VERSION} ]; then

    # download binutils if necessary
    if [ ! -f "binutils-${BINUTILS_VERSION}.tar.bz2" ]; then
        wget "${BINUTILS_URL}/binutils-${BINUTILS_VERSION}.tar.bz2"
    fi

    tar xvjf binutils-${BINUTILS_VERSION}.tar.bz2
fi

# extract gcc
if [ ! -d gcc-${GCC_VERSION} ]; then

    # download gcc if necessary
    if [ ! -f "gcc-${GCC_VERSION}.tar.bz2" ]; then
        wget "${GCC_URL}/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.bz2"
    fi

    tar xvjf gcc-${GCC_VERSION}.tar.bz2
fi

# build and install binutils
#mkdir build-binutils-${BINUTILS_VERSION}
#cd build-binutils-${BINUTILS_VERSION}
#../binutils-${BINUTILS_VERSION}/configure \
#    --target=$TARGET \
#    --prefix="$PREFIX" \
#    --with-sysroot \
#    --disable-nls \
#    --disable-werror
#make ${MAKE_ARGS}
#make install
#cd ..

# build and install gcc
mkdir build-gcc-${GCC_VERSION}
cd build-gcc-${GCC_VERSION}
../gcc-${GCC_VERSION}/configure \
    --target=$TARGET \
    --prefix="$PREFIX" \
    --disable-nls \
    --enable-languages=c \
    --without-headers
make all-gcc ${MAKE_ARGS}
make all-target-libgcc ${MAKE_ARGS}
make install-gcc
make install-target-libgcc
cd ..

# step out of build dir
cd ..
