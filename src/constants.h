//
//
//   Header for global constants
//

#ifndef Const_h
#define Const_h


class CONSTANTS {
public:
  //' mean interbeef ebv
  static const double MEAN_ITB_EBV;
  //' standard deviation interbeef ebv
  static const double SD_ITB_EBV;
  // length of ITB-Nr in number of characters
  static const unsigned ITB_NR_LENGTH;
  // number of characters that correspond to the country code
  static const unsigned COUNTRY_CODE_LENGTH;
  //' length of breed code in ITB-NR
  static const unsigned BREED_CODE_LENGTH;
  //' length of sex code in ITB-NR
  static const unsigned SEX_CODE_LENGTH;
  //' missing value code as string
  static const char STRING_NA[];
  // string that corresponds to all letters
  static const char LETTERS[];






};

#endif
