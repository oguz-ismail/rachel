seen[FILENAME] == 0 {
	if (FILENAME == "out.c") {
		print "#undef n"
		print "#define n xn"
	}
	else if (FILENAME == "stack.c") {
		print "#undef n"
		print "#define a ya"
		print "#define n yn"
	}

	seen[FILENAME] = 1
}

/^extern / {
	print "static" substr($0, 7)
	next
}

/^[a-z]/ && (\
	/\);$/ || (\
		/[^;{]$/ && !/^static / && FILENAME != "main.c"\
	)\
) {
	print "static " $0
	next
}

/^struct node;/ {
	if (seen["node.h"] == 1)
		next
}

/^#include "/ || (\
	/^[a-z]/ && /[^)];/ && !/^static /\
) {
	next
}

{
	print
}
