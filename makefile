#			Linux 
#CC       = g++
#CCOPTS   = -c -I/usr/include/X11R5 -I/usr/X11R6/include -I/usr/include/Motif1.2 -g -DLINUX
#LINK     = g++
#LINKOPTS = -static -L/usr/lib/Motif1.2 -L/usr/lib/X11R5 -lm

#			HP-UX
#CC       = g++
#CCOPTS   = -c -O
LINK     = g++
#LINKOPTS = -lm -lcryptopp

UTIL = AttrGenerator.o utility.o ReadTopology.o
#UTIL  = utility.o func.o dataobj.o blk_file.o MRtree.o
#UTIL  = utility.o AttrGenerator.o

#.cc.o:
#	$(CC) $(CCOPTS) $<

#all: cont

#utility.o: utility.cc utility.h 

#func.o: func.cpp func.h 

#dataobj.o: dataobj.cpp dataobj.h 

#blk_file.o: blk_file.cpp blk_file.h 

#MRtree.o: MRtree.cpp MRtree.h 

#bmain.o: bmain.cc

#qmain.o: qmain.cc

AttrGenerator.o: AttrGenerator.cpp AttrGenerator.h

utility.o: utility.cpp utility.h

ReadTopology.o: ReadTopology.cpp ReadTopology.h

main: main.o $(UTIL)
	$(LINK) -o main main.o $(UTIL) $(LINKOPTS)

#bmain: bmain.o $(UTIL)
#	$(LINK) -o bmain bmain.o $(UTIL) $(LINKOPTS)

#qmain: qmain.o $(UTIL)
#	$(LINK) -o qmain qmain.o $(UTIL) $(LINKOPTS)


clean:
	rm *.o *stackdump *.exe
