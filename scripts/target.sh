case `$1 -dumpmachine` in
x86_64*-linux* )
	echo x86_64-linux ;;
x86_64*-freebsd* )
	echo x86_64-freebsd ;;
x86_64*-netbsd* )
	echo x86_64-netbsd ;;
x86_64*-openbsd* | amd64*-openbsd* )
	echo x86_64-openbsd ;;
x86_64*-solaris* )
	echo x86_64-solaris ;;
aarch64*-linux* )
	echo aarch64-linux ;;
aarch64*-freebsd* )
	echo aarch64-freebsd ;;
aarch64*-netbsd* )
	echo aarch64-netbsd ;;
aarch64*-openbsd* )
	echo aarch64-openbsd ;;
arm*-linux* )
	echo arm-linux ;;
arm*-freebsd* )
	echo arm-freebsd ;;
arm*-netbsd* )
	echo arm-netbsd ;;
powerpc64*-linux* )
	echo powerpc64-linux ;;
i[3456]86*-linux* )
	echo i386-linux ;;
i386*-solaris* )
	echo i386-solaris ;;
* )
	echo unsupported
esac
