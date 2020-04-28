


texture g_BaseTexture;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
};

vector PS_MAIN(float4 _vPosition : POSITION, float2 _vTexUV : TEXCOORD0, float4 _vWinPos : TEXCOORD1) : COLOR0
{


vector vColor = (vector)0.f;

vColor = tex2D(BaseSampler, _vTexUV);

return vColor;

}


technique DefaultTechnique
{

	pass Default
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_MAIN();
	}

}