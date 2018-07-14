static float u2f(unsigned u) { 
  union Data{
    int i;
    float f;
  } data;

  data.i = u;

  return data.f;

}


float fpwr4(int x){

  if(x < -74)
    {
      exp = 0;
      frac = 0;
    }
  else if( x < -63){
    exp = 0x0;
    frac = 1 << (2*x+149);
  }
  else if (x < 64){
    exp = 2*x + 127;
    frac = 0;
  }
  else {
    exp = 255;
    frac = 0;
  }

  u = exp << 23 | frac;
  return u2f(u);
}
