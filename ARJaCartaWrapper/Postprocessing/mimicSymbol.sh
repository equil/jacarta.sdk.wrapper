#!/bin/sh

SUFFIX=$4
if [ "${SUFFIX}" = "" ]
then
    SUFFIX="__"
fi

echo "Mimic symbol $3 ---> $3${SUFFIX} for object file $2 in library $1"

TMP=`mktemp -d /tmp/tmp.XXXXXX`

cp $1 $TMP/libfoo-mimic.a

ar x $TMP/libfoo-mimic.a $TMP/$2
./objconv -v0 -nr:$3:${SUFFIX}$3 $TMP/$2 $TMP/$2-temp > /dev/null
rm $TMP/$2
mv $TMP/$2-temp $TMP/$2
ar r $TMP/libfoo-mimic.a $TMP/$2

rm $TMP/$2

rm $1
cp $TMP/libfoo-mimic.a $1
rm $TMP/libfoo-mimic.a

rmdir $TMP