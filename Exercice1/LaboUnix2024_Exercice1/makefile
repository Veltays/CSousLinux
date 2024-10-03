UNIX_Exercice1: main.o mainwindow.o moc_mainwindow.o
	g++ main.o mainwindow.o moc_mainwindow.o -o UNIX_Exercice1


mainwindow.o: mainwindow.cpp mainwindow.h
	g++ mainwindow.cpp -o mainwindow.o

moc_mainwindow.o: moc_mainwindow.cpp ui_mainwindow.h
	g++ moc_mainwindow.cpp -c


main.o : main.cpp mainwindow.o moc_mainwindow.o
	g++ main.cpp -o main.o

