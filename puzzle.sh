od -A n -t u1 -v </dev/urandom | awk '{
 for (i = 1; i <= NF; i++) {
	if (picked == 0) {
		big = $i%5
		small = 6-big
		picked = 1
	}
	else if (small > 0) {
		x = 1 + $i%10
		if (seen[x]++ < 2) {
			numbers = numbers x " "
			small--
		}
	}
	else if (big == 4) {
		numbers = numbers "25 50 75 100 "
		big = 0
	}
	else if (big > 0) {
		x = (1 + $i%4)*25
		if (seen[x]++ < 1) {
			numbers = numbers x " "
			big--
		}
	}
	else if (n < 2) {
		target = target*256 + $i
		n++
	}
	else {
		target = 101 + target%899
		exit
	}
 }
}
END {
	print numbers target
}'
