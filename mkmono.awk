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
		print "#define n pn"
	}
	else if (FILENAME == "stack.c") {
		print "#undef n"
		print "#define a sa"
		print "#define n sn"
	}

	ok[FILENAME] = 1
}

{
	print
}
