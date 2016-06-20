#!/bin/bash
#set -x

ENCODER=$1
TESTDATA=$2
REFERENCE=$3
TMP=encoded.dat
${ENCODER} < ${TESTDATA} > ${TMP}

DIFF=$(diff $TMP $REFERENCE)

if [ "$DIFF" != "" ] 
then
    cat $TMP
    cat $REFERENCE
    echo $DIFF
    exit -1
fi

