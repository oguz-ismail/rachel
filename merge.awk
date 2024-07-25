BEGIN {
	pfx["leaf.c"] = "a"
	pfx["out.c"] = "b"
	pfx["stack.c"] = "c"
}

seen[FILENAME] == 0 {
	if (pfx[FILENAME] != "") {
		print "#undef a"
		print "#undef n"
		print "#define a " pfx[FILENAME] "a"
		print "#define n " pfx[FILENAME] "n"
	}

	seen[FILENAME] = 1
}

/^extern / {
	print "static" substr($0, 7)
	next
}

/^struct node;/ {
	if (seen["node.h"] == 1)
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

(/^#include "/ && !/libc\.h/) ||\
(/^[a-z]/ && /[^)];/ && !/^(static|typedef) /) {
	next
}

{
	print
}
