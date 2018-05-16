cc=gcc
objects=obj/sys.o obj/cfgsys.o obj/mmlcmd.o obj/libstdio.o obj/error.o

bin/sys:$(objects)
	$(cc) -o bin/sys $(objects)

obj/sys.o:sys/sys.c sys/sysdata.h
	$(cc) -o obj/sys.o -c sys/sys.c -Isys

obj/cfgsys.o:cfg/cfgsys.c cfg/cfgsys.h 
	$(cc) -o obj/cfgsys.o -c cfg/cfgsys.c -Icfg -Ilib
obj/mmlcmd.o:mml/mmlcmd.c mml/mmlcmd.h
	$(cc) -o obj/mmlcmd.o -c mml/mmlcmd.c -Imml
obj/libstdio.o:lib/libstdio.c lib/syslib.h
	$(cc) -o obj/libstdio.o -c lib/libstdio.c -Ilib
obj/error.o:lib/error.c lib/syslib.h
	$(cc) -o obj/error.o -c lib/error.c -Ilib
clean:
	rm -rf $(objects) bin/sys
