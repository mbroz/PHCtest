
// ------- PiQP.Cpp

char name[] = "PiQP - Uses digit extraction scheme to produce hex digits of pi.";
char version[] = "C++ Version 1.00, last revised: 1995-10-18, 0600 hour";
char author[] = "Copyright (c) 1995 by author: Harry J. Smith,";
char address[] = "19628 Via Monte Dr., Saratoga CA 95070.  All rights reserved.";

// This program employs the recently discovered digit extraction scheme
// to produce hex digits of pi.  This code is valid up to ic = 2^24 on
// systems with IEEE arithmetic.

// Developed by Simon Plouffe, Peter Borwein and David Bailey in FORTRAN,
// converted to C++ using Borland C++ Version 4.0 by Harry J. Smith

// Newsgroups: sci.math
// Subject: The 40 billion'th binary digit of Pi is 1
// From: Simon Plouffe <plouffe@cecm.sfu.ca>
// Date: 5 Oct 1995 23:20:57 GMT
//
// THE TEN BILLIONTH HEXADECIMAL DIGIT of Pi is 9
//
// By:  Simon Plouffe, Peter Borwein and David Bailey.
//
// The following is part of a paper titled "On The Rapid Computation of
// Various Polylogarithmic Constants".  The full text, as well as
// Fortran code, is available in
//
//           http://www.cecm.sfu.ca/~pborwein/
//
// as P123 under the link "Computing Pi and Related Matters".
// <snip>
// These calculations rest on three observations.  First, the d-th digit
// of 1/n is "easy" to compute.  Secondly, this scheme extends to
// certain polylogarithm and arctangent series.  Thirdly, very special
// types of identities exist for certain numbers like pi, pi^2, log(2) and
// log^2(2).  These are essentially polylogarithmic ladders in an integer
// base.  A number of these identities that we derive in this work appear
// to be new, for example the critical identity for the binary digits of
// pi is:
//
//      infinity
//       -----
//        \        (- n) /   4         2         1         1   \
// pi =    )     16      |------- - ------- - ------- - -------|
//        /              \8 n + 1   8 n + 4   8 n + 5   8 n + 6/
//       -----
//       n = 0
// <snip>

#include <math.h>     // Definitions for the math floating point package
#include <iostream> // Definition of cin, cout etc.
#include <iomanip>  // Definition of setw, setprecision etc.

using namespace std;

// Procedure prototypes
void   init(void);                           // Initialize
double series(int m, long ic);               // Evaluate the series sum_k ...
double expm(double p, double ak);            // Compute 16^p mod ak
void   ihex(double x, int nhx, char chx[]);  // Compute hex digits of fraction

// ------- Initialize
void init(void) {
	//cout << " [1;33;44m [2J";  // Ansi.Sys ESC seq. for YELLOW on BLUE, clrscr
	cout << "\n" << name << "\n" << version << "\n"
		<< author << "\n" << address << "\n";
	cout << "\nIn hex, Pi = 3.243F6A8885,A308D31319,8A2E037073,"
		<< "44A4093822,299F31D008,2EFA9 ...\n";
	cout << "\nThere are times when the answer is only good to 10 hex digits.\n"
		<< "If the 11th or 12th hex digit output is 0 or F you should disreguard\n"
		<< "trailing 0's of F's respectively and disreguard one more digit.\n"
		<< "Input 6006 to see what I am driving at. Correct answer is A28C0F586E00\n";
	cout << "\nInput can be from 1 through 16777217 = 2^24 + 1.\n";
	cout << setprecision(17);
} // --end-- init

// ------- Evaluate the series sum_k 16^(ic-k)/(8*k+m)
double series(int m, long ic) {
	//
	// This routine evaluates the series sum_k 16^(ic-k)/(8*k+m)
	// using the modular exponentiation technique.
	//
	const double eps = 1.0e-17;
	double ak, p, s, t;
	long k;

	s = 0.0;
	for (k = 0; k < ic; k++) { // Sum the series up to ic.
		ak = 8 * k + m;
		p = ic - k;
		t = expm(p, ak);
		s += t / ak;
		s -= floor(s);
	}
	p = 16.0;  t = 1.0;
	for (k = ic; t > eps; k++) { // Compute a few terms where k >= ic.
		ak = 8 * k + m;
		p /= 16.0;
		t = p / ak;
		s += t;
		s -= floor(s);
	}
	return s;
} // --end-- series

// ------- Compute 16^p mod ak
double expm(double p, double ak) {
	//
	// expm = 16^p mod ak.  This routine uses the left-to-right binary
	// exponentiation scheme.  It is valid for  ak <= 2^24.
	//
	const int ntp = 25;
	double p1, pt, r;
	static double tp[ntp] = { 0.0 }; // tp = power of two table.
	int i;

	if (tp[0] == 0.0) { // If this is the first call, fill the power of two table.
		tp[0] = 1.0;
		for (i = 1; i < ntp; i++)
			tp[i] = 2.0 * tp[i - 1];
	}
	if (ak == 1.0)  return 0.0;

	for (i = 0; tp[i] <= p; i++); // Find the greatest power of two <= p.
	pt = tp[i - 1];
	p1 = p;
	r = 1.0;

	while (pt >= 1.0) { // Perform binary exponentiation algorithm modulo ak.
		if (p1 >= pt) {
			r = fmod(16.0 * r, ak);
			p1 -= pt;
		}
		pt *= 0.5;
		if (pt >= 1.0)
			r = fmod(r * r, ak);
	}
	return fmod(r, ak);
} // --end-- expm

// ------- Compute the first few hex digits of the fraction of x
void ihex(double x, int nhx, char chx[]) {
	//
	// This returns, in chx, the first nhx hex digits of the fraction of x.
	//
	double y;
	int i;
	const char hx[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	y = fabs(x);
	for (i = 0; i < nhx; i++) {
		y = 16.0 * (y - floor(y));
		chx[i] = hx[(int)(y)];
	}
	return;
} // --end-- ihex

// ------- main program PiQP
int main(void) {
	// ic is the hex digit position -- output begins at position st = ic + 1.
	long ic, st = 100000L;
	const int nhx = 12;
	double pid, s1, s2, s3, s4;
	char chx[nhx];
	int i;

	init();
	while (st > 0) {
		cout <<	"\nAt what fractional hex digit would you like to start? (0 to exit): ";
		cin >> st;  ic = st - 1;
		if ((st > 0) && (ic <= 16777216L)) 
		{
			s1 = series(1, ic);
			s2 = series(4, ic);
			s3 = series(5, ic);
			s4 = series(6, ic);
			pid = fmod(4.0 * s1 - 2.0 * s2 - s3 - s4, 1.0);
			if (pid < 0)  pid += 1.0;
			ihex(pid, nhx, chx);
			cout << "Computed sum = " << pid << "\nStarting at position " << st << " the hex digits are: ";
			for (i = 0; i < nhx; i++)  cout << chx[i];
			cout << "\n";
		}
	}
	return 0;
} // --end-- main PiQP
