/*
	Author: Hrvoje Tadin

	Application of logical operations by an example
	in which the parameters are defined for transmitting
	data via a serial port on a computer.
*/

#include<iostream>
#include<bitset>

using namespace std;

int main() {

	/*
		eample of the layout of bit
		parameters for serial communication:

		[B7][B6][B5][B4][B3][B2][B1]
	*/

	// Baud rate, numbered 0-7.
	// Located in the three lowest bits.
	enum {
		Baud110 = 0, Baud150, Baud300, Baud600,
		Baud1200, Baud2400, Baud4800, Baud9600
	};

	// Number of bits per data, 7 (B3=0) or 8 (B3=1)
	enum numOfBits { Bits7 = 0x00, Bits8 = 0x08 };

	// Number of stop-bits (placed in B4 and B5), if its one stop-bit B4 = 1
	// but if there are two stop-bits, then B5 = 1
	enum numOfStopBits { StopB1 = 0x10, StopB2 = 0x20 };

	// Parity data goes in the two highest bits
	enum Parity { ParityNo = 0x00, ParityOdd = 0x40, ParityEven = 0x80 };


	/*INSERTION OF DATA*/

	// one possible combination:
	unsigned int serCom{ Baud1200 | Bits8 | StopB2 | ParityNo };

	cout << "serCom: " << bitset<8>(serCom) << endl;


	/*EXTRACTION OF DATA*/

	// determining the speed by using '&' operator:
	unsigned int speed{ serCom & 0x07 }; //output: 4


	// 8 bits were transmitted?
	bool isItEightBits = serCom & 0x08; // output: true

	// determining the number of stop-bits by using a mask 0x30
	// which have a '1' on places B4 and B5:

	unsigned int numOfStopBits{ serCom & 0x30 }; // output: 32; 100000 in binary

	// below, we move the obtained binary string to the right by 4 places,
	// so that B4 and B5 reach B0 and B1, then we get the number of stop-bits, ie '2'

	numOfStopBits = numOfStopBits >> 4;
	cout << numOfStopBits << endl;;

	cin.sync();
	cin.get();

	return 0;
}