#!/bin/sh

file "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}"|grep 'ar archive random library' >/dev/null 2>&1
if [ $? -ne 0 ]
then
	echo "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}: not a static library"
	exit 1
fi

file "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}"|grep 'universal binary' >/dev/null 2>&1
if [ $? -ne 0 ]
then
    ./mimicSymbol.sh "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}" iReader301.o _SCardTransmit
    ./stripFlatLibrary.sh "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}"
else
    TMP=`mktemp -d /tmp/tmp.XXXXXX`

    for arch in `file "$1"|grep 'architecture '|sed 's/.*(for architecture \(.*\)).*/\1/'`
    do
        lipo "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}" -thin $arch -output $TMP/"${EXECUTABLE_NAME}"-$arch.a

        ./mimicSymbol.sh $TMP/"${EXECUTABLE_NAME}"-$arch.a iReader301.o _SCardTransmit
        ./stripFlatLibrary.sh $TMP/"${EXECUTABLE_NAME}"-$arch.a

    done

    lipo -create -output "${TARGET_BUILD_DIR}/${EXECUTABLE_NAME}" $TMP/*.a

    rm -f -r $TMP/*.a
    rmdir $TMP
fi

