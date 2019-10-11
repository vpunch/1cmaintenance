. $(dirname $0)/settings.sh

# $1 file name
# $2 file path
DEST=$STOR/log/$1.gz
test ! -f $DEST && gzip < $2 > $DEST
