#include <Rcpp.h>
#include "constants.h"

using namespace Rcpp;

//' mean interbeef ebv
const double CONSTANTS::MEAN_ITB_EBV = 100;
//' standard deviation interbeef ebv
const double CONSTANTS::SD_ITB_EBV = 12;
//' length of ITB-Nr in number of characters
const unsigned CONSTANTS::ITB_NR_LENGTH = 19;
//' length of country code in ITB-NR
const unsigned CONSTANTS::COUNTRY_CODE_LENGTH = 3;
//' length of breed code in ITB-NR
const unsigned CONSTANTS::BREED_CODE_LENGTH = 3;
//' length of sex code in ITB-NR
const unsigned CONSTANTS::SEX_CODE_LENGTH = 1;
//' missing value code as string
const char CONSTANTS::STRING_NA[] = "-9999";
//' all letters in a string
const char CONSTANTS::LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";



