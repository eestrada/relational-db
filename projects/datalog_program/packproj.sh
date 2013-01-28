#!/bin/sh
PN=lab1

FNAME=${TEMP}/cs236_${PN}

mkdir -p ${FNAME}

cp inc/* src/* ${FNAME}

cd ${FNAME}

zip ${PN}.zip * > /dev/null

cp ${PN}.zip ${OLDPWD}

cd ${OLDPWD}
