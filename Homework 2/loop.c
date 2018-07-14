long loop(long x, long n){

  long result = 0;
  long mask;

  for(mask = 1; mask != 0; mask << (n%256)){

      result |= (x & mask);
   }
  return result;
}
