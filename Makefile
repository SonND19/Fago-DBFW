MAINTAINER=stremovsky@gmail.com
CPP=g++
LBITS := $(shell getconf LONG_BIT)

Fago-DBFW: 
	rm -rf Fago-DBFW src/Fago-DBFW
	cd src; make; cp Fago-DBFW ../

clean:
	cd src; make clean; cd mysql; rm -rf *.o;
	rm -rf Fago-DBFW *.o
	rm -rf configure-stamp build-stamp
	rm -rf src/Fago-DBFW
	rm -rf debian/Fago-DBFW
	if test -d "../greensql-console"; then if test -d "greensql-console"; then rm -rf "greensql-console"; fi; fi

install:
	if ! test -d "greensql-console"; then if test -d "../greensql-console"; then cp -R ../greensql-console/ .; fi; fi
	cp Fago-DBFW ${DESTDIR}/usr/sbin/Fago-DBFW

ifeq ($(LBITS),64)
	cp src/lib/libgsql-mysql.so.1 ${DESTDIR}/usr/lib/libgsql-mysql.so.1
	cp src/lib/libgsql-pgsql.so.1 ${DESTDIR}/usr/lib/libgsql-pgsql.so.1
	ln -sf /usr/lib/libgsql-mysql.so.1 ${DESTDIR}/usr/lib/libgsql-mysql.so
	ln -sf /usr/lib/libgsql-pgsql.so.1 ${DESTDIR}/usr/lib/libgsql-pgsql.so
	ln -sf /usr/lib/libgsql-mysql.so.1 ${DESTDIR}/usr/lib/libgsql-mysql.so
	ln -sf /usr/lib/libgsql-pgsql.so.1 ${DESTDIR}/usr/lib/libgsql-pgsql.so
else
	cp src/lib/libgsql-mysql.so.1  ${DESTDIR}/usr/lib/libgsql-mysql.so.1
	cp src/lib/libgsql-pgsql.so.1 ${DESTDIR}/usr/lib/libgsql-pgsql.so.1
	ln -sf /usr/lib/libgsql-mysql.so.1 ${DESTDIR}/usr/lib/libgsql-mysql.so
	ln -sf /usr/lib/libgsql-pgsql.so.1 ${DESTDIR}/usr/lib/libgsql-pgsql.so
endif

	mkdir -p ${DESTDIR}/etc/fagodb/
	cp scripts/fagodb-create-db.sh ${DESTDIR}/usr/sbin/fagodb-create-db
	ln -sf /usr/bin/fagodb-create-db ${DESTDIR}/usr/bin/fagodb-create-db.sh
	cp conf/fagodb.conf ${DESTDIR}/etc/fagodb/fagodb.conf
	cp conf/mysql.conf ${DESTDIR}/etc/fagodb/mysql.conf
	cp conf/pgsql.conf ${DESTDIR}/etc/fagodb/pgsql.conf
	touch ${DESTDIR}/var/log/fagodb.log
	touch ${DESTDIR}/var/log/alert.log
	touch ${DESTDIR}/var/log/event.log

install-web:
	cp conf/greensql-apache.conf ${DESTDIR}/etc/fagodb/
	mkdir -p ${DESTDIR}/usr/share/Fago-DBFW/
	if test -d "../greensql-console"; then cp -R ../greensql-console/* ${DESTDIR}/usr/share/Fago-DBFW/; fi 
	if test -d "greensql-console"; then cp -R greensql-console/* ${DESTDIR}/usr/share/Fago-DBFW/; fi
