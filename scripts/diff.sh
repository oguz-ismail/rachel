while true; do
	args=$(scripts/puzzle.sh)
	echo $args

	out1=$("$1" $args 2>&1)
	ret1=$?
	out2=$("$2" $args 2>&1)
	ret2=$?
	if test $ret1 -ne $ret2; then
		echo statuses differ: $ret1 vs $ret2
		exit 1
	fi

	len1=$(echo "$out1" | wc -l)
	len2=$(echo "$out2" | wc -l)
	if test $len1 -ne $len2; then
		echo answers differ in length: $len1 vs $len2
		exit 1
	fi

	if test "$out1" != "$out2"; then
		echo answers differ
	fi

	c1=0
	while "$1" -s $c1 $args >/dev/null 2>&1; do
		c1=$((c1+1))
	done

	c2=0
	while "$2" -s $c2 $args >/dev/null 2>&1; do
		c2=$((c2+1))
	done

	if test $c1 -ne $c2; then
		echo answer counts differ: $c1 vs $c2
	fi

	echo
done
