#! /bin/bash

pg_basebackup -p 5432 -F tar -z -D /mnt/1cbak/base/$(date +\%Y-\%m-\%d)
/root/rm1cbak.sh

cd /mnt/1cbak

LAST=$(find wal/ -type f -name '*.backup' -mtime +30 -print | tail -n 1)
if [[ -n $LAST ]]; then
    find wal/ -type f ! -newer $LAST -delete
    find base/ -mindepth 1 -type d ! -newer $LAST -delete
fi
