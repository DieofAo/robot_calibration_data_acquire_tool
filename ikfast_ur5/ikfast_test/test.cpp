#include <iostream>
#include <stdio.h>
#include <ur_kinematics/ikfast.h>
#include <ur_kinematics/ur_kin.h>
#include <math.h>

using namespace std;
using namespace ur_kinematics;

int main(int argc, char* argv[])
{
  double q[6] = {0.8, 0.8, 0.8, 0.8, 0.8, 0.8};
  double T[16];
  forward(q, T);
  for(int i=0;i<4;i++) {
    for(int j=i*4;j<(i+1)*4;j++)
      printf("%1.3f ", T[j]);
    printf("\n");
  }
  double q_sols[8*6];
  int num_sols;
  num_sols = inverse(T, q_sols);
  for(int i=0;i<num_sols;i++)
    printf("%1.6f %1.6f %1.6f %1.6f %1.6f %1.6f\n",
       q_sols[i*6+0], q_sols[i*6+1], q_sols[i*6+2], q_sols[i*6+3], q_sols[i*6+4], q_sols[i*6+5]);
  printf("\n");
  return 0;
}
