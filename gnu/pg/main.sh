STOR=/mnt/1cbak/sql
DBLIST=sc

for D in $DBLIST do
    pg_dump -d $D > "$STOR\$D-$(date -I).sql" | tar
    psql sc <<< 'VACUUM FULL ANALYZE; REINDEX DATABASE $D;'
done
