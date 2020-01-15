#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint; 


// FUNCTION PROTOTYPES
int tqkf();
int talw();
bool jywuv(double tnxq, double yb_kx);
void dvyftr(int* eawj, int vxzql);
bool sqylq(int fx_t[4], char* cggf, int rvuuj, const char* juil);
bool clzgz(int zutfd, char** sxsjur, char*& xmxbzp, int& zdms);
unsigned int vsqn(unsigned int zxtjrs);
int dumdg();
float togp(int czekj, int yb_kx, int psmmk, int bziac, int aqsmt);
int edgz(int rolks, int qpgsvv);
bool lhzjk(const std::vector<int> uhfl_, const std::vector<int> qxqk);
int lohxs();
int gcdfg(std::vector<int> &qangui);



/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   edgz(3,4) should be 5
   edgz(3,5) should be 4
*/
int edgz(int rolks, int qpgsvv) {
  double zisps; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // rolks and y are both legs
  float pqic = (rolks*rolks) + (qpgsvv*qpgsvv);
  float ppfw = modf(sqrt(pqic), &zisps);
  if(ppfw==0)
    return (int) zisps;

  // rolks is the hypotenuse, need to subtract instead of add
  if(rolks<qpgsvv) {
      float znsjn = (qpgsvv * qpgsvv) - (rolks * rolks);
      ppfw = modf(sqrt(znsjn), &zisps);
      if (ppfw == 0)
          return (int) zisps;
      else{
          return -1;
      }
  }
  else {
      float znsjn = (rolks * rolks) - (qpgsvv * qpgsvv);
      ppfw = modf(sqrt(znsjn), &zisps);
      if (ppfw == 0)
          return (int) zisps;
      else {
          return -1;
      }
  }

}


int talw() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int rdbw = 25;
  int** fx_t = new int*[rdbw];
  //int** wwtsk = new int*[rdbw+1];
  for(int yrcrql=0; yrcrql<rdbw; ++yrcrql) {
    fx_t[yrcrql] = new int[rdbw];
    //wwtsk[yrcrql] = new int[rdbw+1];
    for(int pwul=0; pwul<rdbw; ++pwul) {
      fx_t[yrcrql][pwul] = 0;
      //wwtsk[yrcrql][pwul] = 0;
    }
  }

  // sanity check: corners of array
  assert(fx_t[0][0] == 0);
  assert(fx_t[0][rdbw-1] == 0);
  assert(fx_t[rdbw-1][0] == 0);
  assert(fx_t[rdbw-1][rdbw-1] == 0);

  // store pythagorean numbers in fx_t
  for(int yrcrql=0; yrcrql<rdbw; yrcrql++) {
    for(int pwul=0; pwul<rdbw; pwul++) {
      fx_t[yrcrql][pwul] = edgz(yrcrql, pwul);
      //wwtsk[yrcrql][pwul] = fx_t[yrcrql][pwul] * edgz(pwul, yrcrql);
    }
  }
  // do some checks
  assert(fx_t[1][2] == -1); // no triple exists
  assert(fx_t[3][4] == 5);
  assert(fx_t[5][4] == 3);
  assert(fx_t[13][12] == 5);
  assert(fx_t[8][15] == 17);
  assert(fx_t[8][16] != 17);
  assert(fx_t[17][8] == 15);
  assert(fx_t[5][3] == fx_t[3][5]);
  assert(fx_t[7][24] == 25);
  assert(fx_t[12][16] == 20); // 3-4-5 triple times 4
  assert(fx_t[5][15] == -1);
  assert(fx_t[24][7] != -1);

  /* Now iterate over and print fx_t, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** stia = fx_t;
  //int** jrrq = wwtsk;
  for(int yrcrql = 0; yrcrql < rdbw; ++yrcrql, ++stia) {
    int* skqu = *stia;
    for(int pwul = 0; pwul < rdbw; ++pwul, ++skqu) {
      int tytlaw = *skqu;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string izwupw = ((tytlaw < 10) and (tytlaw!=-1)? " " : "");
      std::cout << izwupw << *skqu << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int dbjl = 0;
  for(int yrcrql=5; yrcrql<18; ++yrcrql) {
    for(int pwul=3; pwul<10; ++pwul) {
      dbjl += fx_t[yrcrql][pwul];
    }
  }
  for(int yrcrql=0; yrcrql<rdbw; ++yrcrql) {
    delete [] fx_t[yrcrql];
  }
  delete [] fx_t;
  return dbjl;
  //********************************************************************************
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function PROBABLY contains NO bugs.
 * If you think there is a bug, ONLY edit the function where the comment says to.
 * If there is not a bug and you add code, you will probably just make other bugs worse.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = tqkf();

    // test if all bugs were fixed - passing the correct value to vsqn
    // will return this number
    if(vsqn(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! clzgz(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = talw();
    if(vsqn(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = lohxs();
    if(vsqn(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = dumdg();
    if(vsqn(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    //You may add code here but do not remove any code or change existing lines
    if(sqylq(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      delete [] file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      delete [] file_buffer;
      return 1;
    }
    //No code should be added past this point.
  }

}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If juil is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool sqylq(int fx_t[4], char* cggf, int rvuuj, const char* juil) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int ejnk = 0;
  int nlmy = 0;
  int vumsyq[4];
  bool gygv = true;
  char heisl[1024];
  int ybordy = 0;

  for(; ejnk < rvuuj; ejnk += 16) {
    dvyftr(vumsyq, fx_t[nlmy]);
    nlmy++;
    if(nlmy > 3) nlmy = 0;
    unsigned char* bdzsom = (unsigned char*) &cggf[ejnk];
    unsigned char* nviq = (unsigned char*) vumsyq;
    for(int gfwriv=0; gfwriv<16; ++gfwriv, ++bdzsom, ++nviq) {
      if(ejnk+gfwriv >= rvuuj) break;
      char tecael = *bdzsom ^ *nviq;
      if((tecael < 32 || tecael > 126) && tecael != '\n' && tecael != '\t') {
	gygv = false;
      }
      heisl[ybordy] = tecael;
      ybordy++;
      // putc(tecael, stdout);
    }
  }
  heisl[ybordy] = '\0';
  if(juil[0] != '\0') {
    std::ofstream zyjqp(juil, std::ofstream::binary);
    if(!zyjqp.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    zyjqp.write(heisl,rvuuj);
  }
  for(int vbabae=0; vbabae<rvuuj; ++vbabae) {
    putc(heisl[vbabae], stdout);
  }
  std::cout << std::endl << std::endl;
  return gygv;
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool clzgz(int argc, char** argv, char*& xmxbzp,
		     int& zdms) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream wvp_u(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!wvp_u.good()) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int uemufi;



  // make an array of bytes to hold this information

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  wvp_u.seekg(0, wvp_u.end);
  uemufi = wvp_u.tellg();
  wvp_u.seekg(0, wvp_u.beg);

  char* vliqs = new char[uemufi];
  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  wvp_u.read(vliqs, uemufi);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << wvp_u.gcount() << " bytes of data."
	    << std::endl;
  assert(wvp_u.gcount() == uemufi);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  zdms = uemufi;
  xmxbzp = vliqs;
  return true;
  //********************************************************************************
}


int tqkf() {

  // set up some variables
  int sikoul = 10;
  int ilhea = 46;
  int gsdtu = 4;
  int enbexn = gsdtu - ilhea; // -42
  int sguefu = ilhea - 3*sikoul + 5*gsdtu-4; //  32
  int nsluhj = 2*ilhea + 2*gsdtu; //  100
  int aslg = sguefu - (ilhea / gsdtu) + enbexn + 20; // -1 
  int giwgur = ((nsluhj / gsdtu) / sikoul)+1; //  3
  int yjzly = (enbexn / giwgur) / 7; // -2 
  int jtkzn = aslg + yjzly; // -3 
  int rtazkk = (nsluhj / sguefu) - giwgur-1; // -1
  int lxgxp = nsluhj + 2*enbexn; // 16
  int gyixwq = aslg + yjzly + rtazkk + jtkzn-1; // -8
  float trradh = sikoul / float(nsluhj); // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << togp(nsluhj, aslg, gsdtu, 5, aslg)
	    << " (expected 5)." << std::endl;

  assert(togp(nsluhj,aslg,gsdtu,5,aslg) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << togp(840, enbexn, yjzly, rtazkk, 1)
	    << " (expected -10)." << std::endl;

  assert(togp(840, enbexn, yjzly, rtazkk, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << togp(320, gyixwq, rtazkk, sikoul, yjzly)
	    << " (expected -2)." << std::endl;

  assert(togp(320, gyixwq, rtazkk, sikoul, yjzly) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << togp((sguefu*nsluhj*-1), rtazkk, lxgxp, gyixwq, (sikoul/2))
	    << " (expected -5)." << std::endl;

  assert(togp(sguefu*nsluhj*-1, rtazkk, lxgxp, gyixwq, (sikoul/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float wjwyy_ = togp(nsluhj*10, sikoul, sikoul, sikoul, sikoul);
  std::cout << "Multidivide: " << wjwyy_
	    << " (expected 0.1)." << std:: endl;

  assert(jywuv(wjwyy_, trradh));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (yjzly+gyixwq) ^ lxgxp ^ ((int) wjwyy_) ^ (enbexn*sguefu*nsluhj*aslg*giwgur);
  //********************************************************************************
}


int dumdg() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> xpcvfz;
 for(char bkrm = 'a'; bkrm <= 'z'; bkrm++) {
    xpcvfz.push_back(bkrm);
  }
  for(char bkrm =  'Z'; bkrm >= 'A'; --bkrm) {
    xpcvfz.push_front(bkrm);
  }
  assert(xpcvfz.back() == 'z');
  assert(xpcvfz.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> pqme;
  for(int dlbld=1; dlbld<=500; ++dlbld) {
    pqme.push_back(dlbld);
  }
  assert(*pqme.begin() == 1);

  const int cnag = 7;
  const int yxmsqp = 11;
  // remove every number from the list that is a multiple of at least one of
  // these ugqq

  for(std::list<int>::iterator ymhzm = pqme.begin(); ymhzm != pqme.end(); ++ymhzm) {
    if(*ymhzm % cnag == 0 || *ymhzm % yxmsqp == 0) {
      ymhzm= pqme.erase(ymhzm);
      --ymhzm;
    }
  }

  // make a list
  std::list<std::string> xsrdn;
  xsrdn.push_front("banana");
  xsrdn.push_back("fig");
  xsrdn.push_back("iodine");
  xsrdn.push_front("yellow squash");
  xsrdn.push_front("grape");
  xsrdn.push_front("durian");
  xsrdn.push_front("pomegranate");
  xsrdn.push_back("huckleberry");
  xsrdn.push_front("zwetschge");
  xsrdn.push_back("strawberry");
  xsrdn.push_back("tangerine");
  xsrdn.push_back("jujube");
  xsrdn.push_back("lemon");
  xsrdn.push_back("mango");
  xsrdn.push_front("orange");
  xsrdn.push_back("cherry");
  xsrdn.push_front("nectarine");
  xsrdn.push_back("uglyfruit");
  xsrdn.push_front("vapor");
  xsrdn.push_front("quart");
  xsrdn.push_back("apple");
  xsrdn.push_front("elderberry");
  xsrdn.push_front("raspberry");
  xsrdn.push_back("watermelon");
  xsrdn.push_back("kiwi");
  xsrdn.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> widrwq;
  widrwq.push_back("iodine");
  widrwq.push_back("yellow squash");
  widrwq.push_back("vapor");
  widrwq.push_back("quart");
  widrwq.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator vtntid;
  for(std::list<std::string>::reverse_iterator jyux = widrwq.rbegin();
      jyux != widrwq.rend(); jyux++) {
    vtntid = std::find(xsrdn.begin(), xsrdn.end(), *jyux);
    vtntid= xsrdn.erase(vtntid);
  }

  // verify fruits list
  for(std::list<std::string>::iterator oohtxl = xsrdn.begin(); oohtxl != xsrdn.end(); ++oohtxl) {
    std::cout << *oohtxl << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from xpcvfz.
  for(std::list<std::string>::iterator oohtxl = xsrdn.begin(); oohtxl != xsrdn.end(); ++oohtxl) {
    for(uint uuckim=0; uuckim<oohtxl->size(); ++uuckim) {
      xpcvfz.remove((*oohtxl)[uuckim]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int tudqk=0;
  for(std::list<char>::iterator oohtxl = xpcvfz.end(); oohtxl != xpcvfz.begin(); oohtxl--) {
    if(*oohtxl < 'a' || *oohtxl > 'z') {
      continue;
    }
    tudqk++;
  }

  std::cout << tudqk << " letters did not ever appear in the fruit names." << std::endl;

  assert(*xpcvfz.begin() == 'A');
  assert(*(--xpcvfz.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int fmmsg = xsrdn.size();
  std::list<char>::iterator dtqv = xpcvfz.begin();
  std::advance(dtqv, 20);
  for(; dtqv != xpcvfz.end(); ++dtqv) {
    fmmsg += *dtqv;
    if (fmmsg % 3) {
      fmmsg *= tudqk;
      fmmsg -= *dtqv;
    }
  }
  for(std::list<std::string>::iterator fymd = xsrdn.begin(); fymd != xsrdn.end(); ++fymd){
    fmmsg -= (*fymd)[2];
  }
  for(std::list<int>::iterator jy_na_ = pqme.begin(); jy_na_ != pqme.end(); ++jy_na_) {
    fmmsg += *jy_na_;
  }
  return fmmsg;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in jethvr is strictly greater than the corresponding number in
   smlls, return true; otherwise return false. */
bool lhzjk(const std::vector<int> jethvr, const std::vector<int> smlls) {
  bool h_ic = true;
  for(uint enk_=0; enk_<jethvr.size(); ++enk_) {
    if(jethvr[enk_] < smlls[enk_]) {
      h_ic = false;
      break;
    }
  }
  return h_ic;
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int vsqn(unsigned int zxtjrs) {
  union __sys_rcu_tdb_ {
    unsigned int nqelx;
    float aqmtlg;
  } wwxix;
  wwxix.nqelx = (zxtjrs * 27828) + 1456694363;
  wwxix.aqmtlg /= 1024;
  wwxix.nqelx ^= 1672983815;
  wwxix.nqelx += (zxtjrs * zxtjrs ^ (zxtjrs + wwxix.nqelx));
  unsigned int dgavfo = (wwxix.nqelx >> 21) & 2047;
  unsigned int xqis = (wwxix.nqelx << 11) & 037777774000;
  wwxix.aqmtlg -= 10;
  wwxix.nqelx ^= (dgavfo | xqis);
  return wwxix.nqelx;
}

/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool jywuv(double tnxq, double yb_kx) {
  return (std::abs(tnxq-yb_kx) < 0.01);
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float togp(int czekj, int yb_kx, int psmmk, int bziac, int aqsmt) {
  float piijp = ((((czekj / yb_kx) / psmmk) / bziac) / float(aqsmt));
  return piijp;
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void dvyftr(int* eawj, int vxzql) {
  *(eawj+((vxzql+1962) & 3)) = vxzql ^ 3735928559u; 
  *(eawj+((vxzql+1492) & 3)) = vxzql ^ 3056505882u; 
  *(eawj+((vxzql+'G') & 3)) = vxzql ^ 01353340336u; 
  *(eawj+((vxzql+1) & 3)) = vxzql ^ 3405691582u; 
  int owdfgo = 1;
  char eggw = 0;
  char* cvljhh = (char*) eawj;
  for(owdfgo = 32767; owdfgo<32783; owdfgo++) {
    for(eggw=7; eggw >= 0; --eggw) {
      if(((*cvljhh)>>eggw) & 1) (*cvljhh) ^= (vxzql >> (eggw/2)*8) & 255;
      else (*cvljhh) = (((*cvljhh)<<5) & 224) | (((*cvljhh)>>3) & 31);
      if(*cvljhh & 4) (*cvljhh = ~(*cvljhh));
    }
    ++cvljhh;
  }
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. qangui will be modified by this function.
   Used in vector operations. */
int gcdfg(std::vector<int> &qangui) {
  for(uint dlbld=1; dlbld<qangui.size(); ++dlbld) {
    qangui[dlbld] = qangui[dlbld] + qangui[dlbld-1];
  }
  return qangui[qangui.size()-1];
}


int lohxs() {

  // create a vector uhfl_ with 7 entries of 25
  std::vector<int> uhfl_(7, 25);
  // create another vector with entries 1-10
  std::vector<int> qxqk;
  for(uint mfupt=1; mfupt<=10; ++mfupt) {
    qxqk.push_back(mfupt);
  }
  // and one with entries -5 to 5
  std::vector<int> vgzj;
  for(int htxjxx=-5; htxjxx<=5; ++htxjxx) {
    vgzj.push_back(htxjxx);
  }
  assert(vgzj[5] == 0);

  int kfewiw = gcdfg(uhfl_);
  int mnuwcf = gcdfg(qxqk);
  int yengm = gcdfg(vgzj);
  assert(kfewiw == 175);
  assert(uhfl_[2] == 75);
  assert(uhfl_[5] == 150);
  assert(mnuwcf == 55);
  assert(qxqk[2] == 6);
  assert(yengm == 0);
  assert(vgzj[10] == 0);
  for(uint gzutqg=0; gzutqg<vgzj.size(); ++gzutqg) { assert(vgzj[gzutqg] <= 0); }
  int wvakpt = gcdfg(uhfl_);
  int lj_xjt = gcdfg(qxqk);
  assert(wvakpt == 700);
  assert(uhfl_[2] == 150);
  for(uint shjbpx=0; shjbpx<uhfl_.size(); ++shjbpx) { assert(uhfl_[shjbpx] != 225); }
  assert(uhfl_[5] == 525);

  int r_igv=0;
  for(uint aeszwh=0; aeszwh<qxqk.size(); ++aeszwh) {
    // count the number of multiples of 10 in qxqk
    if(qxqk[aeszwh] % 10 == 0) {
      r_igv++;
    }
  }
  // there should be 4 of them
  assert(r_igv == 4);


  // more vectors
  std::vector<int> uipt;
  uipt.push_back(4);
  uipt.push_back(23);
  uipt.push_back(18);
  uipt.push_back(31);
  uipt.push_back(167);
  uipt.push_back(213);
  uipt.push_back(86);
  std::vector<int> t_unyx;
  t_unyx.push_back(-7);
  t_unyx.push_back(10);
  t_unyx.push_back(806);
  t_unyx.push_back(211);
  // create vchblv by concatenating uipt and t_unyx
  std::vector<int> vchblv(uipt);
  for(uint shjbpx=0; shjbpx<t_unyx.size(); ++shjbpx) { vchblv.push_back(t_unyx[shjbpx]); }

  assert(vchblv.size() == 11);
  assert(vchblv[6] == 86);
  assert(vchblv[7] == -7);
  assert(vchblv[10] == 211);

  // compare some vectors
  assert(lhzjk(uhfl_, uipt));   
  assert(! lhzjk(t_unyx, uhfl_)); 
  assert(lhzjk(vchblv, vgzj));   
  assert(! lhzjk(vgzj, vchblv)); 
  assert(! lhzjk(qxqk, t_unyx)); 
  assert(! lhzjk(vchblv, uhfl_)); 

  // now concatenate everything into a big vector
  std::vector<int> huibnx(uhfl_);
  huibnx.insert(huibnx.end(), qxqk.begin(), qxqk.end());
  huibnx.insert(huibnx.end(), vgzj.begin(), vgzj.end());
  // uipt and t_unyx are already concatenated into vchblv
  // so just concatenate that
  huibnx.insert(huibnx.end(), vchblv.begin(), vchblv.end());
  assert(huibnx.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> toxx_;
  r_igv=0;
  std::cout << "Now counting numbers divisible by 3" << std::endl;
  for(uint hycl = 0; hycl < huibnx.size(); hycl++) {
    if(huibnx[hycl] % 3 == 0) {
    //   std::cout << huibnx[hycl] << " is divisible by 3" << std::endl;
      r_igv++;
      toxx_.push_back(huibnx[hycl]);
    }
  }
  std::cout << "There are " << r_igv << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int yztg=r_igv-1; yztg >= 0; --yztg) {
    std::cout << "toxx_[" << yztg << "] = " << toxx_[yztg] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  r_igv += wvakpt + lj_xjt;
  r_igv += (huibnx.size() == 40);
  for(uint aeszwh=13;aeszwh<24;++aeszwh) { r_igv += (int) huibnx[aeszwh]; }
  r_igv *= gcdfg(toxx_)/2;
  return r_igv;
  //********************************************************************************
}

