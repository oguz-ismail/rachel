while true; do
	puzzle=$(scripts/puzzle.sh)
	echo $puzzle

	ans1=$("$1" $puzzle 2>&1)
	rc1=$?
	ans2=$("$2" $puzzle 2>&1)
	rc2=$?
	if test $rc1 -ne $rc2; then
		echo statuses differ: $rc1 vs $rc2
		exit 1
	fi

	len1=$(echo "$ans1" | wc -l)
	len2=$(echo "$ans2" | wc -l)
	if test $len1 -ne $len2; then
		echo answers differ in length: $len1 vs $len2
		exit 1
	fi

	if test "$ans1" != "$ans2"; then
		echo answers differ
	fi

	n1=0
	while "$1" -s $n1 $puzzle >/dev/null 2>&1; do
		n1=$((n1+1))
	done

	n2=0
	while "$2" -s $n2 $puzzle >/dev/null 2>&1; do
		n2=$((n2+1))
	done

	if test $n1 -ne $n2; then
		echo answer counts differ: $n1 vs $n2
	fi

	echo
done
