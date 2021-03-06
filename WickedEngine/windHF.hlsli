#ifndef _WIND_HF_
#define _WIND_HF_

#include "globals.hlsli"

inline void affectWind(inout float3 pos, in float weight, float time) {
	float3 wind = sin(time + (pos.x + pos.y + pos.z))*g_xFrame_WindDirection.xyz*0.1*weight;
	pos += wind;
}

#endif // _WIND_HF_
