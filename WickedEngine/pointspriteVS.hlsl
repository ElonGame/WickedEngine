struct GS_INPUT{
	float4	pos			: SV_POSITION;
	float4  inSizOpMir	: TEXCOORD0;
	//float3	color		: COLOR;
	float	rot			: ROTATION;
	float3 vel			: VELOCITY;
};

GS_INPUT main(float3 inPos : POSITION, float4 inSizOpMir : TEXCOORD0/*, float4 inCol : TEXCOORD2*/, float rot : ROTATION, float3 vel : VELOCITY)
{
	GS_INPUT Out = (GS_INPUT)0;

	Out.pos=float4(inPos,1.0f);
	Out.inSizOpMir=inSizOpMir;
	//Out.color=inCol.xyz;
	//Out.rot=inCol.w;
	Out.rot=rot;
	Out.vel = vel;

	return Out;
}