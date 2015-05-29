#include "body.h"
#include "test.h"

extern BODYTYPE body[BODYMAX];
void TestFill()
{
	body[0].pos[0] = 50000;
	body[0].pos[1] = 0;
	body[0].pos[2] = 0;


	body[1].pos[0] = 0;
	body[1].pos[1] = 50000;
	body[1].pos[2] = 0;

	body[2].pos[0] = 0;
	body[2].pos[1] = 0;
	body[2].pos[2] = 50000;

	body[3].pos[0] = 50001;
	body[3].pos[1] = 0;
	body[3].pos[2] = 0;


}
/*
01.   __device__ float3   
02.bodyBodyInteraction(float4 bi, float4 bj, float3 ai)   
03.{   
04.  float3 r;   
05.  // r_ij  [3 FLOPS]   
06.  r.x = bj.x - bi.x;   
07.  r.y = bj.y - bi.y;   
08.  r.z = bj.z - bi.z;   
09.  // distSqr = dot(r_ij, r_ij) + EPS^2  [6 FLOPS]   
10.   float distSqr = r.x * r.x + r.y * r.y + r.z * r.z + EPS2;   
11.  // invDistCube =1/distSqr^(3/2)  [4 FLOPS (2 mul, 1 sqrt, 1 inv)]   
12.   float distSixth = distSqr * distSqr * distSqr;   
13.  float invDistCube = 1.0f/sqrtf(distSixth);   
14.  // s = m_j * invDistCube [1 FLOP]   
15.   float s = bj.w * invDistCube;   
16.  // a_i =  a_i + s * r_ij [6 FLOPS]   
17.  ai.x += r.x * s;   
18.  ai.y += r.y * s;   
19.  ai.z += r.z * s;   
20.  return ai;   
21.}  

*/