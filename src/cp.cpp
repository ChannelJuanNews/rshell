#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctime>
#include "Timer.h"

using namespace std;

int main( int argc, char *argv[] ){
	// if not enough arguments then exit
	if ( argc < 3 ) {
		cout << "Error! Not enough arguments." << endl;
		exit(1);
	}
	// if optional flag is passed in
	if ( argc == 4 ){




		Timer one;
		double oneusrTime;
		double onewallTime;
		double onesysTime;
		one.start();	
		//=======================FIRST ONE=============================
		cout << "Using istream and ostream" << endl;
		//Open file
		ifstream fin(argv[1]);
		if(!fin.is_open()){
			cout << "Error opening source file" << endl;
			exit(1);
		}
		ifstream fcheck(argv[2]);
		if(fcheck.is_open()){
			cout << "Error! Dest file already exists!" << endl;
			exit(1);
		}
		ofstream fout(argv[2]);
		
		char c;
		while (fin.get(c)){
			fout.put(c);
		}
		fin.close();
		fout.close();
		one.elapsedTime(onewallTime, oneusrTime, onesysTime);
                cout << "First Method: " << endl;
                cout << "\tWall time: " << onewallTime << endl;
		cout << "\tUser time: " << oneusrTime << endl;
	        cout << "\tSystem time: " << onesysTime << endl << endl;


		//=========================SECOND ONE===========================
		cout << "Using read() and write()" << endl;
		Timer two;
		double twousr;
		double twowall;
		double twosys;
		two.start();
		int fdnew;
		int fdold;
		if(-1 == (fdnew = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
		{
			perror("Open");
			exit(1);
		}
		if(-1 == (fdold = open(argv[1], O_RDONLY)))
		{	
			perror("Open");
			exit(1);
		}
		int size;
		char d;
		if(-1 == (size = read(fdold, &d, 1)))
		{
			perror("Write");
			exit(1);
		}
		while(size > 0)
		{
			if(-1 == write(fdnew,&d,size))
			{
				perror("write");
				exit(1);
			}
			if(-1 == (size = read(fdold,&d,1)))
			{
				perror("read");
				exit(1);
			}
		}
		if(-1 == close(fdnew))
		{
			perror("close");
			exit(1);
		}
		if(-1 == close(fdold))
		{
			perror("close");
			exit(1);
		}
		two.elapsedTime(twowall,twousr,twosys);
		cout << "Second Method: " << endl;
		cout << "\tWall time: " << twowall << endl;
		cout << "\tUser time: " << twousr << endl;
		cout << "\tSystem time: " << twosys << endl << endl;


		//==========================THIRD ONE==============================
		cout << "Using read() and write() W/ Buffer" << endl;
		//int fdnew;
		//int fdold;
		Timer three;
                double threeusr;
                double threewall;
                double threesys;
                three.start();


		if(-1 == (fdnew = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
		{
			perror("Open");
			exit(1);
		}
		if(-1 == (fdold = open(argv[1], O_RDONLY)))
		{
			perror("Open");
			exit(1);
		}
//		int size;
		char e[BUFSIZ];
		if(-1 == (size = read(fdold, e, sizeof(e))))
		{
			perror("Write");
			exit(1);
		}
		while(size > 0)
		{
			if(-1 == write(fdnew,e,size))
			{
				perror("write");
				exit(1);
			}
			if(-1 == (size = read(fdold,e,sizeof(e))))
			{
				perror("read");
				exit(1);
			}
		}
		if(-1 == close(fdnew))
		{
			perror("close");
			exit(1);
		}
		if(-1 == close(fdold))
		{
			perror("close");
			exit(1);
		}

		three.elapsedTime(threewall,threeusr,threesys);
                cout << "Third Method: " << endl;
                cout << "\tWall time: " << threewall << endl;
                cout << "\tUser time: " << threeusr << endl;
                cout << "\tSystem time: " << threesys << endl << endl;



	}
	// else run fastest one
	else{
			




			





		cout << "Using read() and write() W/ Buffer" << endl;
		int fdnew;
		int fdold;
		if(-1 == (fdnew = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
		{
			perror("Open");
			exit(1);
		}
		if(-1 == (fdold = open(argv[1], O_RDONLY)))
		{
			perror("Open");
			exit(1);
		}
		int size;
		char c[BUFSIZ];
		if(-1 == (size = read(fdold, c, sizeof(c))))
		{
			perror("Write");
			exit(1);
		}
		while(size > 0)
		{
			if(-1 == write(fdnew,c,size))
			{
				perror("write");
				exit(1);
			}
			if(-1 == (size = read(fdold,c,sizeof(c))))
			{
				perror("read");
				exit(1);
			}
		}
		if(-1 == close(fdnew))
		{
			perror("close");
			exit(1);
		}
		if(-1 == close(fdold))
		{
			perror("close");
			exit(1);
		}
		
	}
	return 0;
}
