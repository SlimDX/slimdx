using System;
using System.Collections.Generic;
using System.Text;
using SlimDX.Direct3D9;
using SlimDX;

namespace SkinnedMesh
{
    class CustomFrame : Frame
    {
        public Matrix CombinedTransform { get; set; }

        public CustomFrame()
        {
            TransformationMatrix = Matrix.Identity;
            CombinedTransform = Matrix.Identity;
        }
    }

    class CustomMeshContainer : MeshContainer
    {
        public Texture[] Textures { get; set; }
        public Mesh OriginalMesh { get; set; }
        
        public CustomFrame[] BoneMatricesLookup { get; set; }
        public Matrix[] BoneOffsets { get; set; }

        public BoneCombination[] BoneCombinations { get; set; }
        public int Influences { get; set; }
        public int PaletteEntries { get; set; }

        public CustomMeshContainer()
        {
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                foreach (Texture texture in Textures)
                    texture.Dispose();
                OriginalMesh.Dispose();
            }

            base.Dispose(disposing);
        }
    }

    class CustomAllocateHierarchy : DefaultAllocateHierarchy
    {
        const int MaxMatrices = 26;

        public CustomAllocateHierarchy()
        {
        }

        public override Frame CreateFrame(string name)
        {
            return new CustomFrame() { Name = name };
        }

        public override MeshContainer CreateMeshContainer(string name, MeshData meshData, ExtendedMaterial[] materials, EffectInstance[] effectInstances, int[] adjacency, SkinInfo skinInfo)
        {
            CustomMeshContainer meshContainer = new CustomMeshContainer();
            meshContainer.Name = name;
            meshContainer.MeshData = meshData;

            meshContainer.SetAdjacency(adjacency);
            meshContainer.SetEffects(effectInstances);
            meshContainer.SetMaterials(materials);
            meshContainer.Textures = new Texture[materials.Length];

            for (int i = 0; i < materials.Length; i++)
            {
                if (!string.IsNullOrEmpty(materials[i].TextureFileName))
                    meshContainer.Textures[i] = Texture.FromFile(meshData.Mesh.Device, materials[i].TextureFileName);
            }

            meshContainer.SkinInfo = skinInfo;
            meshContainer.OriginalMesh = meshData.Mesh.Clone(meshData.Mesh.Device, meshData.Mesh.CreationOptions, meshData.Mesh.VertexFormat);

            meshContainer.BoneOffsets = new Matrix[skinInfo.BoneCount];
            for (int i = 0; i < skinInfo.BoneCount; i++)
                meshContainer.BoneOffsets[i] = skinInfo.GetBoneOffsetMatrix(i);

            meshContainer.PaletteEntries = Math.Min(MaxMatrices, meshContainer.SkinInfo.BoneCount);

            int influences;
            BoneCombination[] boneCombinations;

            meshContainer.MeshData.Mesh.Dispose();
            meshContainer.MeshData = new MeshData(meshContainer.SkinInfo.ConvertToIndexedBlendedMesh(meshContainer.OriginalMesh, meshContainer.PaletteEntries,
                adjacency, out influences, out boneCombinations));
            meshContainer.Influences = influences;
            meshContainer.BoneCombinations = boneCombinations;

            VertexElement[] elements = meshContainer.MeshData.Mesh.GetDeclaration();
            for (int i = 0; i < elements.Length; i++)
            {
                if (elements[i].Stream == 0xff)
                    break;

                if (elements[i].Usage == DeclarationUsage.BlendIndices && elements[i].UsageIndex == 0)
                    elements[i].Type = DeclarationType.Color;
            }

            meshContainer.MeshData.Mesh.UpdateSemantics(elements);

            return meshContainer;
        }
    }
}
