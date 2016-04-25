#ifndef FAST_FUNCTION
#define FAST_FUNCTION
char *stringcopy(char *dest, const char *src,int length);
char *clone(const char *str);
float sqrtfloat(float number);

 
int getopt (int argc, char *argv[], char *optstring);

#define EQUALS(A,B) strncmp(A,B,strlen(A)+1)==0
#define STARTS(A,B) strncmp(A,B,strlen(B)+1)==0

#endif