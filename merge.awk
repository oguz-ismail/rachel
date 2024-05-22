/^[^\t }#\/]/ && (\
	/\);$/ || (\
		/[^;{]$/ && !/^static/ && FILENAME != "main.c"\
	)\
) {
	print "static " $0
	next
}

/^#include "/ || (\
	seen["node.h"] == 1 && /^struct node;/\
) {
	next
}

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

{
	print
}
