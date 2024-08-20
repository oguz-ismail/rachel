FILENAME != f {
	f = FILENAME
	c++
	print "#undef a"
	print "#undef n"
	print "#define a a" c
	print "#define n n" c
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

(/^#include "/ && !/crt\.h/) ||\
(/^[a-z]/ && /[^)];/ && !/^(static|typedef) /) {
	next
}

{
	print
}
