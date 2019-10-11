#! /bin/bash

. $(dirname $0)/settings.sh
. $(dirname $0)/common.sh

msg "$(basename $0) START"

pg_basebackup -w -F tar -z -D "$STOR/bin/$MARK"

LAST=$(find "$STOR/log/" -type f -name '*.backup' -mtime +30 -print | tail -n 1)
if [[ -n $LAST ]]; then
    find "$STOR/log/" -type f ! -newer $LAST -delete
    find "$STOR/bin/" -mindepth 1 -type d ! -newer $LAST -delete
fi

msg "$(basename $0) END"
