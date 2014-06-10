#!/bin/sh

if [ -z "$1" ]
then
	echo "$0: Please, specify a library in first argument."
	exit 1
fi

file "$1"|grep 'ar archive random library' >/dev/null 2>&1
if [ $? -ne 0 ]
then
	echo "$1: not a static library"
	exit 1
fi

TMP=`mktemp -d /tmp/tmp.XXXXXX`

echo "Creating temp directory $TMP"

file "$1"|grep 'universal binary' >/dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "Process thin library"
    cp $1 $TMP/libfoo-unstripped.a

    ar x $TMP/libfoo-unstripped.a $TMP/iReader301.o
    ./objconv -v0 -nr:_SCardTransmit:___SCardTransmit $TMP/iReader301.o $TMP/iReader301-.o
    rm $TMP/iReader301.o
    mv $TMP/iReader301-.o $TMP/iReader301.o
    ar r $TMP/libfoo-unstripped.a $TMP/iReader301.o
    rm $TMP/iReader301.o

    strip -s saveSymbols.conf -i -o $1 $TMP/libfoo-unstripped.a
    rm $TMP/libfoo-unstripped.a
else
    for arch in `file "$1"|grep 'architecture '|sed 's/.*(for architecture \(.*\)).*/\1/'`
    do
        echo "Process library $1 for architecture $arch"

        lipo "$1" -thin $arch -output $TMP/libfoo-$arch-unstripped.a

        ar x $TMP/libfoo-$arch-unstripped.a $TMP/iReader301.o
        ./objconv -v0 -nr:_SCardTransmit:___SCardTransmit $TMP/iReader301.o $TMP/iReader301-.o
        rm $TMP/iReader301.o
        mv $TMP/iReader301-.o $TMP/iReader301.o
        ar r $TMP/libfoo-$arch-unstripped.a $TMP/iReader301.o
        rm $TMP/iReader301.o

        strip -s saveSymbols.conf -i -o $TMP/libfoo-$arch.a $TMP/libfoo-$arch-unstripped.a
    done

    rm -f $TMP/*-unstripped.a

    echo "Creating lib $1"

    lipo -create -output "$1" $TMP/*.a
fi

rm -f -r $TMP/*.a
rmdir $TMP