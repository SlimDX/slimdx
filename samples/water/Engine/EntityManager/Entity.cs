using System;
using SlimDX;
using SlimDX.Direct3D;
using SlimDX.Direct3D9;
using System.Runtime.InteropServices;

namespace Engine
{
	public abstract class Entity
	{
		#region Members
		protected Effect effect;
		protected Matrix matWorld;
		protected Matrix matView;
		protected Matrix matProj;
		protected Mesh mesh;
		protected Texture texture;
		protected Material material;
		#endregion
		#region Methods
		public Entity(Device device, string meshFilename, string effectFilename)
		{
			//load the mesh
			mesh = Mesh.FromFile(device, meshFilename, MeshFlags.Managed);

			//Vertex elements that describe the new format of the mesh
			VertexElement[] elements = new VertexElement[]
			{
				new VertexElement(0, 0, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Position, 0),
				new VertexElement(0, 12, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Normal, 0),
				new VertexElement(0, 24, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.TextureCoordinate, 0),
				new VertexElement(0, 36, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Tangent, 0),
				new VertexElement(0, 48, DeclarationType.Float3, DeclarationMethod.Default, DeclarationUsage.Binormal, 0),
				VertexElement.VertexDeclarationEnd,
			};
			Mesh tempMesh = mesh.Clone(device, MeshFlags.Managed, elements);
			mesh.Dispose();
			mesh = tempMesh;

			/* Performs tangent frame computations on a mesh. Tangent, binormal, and optionally normal vectors are generated. 
			  * Singularities are handled as required by grouping edges and splitting vertices.
			 */
			mesh.ComputeTangentFrame(TangentOptions.None);

			//load the effect
			effect = Effect.FromFile(device, effectFilename, null, null, ShaderFlags.Debug | ShaderFlags.PartialPrecision, null);
		}
		public abstract void Update(Matrix matView, Matrix matProj);
		public abstract void Render(Device device);
		#endregion
	}
}
