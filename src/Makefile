OBJS:=main.o buffer.o proxy.o config.o connection.o normalization.o log.o proxymap.o dbmap.o patterns.o misc.o \
		riskengine.o dbpermobj.o alert.o mysql/mysql_con.o pgsql/pgsql_con.o sql_api.o\
		socket.o

CPP=g++
CFLAGS:=-g -Wall -D_REENTRANT -O2
CXXFLAGS:=-g -Wno-deprecated -Wall -I/usr/local/include/
LIBS:=-L/usr/local/lib -L/usr/lib -L/usr/lib64 -lpcre -levent -ldl

Fago-DBFW: $(OBJS)
	cd parser; make CXXFLAGS="$(CXXFLAGS)"
	cd lib; make;
	$(CXX) $(CXXFLAGS) -o Fago-DBFW $(OBJS) parser/parser.o parser/sql.o parser/sql.tab.o ${LIBS}

mysql/mysql_con.o:
	$(CXX) $(CXXFLAGS) -c mysql/mysql_con.cpp -o mysql/mysql_con.o

pgsql/pgsql_con.o:
	$(CXX) $(CXXFLAGS) -c pgsql/pgsql_con.cpp -o pgsql/pgsql_con.o

clean:
	rm -rf Fago-DBFW *.o mysql/*.o pgsql/*.o
	cd parser; make clean; cd ..
	cd lib; make clean; cd ..
