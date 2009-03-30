/*
* Copyright (c) 2007-2009 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Xml;
using SampleFramework;
using SlimDX;
using SlimDX.Direct3D9;

namespace Asteroids
{
    /// <summary>
    /// Represents an old-school vector style model.
    /// </summary>
    /// <remarks>
    /// The vector model system was originally designed by Trent Polack.
    /// </remarks>
    class VectorModel : IResource
    {
        const int MaxInstances = 20;

        static Effect effect;
        static VertexDeclaration declaration;
        static Dictionary<string, VectorModel> allModels = new Dictionary<string, VectorModel>();
        static bool resetDone;

        GraphicsDeviceManager manager;
        VectorModelVertex[] vertices;
        ushort[] indices;
        BoundingBox bounds;
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        int vertexCount;
        int indexCount;

        Vector4[] instanceData = new Vector4[MaxInstances];
        int instanceCount;

        Device Device
        {
            get { return manager.Direct3D9.Device; }
        }

        public static Matrix ViewMatrix
        {
            get;
            set;
        }

        public static Matrix ProjectionMatrix
        {
            get;
            set;
        }

        public float Width
        {
            get { return bounds.Maximum.X - bounds.Minimum.X; }
        }

        public float Height
        {
            get { return bounds.Maximum.Y - bounds.Minimum.Y; }
        }

        public float Radius
        {
            get;
            private set;
        }

        private VectorModel()
        {
        }

        public static VectorModel FromFile(string fileName)
        {
            // if we already have one of these models, return that instance instead
            if (allModels.ContainsKey(fileName))
                return allModels[fileName];

            VectorModel model = new VectorModel();
            XmlDocument document = new XmlDocument();
            document.Load(fileName);
            LoadXml(document, model);

            allModels.Add(fileName, model);
            return model;
        }

        public void Initialize(GraphicsDeviceManager graphicsDeviceManager)
        {
            manager = graphicsDeviceManager;

            if (effect == null)
                effect = Effect.FromFile(Device, "Content/Shaders/VectorModel.fx", ShaderFlags.None);
        }

        public void LoadContent()
        {
            if (!resetDone)
                effect.OnResetDevice();
            resetDone = true;

            if (declaration == null)
                declaration = manager.Direct3D9.CreateVertexDeclaration(typeof(VectorModelVertex));

            vertexBuffer = new VertexBuffer(Device, VectorModelVertex.SizeInBytes * vertices.Length, Usage.WriteOnly, VertexFormat.None, Pool.Default);
            vertexBuffer.Lock(0, 0, LockFlags.None).WriteRange(vertices);
            vertexBuffer.Unlock();

            indexBuffer = new IndexBuffer(Device, sizeof(ushort) * indices.Length, Usage.WriteOnly, Pool.Default, true);
            indexBuffer.Lock(0, 0, LockFlags.None).WriteRange(indices);
            indexBuffer.Unlock();
        }

        public void UnloadContent()
        {
            if (vertexBuffer != null)
                vertexBuffer.Dispose();
            vertexBuffer = null;

            if (indexBuffer != null)
                indexBuffer.Dispose();
            indexBuffer = null;

            if (resetDone)
            {
                effect.OnLostDevice();
                resetDone = false;
            }
        }

        public void Dispose()
        {
            if (declaration != null)
                declaration.Dispose();
            declaration = null;

            if (effect != null)
                effect.Dispose();
            effect = null;

            GC.SuppressFinalize(this);
        }

        public void Draw(Vector2 position, float rotation, float alpha)
        {
            instanceData[instanceCount++] = new Vector4(position, rotation, alpha);
            if (instanceCount == MaxInstances)
                Flush();
        }

        void Flush()
        {
            if (instanceCount == 0)
                return;

            Device.VertexDeclaration = declaration;
            Device.SetStreamSource(0, vertexBuffer, 0, VectorModelVertex.SizeInBytes);
            Device.Indices = indexBuffer;

            effect.SetValue("InstanceData", instanceData);
            effect.SetValue("ViewMatrix", ViewMatrix);
            effect.SetValue("ProjectionMatrix", ProjectionMatrix);

            effect.Technique = "VectorModelTechnique";
            effect.Begin();
            effect.BeginPass(0);

            Device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, vertexCount * instanceCount, 0, indexCount * instanceCount / 3);

            effect.EndPass();
            effect.End();

            instanceCount = 0;
        }

        public static void FlushAll()
        {
            foreach (VectorModel model in allModels.Values)
                model.Flush();
        }

        static void LoadXml(XmlDocument document, VectorModel model)
        {
            XmlNode rootNode = document["VectorModel"];
            if (rootNode == null)
                throw new InvalidDataException("Not a valid vector model file.");

            float minX = float.MaxValue;
            float minY = float.MaxValue;
            float maxX = float.MinValue;
            float maxY = float.MinValue;

            var polygons = Helpers.MakeList(new { Color = new Color4(Color.White), LineWidth = 1.0f, Vertices = new List<Vector2>() });
            foreach (XmlNode polygonNode in rootNode)
            {
                if (polygonNode.Name != "Polygon")
                    continue;

                Color4 color = Color.White;
                XmlAttribute colorAttribute = polygonNode.Attributes["Color"];
                if (colorAttribute != null)
                    color = Helpers.Parse<Color4>(colorAttribute.Value);

                float lineWidth = 1.0f;
                XmlAttribute lineAttribute = polygonNode.Attributes["LineWidth"];
                if (lineAttribute != null)
                    lineWidth = Helpers.Parse<float>(lineAttribute.Value);

                List<Vector2> verts = new List<Vector2>();
                foreach (XmlNode vertexNode in polygonNode)
                {
                    if (vertexNode.Name != "Vertex")
                        continue;

                    Vector2 position = Helpers.Parse<Vector2>(vertexNode.InnerText);
                    verts.Add(position);

                    minX = Math.Min(minX, position.X);
                    minY = Math.Min(minY, position.Y);
                    maxX = Math.Max(maxX, position.X);
                    maxY = Math.Max(maxY, position.Y);
                }

                polygons.Add(new { Color = color, LineWidth = lineWidth, Vertices = verts });
            }

            VertexRemapper remapper = new VertexRemapper();
            List<ushort> tempIndices = new List<ushort>();

            foreach (var polygon in polygons)
            {
                for (int i = 0; i < polygon.Vertices.Count; i++)
                {
                    Vector2 v0 = polygon.Vertices[i];
                    Vector2 v1 = polygon.Vertices[(i + 1) % polygon.Vertices.Count];

                    float halfWidth = polygon.LineWidth * 0.5f;
                    Vector2 tangent = v1 - v0;
                    Vector2 normal = Vector2.Normalize(new Vector2(-tangent.Y, tangent.X)) * halfWidth;

                    VectorModelVertex[] vs = new VectorModelVertex[4] {
                        new VectorModelVertex(v0 - normal, (int)polygon.Color),
                        new VectorModelVertex(v0 + normal, (int)polygon.Color),
                        new VectorModelVertex(v1 + normal, (int)polygon.Color),
                        new VectorModelVertex(v1 - normal, (int)polygon.Color) };

                    tempIndices.Add(remapper.GetIndex(vs[0]));
                    tempIndices.Add(remapper.GetIndex(vs[1]));
                    tempIndices.Add(remapper.GetIndex(vs[2]));
                    tempIndices.Add(remapper.GetIndex(vs[0]));
                    tempIndices.Add(remapper.GetIndex(vs[2]));
                    tempIndices.Add(remapper.GetIndex(vs[3]));
                }
            }

            // duplicate each vertex and index to allow the vector model draw operation
            // to draw up to MaxInstances number of models at a time
            model.vertexCount = remapper.Vertices.Count;
            model.indexCount = tempIndices.Count;
            model.vertices = new VectorModelVertex[model.vertexCount * MaxInstances];
            model.indices = new ushort[model.indexCount * MaxInstances];

            int currentVertex = 0;
            int currentIndex = 0;
            for (int i = 0; i < MaxInstances; i++)
            {
                int baseVertex = model.vertexCount * i;

                foreach (VectorModelVertex vertex in remapper.Vertices)
                {
                    model.vertices[currentVertex] = vertex;
                    model.vertices[currentVertex].Padding = (float)i;
                    currentVertex++;
                }

                foreach (ushort index in tempIndices)
                    model.indices[currentIndex++] = (ushort)(index + baseVertex);
            }

            float radius = Math.Max(Math.Max(Math.Abs(maxX), Math.Abs(maxY)), Math.Max(Math.Abs(minX), Math.Abs(minY)));
            model.bounds = new BoundingBox(new Vector3(minX, minY, 0.0f), new Vector3(maxX, maxY, 0.0f));
            model.Radius = radius;
        }
    }
}
