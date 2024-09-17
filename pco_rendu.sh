#!/bin/bash

PROJECT_DIR=code/counter
ARCHIVE=rendu.tar.gz

if [ ! -d "$PROJECT_DIR" ]
then
    echo "Could not find $PROJECT_DIR directory in $(pwd)" >&2
    exit 1
fi

echo "The following files are archived in $ARCHIVE : "
tar --exclude='rendu.tar.gz' --exclude='*.o' --exclude='*.user' -czvf $ARCHIVE $PROJECT_DIR

