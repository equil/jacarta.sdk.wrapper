#!/bin/sh

echo "Strip library $1"

TMP=`mktemp -d /tmp/tmp.XXXXXX`

cp $1 $TMP/libfoo.a
cp saveSymbols.conf $TMP/saveSymbols.temp.conf

rm -f tmppipe
mkfifo tmppipe
RELOCATION_ENTRIES=$( strip -s $TMP/saveSymbols.temp.conf -i -o $1 $TMP/libfoo.a 2> tmppipe | grep '^strip: symbols referenced by relocation entries' tmppipe )
rm -f tmppipe

while ( [ "x${RELOCATION_ENTRIES}" != "x" ] ) do

    mkfifo tmppipe
    OUTPUT=$( strip -s $TMP/saveSymbols.temp.conf -i -o $1 $TMP/libfoo.a 2> tmppipe | grep '.*' tmppipe )
    rm -f tmppipe

    RELOCATION_ENTRIES=$( echo "${OUTPUT}" | grep '^strip: symbols referenced by relocation entries' )
    if [ "x${RELOCATION_ENTRIES}" != "x" ]
    then
        echo "Add symbols for error: ${RELOCATION_ENTRIES}"
        echo "#${RELOCATION_ENTRIES}" >> $TMP/saveSymbols.temp.conf
        echo "${OUTPUT}" | grep -v '^strip' >> $TMP/saveSymbols.temp.conf
        echo "${OUTPUT}" | grep -v '^strip'
    fi
done

rm saveSymbols.conf
mv $TMP/saveSymbols.temp.conf saveSymbols.conf


mkfifo tmppipe

nm $1 | grep '_lmFunctionsLoader' 2> tmppipe | grep '.*' tmppipe > $1.beforeRD.txt

cp $1 $TMP/libfoo.a
OUTPUT=$( strip -R removeSymbols.conf -r -u -A -x -i -o $1 $TMP/libfoo.a 2> tmppipe | grep '.*' tmppipe )

nm $1 | grep '_lmFunctionsLoader'

rm -f tmppipe

rm $TMP/libfoo.a

rmdir $TMP

echo "Finish strip of library $1"