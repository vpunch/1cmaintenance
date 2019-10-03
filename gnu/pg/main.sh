#! /bin/bash

. $(dirname $0)/settings.sh
. $(dirname $0)/common.sh
STOR=$STOR/sql

msg "$(basename $0) START"

mkdir -p $STOR

for DB in "${DBS[@]}"; do
	DBLIST+=" $DB"
done

if test -z "$DBLIST"; then
	DBLIST=$(psql -t -A -c "SELECT datname FROM pg_database WHERE datname NOT IN ('template0', 'template1', '$PGUSER');")
fi

for DB in $DBLIST; do
    pg_dump -d $DB | 7z a -p"$PASS" -si "$STOR/$DB $MARK.sql.7z"
    psql -d $DB <<< "VACUUM FULL ANALYZE; REINDEX DATABASE $DB;"
done

find $STOR -type f -name '*.sql.7z' -mtime +90 -delete

msg "$(basename $0) END"
