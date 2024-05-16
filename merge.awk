/^[^\t }#\/]/ && (\
	/\);$/ || (\
		/[^;{]$/ && !/^static/ && FILENAME != "main.c"\
	)\
) {
	print "static " $0
	next
}

/^#include "/ || /^struct node;/ {
	next
}

ok[FILENAME] == 0 {
	if (FILENAME == "out.c") {
		print "#undef n"
		print "#define n xn"
	}
	else if (FILENAME == "stack.c") {
		print "#undef n"
		print "#define a ya"
		print "#define n yn"
	}

	ok[FILENAME] = 1
}

{
	print
}
