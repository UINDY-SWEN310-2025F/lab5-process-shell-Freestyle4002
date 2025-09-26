if [ -z "$1" ]; then
	echo "Usage: $0 <PID>"
	exit 1
fi

PID=$1

OUTPUT=$(ps -o f,s,uid,pid,ppid,c,pri,ni,addr,sz,wchan,tty,time,cmd -p "$PID" --no-headers)

if [ -z "$OUTPUT" ]; then
	echo "no process found for $PID"
else
	echo "F S UID PID PPID C PRI NI ADDR SZ WCHAN TTY TIME CMD"
	echo "$OUTPUT"
fi
