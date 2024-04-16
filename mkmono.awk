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

ok == 0 && FILENAME == "stack.c" {
	print "#define a sa"
	print "#define n sn"
	ok = 1
}

{
	print
}
