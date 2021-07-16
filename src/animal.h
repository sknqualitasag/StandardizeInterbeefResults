#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <strstream>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <map>
#include <vector>
#include <functional>
#include <sstream>

#include <set>
#include <sstream>
#include <vector>
#include <map>
#include "constants.h"



using namespace std;

class animal {
public:

  double meanWW,meanMatWW;
  string myId, breed, nameStr;
  bool base;
  string birthDateYYYYMMDDITB;
  int numDescendantsWWITB, numObsWWITB, numDaughterWWITB, numProgreniesWWITB, numProgreniesCHWWITB, numHerdsCHWWITB, itbPubldWWITB, itbPublmWWITB, statusOfBullInt;
  double solWWITB, scaledSolWWITB, accWWITB, solMatWWITB, scaledSolMatWWITB, matAccWWITB;

  animal(string myId, string birthDateYYYYMMDD, int numDescendants, int numObs, int numDaughter, int numProgrenies, double sol, double acc, double matSol, double matAcc, int numProgreniesCH, int numHerdsCH, double itbPubld, double itbPublm,  int statusOfBull, string name); //Sophie
  string indITBStr, birthYearStr, birthMonthStr, birthDayStr, indITBBreedStr, sexITBStr;
  int birthYearInt, birthMonthInt, birthDayInt;
  string getVerifiedITBNr(string id);
  string verifyBreed(string id);
  string verifySex(string id);


};

