case `$1 -dumpmachine` in
x86_64*-linux* )
	echo x86_64-linux ;;
x86_64*-freebsd* )
	echo x86_64-freebsd ;;
x86_64*-netbsd* )
	echo x86_64-netbsd ;;
amd64*-openbsd* )
	echo x86_64-openbsd ;;
x86_64*-solaris* )
	echo x86_64-solaris ;;
aarch64*-linux* )
	echo aarch64-linux ;;
aarch64*-freebsd* )
	echo aarch64-freebsd ;;
powerpc64*-linux* )
	echo powerpc64-linux ;;
i[3456]86*-linux* )
	echo i386-linux ;;
i386*-solaris* )
	echo i386-solaris ;;
* )
	echo unsupported
esac
