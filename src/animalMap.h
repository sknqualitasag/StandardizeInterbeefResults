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
#include "animal.h"

using namespace std;


class animalMap : public map<string,animal*> {

public:
  void inputSolITB(char* fname1, string startYear, string endYear);
  void inputPubInfoITB(char* fname1);
  void standardizeITB(double mean, double std, string outfileITB, string basisBreedYearAbreviation);

};
