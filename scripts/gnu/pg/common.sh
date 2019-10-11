MARK=$(date +'%F %H.%M.%S')
function msg {
	echo $(date +'%F %H.%M.%S') $1 >> $LOG
}
