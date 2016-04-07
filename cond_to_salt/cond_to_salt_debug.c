#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>
#include <errno.h>
double Salinity(double C, double T, double P)
{
 double R, RT, RP, temp, sum1, sum2, result, val;
 double A1 = 2.070e-5, A2 = -6.370e-10, A3 = 3.989e-15, B1 = 3.426e-2, B2 = 4.464e-4, B3 = 4.215e-1, B4 = -3.107e-3, C0 = 6.766097e-1, C1 = 2.00564e-2, C2 = 1.104259e-4, C3 = -6.9698e-7, C4 = 1.0031e-9;
static double a[6] = {
 0.0080, -0.1692, 25.3851, 14.0941, -7.0261, 2.7081
};
static double b[6]={
 0.0005, -0.0056, -0.0066, -0.0375, 0.0636, -0.0144
};
 int i;
 if (C <= 0.0)
  result = 0.0;
 else {
  C *= 10.0;
  R = C / 42.914;
  val = 1 + B1 * T + B2 * T * T + B3 * R + B4 * R * T;
  if (val) RP = 1 + (P * (A1 + P * (A2 + P * A3))) / val;
  val = RP * (C0 + (T * (C1 + T * (C2 + T * (C3 + T * C4)))));
  if (val) RT = R / val;
  if (RT <= 0.0) RT = 0.000001;
  sum1 = sum2 = 0.0;
  for (i = 0;i < 6;i++)
  {
   temp = pow(RT, (double)i/2.0);
   sum1 += a[i] * temp;
   sum2 += b[i] * temp;
  }
   val = 1.0 + 0.0162 * (T - 15.0);
  if (val)
   result = sum1 + sum2 * (T - 15.0) / val;
  else
   result = -99.;
 }
return result;
}
void pdetails()
{
 fputs("Rev 1.0.0 (Thu Jun 11 16:41:38 UTC 2015)\n",stdout);
 exit(0);
}
void usage (char **argv)
{
      fputs("\nUsage               \n",stdout);
      printf("                %s [OPTIONS]\n\n",argv[0]);
      fputs("Arguments \n\n",stdout);
      fputs ("\
                -t --temp Temperature deg C ITPS-68\n\
                -c --cond Conductivity S/m\n\
                -p --pres Pressure in decibars\n\
                -v --version Show program version\n\
                -h --help Show help\n\
\n\n", stdout);
fputs("Examples :\n\t ",stdout);
printf("%s",argv[0]);
fputs("   --temp=28.8777 --cond=5.779922 --pres=2.011\n\t 35.446250",stdout);
fputs("\n\n\t OR\n\n\t ",stdout);
printf("%s",argv[0]);
fputs("   -t 28.8777 -c 5.779922 -p 2.011\n\t 35.446250\n",stdout);
fputs("\n         If you find any bugs report to ahegde@nio.org / akshay.k.hegde@gmail.com\n\n",stdout);
 exit(0);
}
void empty_check(char *c, char *s)
{
 if (c && c[0] == '\0')
 {
     printf("\n\t%s should not be empty\n\n");
     exit(0);
 }
}
int main(int argc, char **argv)
{
 int c, tf=0,cf=0,pf=0; float temp,cond,pres;
while (1)
    {
      static struct option long_options[] =
        {
   {"temp", required_argument, 0, 't'},
          {"cond", required_argument, 0, 'c'},
   {"pres", required_argument, 0, 'p'},
   {"version", no_argument, 0, 'v'},
    {"help", no_argument, 0, 'h'},
          {0, 0, 0, 0}
        };
      int option_index = 0;
      c = getopt_long(argc, argv,"t:c:p:vh",long_options, &option_index);
      if (c == -1)
        break;
      switch (c)
        {
        case 0:
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;
 case 'h':
   usage(argv);
   break;
        case 'v':
          pdetails();
   break;
 case 't':
          empty_check(optarg,"temp");
   temp = atof(optarg); tf=1;
   break;
 case 'c':
          empty_check(optarg,"cond");
   cond = atof(optarg); cf=1;
   break;
 case 'p':
          empty_check(optarg,"pres");
   pres = atof(optarg); pf=1;
   break;
 case '?':
          break;
        default:
          abort ();
        }
   }
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');
    }
  if(cf && tf && pf)
  {
   printf("%5.10lf\n", Salinity(cond,temp,pres));
   return 0;
  }else
  {
   usage(argv);
  }
}
