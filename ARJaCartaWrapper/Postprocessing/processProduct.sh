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

file "$1"|grep 'universal binary' >/dev/null 2>&1
if [ $? -ne 0 ]
then
    ./mimicSymbol.sh "$1" iReader301.o _SCardTransmit
    ./stripFlatLibrary "$1"
else
    TMP=`mktemp -d /tmp/tmp.XXXXXX`

    for arch in `file "$1"|grep 'architecture '|sed 's/.*(for architecture \(.*\)).*/\1/'`
    do
        lipo "$1" -thin $arch -output $TMP/"$1"-$arch.a

        ./mimicSymbol.sh $TMP/"$1"-$arch.a iReader301.o _SCardTransmit
        ./mimicSymbol.sh $TMP/"$1"-$arch.a eTokenGOST.o _lmFunctionsLoader _eTokenGOST
        ./mimicSymbol.sh $TMP/"$1"-$arch.a LoadableModule.o _lmFunctionsLoader _LoadableModule
        ./mimicSymbol.sh $TMP/"$1"-$arch.a PKCS11.o _lmFunctionsLoader _PKCS11
        ./mimicSymbol.sh $TMP/"$1"-$arch.a API.o _lmFunctionsLoader _API
        ./stripFlatLibrary.sh $TMP/"$1"-$arch.a

    done

    lipo -create -output "$1" $TMP/*.a

    rm -f -r $TMP/*.a
    rmdir $TMP
fi

