#!/bin/sh
PN=cs236

FNAME=${TEMP}/${PN}

mkdir -p ${FNAME}

cp inc/* src/* ${FNAME}

cd ${FNAME}

zip ${PN}.zip * > /dev/null

cp ${PN}.zip ${OLDPWD}

cd ${OLDPWD}

