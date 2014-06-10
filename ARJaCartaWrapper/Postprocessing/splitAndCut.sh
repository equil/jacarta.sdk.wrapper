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

for arch in `file "$1"|grep 'architecture '|sed 's/.*(for architecture \(.*\)).*/\1/'`
do
	lipo "$1" -thin $arch -output $TMP/libfoo-$arch-unstripped.a
    strip -s saveSymbols.conf -i -o $TMP/libfoo-$arch.a $TMP/libfoo-$arch-unstripped.a
done

rm -f $TMP/*-unstripped.a

echo "Creating lib $1"

lipo -create -output "$1" $TMP/*.a

rm -f $TMP/*.a
rmdir $TMP