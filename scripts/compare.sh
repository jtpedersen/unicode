#!/bin/bash
set -x

DECODER=$1
ENCODER=$2
TESTDATA=$3
TMP=encoded.dat
ROUNDTRIP=roundtrip.dat
${DECODER} < ${TESTDATA} > ${TMP}
${ENCODER} < ${TMP} > ${ROUNDTRIP}

DIFF=$(diff $TESTDATA $ROUNDTRIP)

if [ "$DIFF" != "" ] 
then
    echo $DIFF
    exit -1
fi

