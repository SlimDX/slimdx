#pragma once

#include "../Common/ComObject.h"

namespace SlimDX
{
	namespace Direct3D10
	{
		ref class EffectPass10 : IEffectPass10 {
		public:
			EffectPass10(ID3D10EffectPass* native);
			virtual void Apply();
			virtual EffectPassDescription10 GetDescription();
		private:
			ID3D10EffectPass* native;
		};

		ref class EffectTechnique10 : IEffectTechnique10 {
		public:
			EffectTechnique10(ID3D10EffectTechnique* native);
			virtual IEffectPass10^ GetPassByIndex(int index);
		private:

			System::Collections::Generic::Dictionary<System::IntPtr, EffectPass10^>^ passes;
			ID3D10EffectTechnique* native;
		};

		ref class Effect10 : IEffect10, ComObject<ID3D10Effect> {
		public:
			Effect10( ID3D10Effect* native );
			Effect10( System::IntPtr native );

			virtual IEffectTechnique10^ GetTechniqueByIndex(int index);
		private:
			System::Collections::Generic::Dictionary<System::IntPtr, EffectTechnique10^>^ techniques;
		};
	}
}