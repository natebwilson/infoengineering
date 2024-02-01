//compartmentalized to make main sketch easier to read


uint8_t frame[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


//used to flip the pixel at given matrix address

void flipPixel(int rowf, int columnf){ //using rowf and columnf to distinguish from global variables
  if(frame[rowf][columnf] == 0){
    frame[rowf][columnf] = 1;
  }
  else{
    frame[rowf][columnf] = 0;
  }
}

//this function is necessary to convert the alphanumeric input from the webpage into useable indices
int letterToColumn(char letter){ 
  //the char datatype stores letters as their ASCII index, in which all uppercase letters are 32 less than their lowercase counterparts
  //this if function converts those letters into lowercase if they are not already
  if(letter < 77){ 
    letter += 32;
  } 
  //returns a column for each letter a-l, a returns zero since our frame array is zero indexed (the first column is column 'o')
  switch(letter){
    case 'a':
      return 0;
    case 'b':
      return 1;
    case 'c':
      return 2;
    case 'd':
      return 3;
    case 'e':
      return 4;
    case 'f':
      return 5;
    case 'g':
      return 6;
    case 'h':
      return 7;
    case 'i':
      return 8;
    case 'j':
      return 9;
    case 'k':
      return 10;
    case 'l':
      return 11;
  }
}

