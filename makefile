BookBuilder: Page.o IndexTerm.o indexConstants.o Index.o bookMaker.o Book.o
	g++ -g -std=gnu++11 Page.o indexConstants.o Index.o bookMaker.o Book.o IndexTerm.o
	mv a.out BookBuilder

Page.o: Page.cpp Page.h
	g++ -g -std=gnu++11 -c Page.cpp

IndexTerm.o: IndexTerm.cpp IndexTerm.h
	g++ -g -std=gnu++11 -c IndexTerm.cpp

indexConstants.o: indexConstants.cpp indexConstants.h
	g++ -g -std=gnu++11 -c indexConstants.cpp

Index.o: Index.cpp Index.h
	g++ -g -std=gnu++11 -c Index.cpp

bookMaker.o: bookMaker.cpp
	g++ -g -std=gnu++11 -c bookMaker.cpp

Book.o: Book.cpp Book.h
	g++ -g -std=gnu++11 -c Book.cpp
