#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class EffectPass : IEffectPass {
		public:
			EffectPass(ID3D10EffectPass* native);
			virtual void Apply();
			virtual EffectPassDescription GetDescription();
		private:
			ID3D10EffectPass* native;
		};

		ref class EffectTechnique : IEffectTechnique {
		public:
			EffectTechnique(ID3D10EffectTechnique* native);
			virtual IEffectPass^ GetPassByIndex(int index);
		private:

			System::Collections::Generic::Dictionary<System::IntPtr, EffectPass^>^ passes;
			ID3D10EffectTechnique* native;
		};

		ref class Effect : IEffect, ComObject<ID3D10Effect> {
		public:
			Effect( ID3D10Effect* native );
			Effect( System::IntPtr native );

			virtual IEffectTechnique^ GetTechniqueByIndex(int index);
		private:
			System::Collections::Generic::Dictionary<System::IntPtr, EffectTechnique^>^ techniques;
		};
	}
}