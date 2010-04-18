#include "stdafx.h"

#include "Effect10.h"

using namespace System;
using namespace System::Collections::Generic;

namespace SlimDX
{
	namespace Direct3D10
	{
		EffectPass::EffectPass(ID3D10EffectPass* native) : native(native) {
		}

		void EffectPass::Apply() {
			native->Apply(0);
		}

		EffectPassDescription EffectPass::GetDescription() {
			EffectPassDescription result;
			D3D10_PASS_DESC passDesc;
			native->GetDesc(&passDesc);

			result.Name = gcnew System::String(passDesc.Name);
			result.Annotations = passDesc.Annotations;
			result.StencilRef = passDesc.StencilRef;
			result.SampleMask = passDesc.SampleMask;
			result.BlendFactorR = passDesc.BlendFactor[0];
			result.BlendFactorG = passDesc.BlendFactor[1];
			result.BlendFactorB = passDesc.BlendFactor[2];
			result.BlendFactorA = passDesc.BlendFactor[3];

			ShaderSignature signature;
			signature.Signature = IntPtr(passDesc.pIAInputSignature);
			signature.SignatureLength = static_cast<int>( passDesc.IAInputSignatureSize );

			result.ShaderSignature = signature;

			return result;
		}

		EffectTechnique::EffectTechnique(ID3D10EffectTechnique* native) : native(native) {
			passes = gcnew Dictionary<IntPtr, EffectPass^>();
		}

		IEffectPass^ EffectTechnique::GetPassByIndex(int index) {
			ID3D10EffectPass* pass = native->GetPassByIndex(index);
			if(!passes->ContainsKey(IntPtr(pass))) {
				passes->Add(IntPtr(pass), gcnew EffectPass(pass));;
			}

			return passes[IntPtr(pass)];
		}

		Effect::Effect( ID3D10Effect* native ) : ComObject<ID3D10Effect>(native) {
			techniques = gcnew Dictionary<IntPtr, EffectTechnique^>();
		}

		Effect::Effect( System::IntPtr native ) : ComObject<ID3D10Effect>(native) {
			techniques = gcnew Dictionary<IntPtr, EffectTechnique^>();
		}

		IEffectTechnique^ Effect::GetTechniqueByIndex(int index) {
			ID3D10EffectTechnique* technique = NativePointer->GetTechniqueByIndex(index);
			if(!techniques->ContainsKey(IntPtr(technique))) {
				techniques->Add(IntPtr(technique), gcnew EffectTechnique(technique));;
			}

			return techniques[IntPtr(technique)];
		}
	}
}