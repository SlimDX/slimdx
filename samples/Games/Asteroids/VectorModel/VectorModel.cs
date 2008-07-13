/*
* Copyright (c) 2007-2008 SlimDX Group
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
using System.ComponentModel;
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
        // constants
        const int MaxInstances = 20;

        // static data
        static Effect effect;
        static VertexDeclaration declaration;
        static Dictionary<string, VectorModel> allModels = new Dictionary<string, VectorModel>();
        static bool resetDone;

        // variables
        GraphicsDeviceManager manager;
        VectorModelVertex[] vertices;
        ushort[] indices;
        BoundingBox bounds;
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        int vertexCount;
        int indexCount;

        // cached drawing information
        Vector4[] instanceData = new Vector4[MaxInstances];
        int instanceCount;

        /// <summary>
        /// Gets the device.
        /// </summary>
        /// <value>The device.</value>
        Device Device
        {
            get { return manager.Direct3D9.Device; }
        }

        /// <summary>
        /// Gets or sets the view matrix.
        /// </summary>
        /// <value>The view matrix.</value>
        public static Matrix ViewMatrix
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the projection matrix.
        /// </summary>
        /// <value>The projection matrix.</value>
        public static Matrix ProjectionMatrix
        {
            get;
            set;
        }

        /// <summary>
        /// Gets the width.
        /// </summary>
        /// <value>The width.</value>
        public float Width
        {
            get { return bounds.Maximum.X - bounds.Minimum.X; }
        }

        /// <summary>
        /// Gets the height.
        /// </summary>
        /// <value>The height.</value>
        public float Height
        {
            get { return bounds.Maximum.Y - bounds.Minimum.Y; }
        }

        /// <summary>
        /// Gets the radius.
        /// </summary>
        /// <value>The radius.</value>
        public float Radius
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="VectorModel"/> class.
        /// </summary>
        private VectorModel()
        {
        }

        /// <summary>
        /// Loads a vector model from file.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <returns>The loaded vector model.</returns>
        public static VectorModel FromFile(string fileName)
        {
            // if we already have one of these models, return that instance instead
            if (allModels.ContainsKey(fileName))
                return allModels[fileName];

            // load the XML document
            VectorModel model = new VectorModel();
            XmlDocument document = new XmlDocument();
            document.Load(fileName);
            LoadXml(document, model);

            // register the model
            allModels.Add(fileName, model);
            return model;
        }

        /// <summary>
        /// Initializes the resource.
        /// </summary>
        /// <param name="graphicsDeviceManager">The graphics Device manager.</param>
        public void Initialize(GraphicsDeviceManager graphicsDeviceManager)
        {
            // store the reference
            manager = graphicsDeviceManager;

            // if the effect hasn't been created yet, do so now
            if (effect == null)
                effect = Effect.FromFile(Device, "Content/Shaders/VectorModel.fx", ShaderFlags.None);
        }

        /// <summary>
        /// Allows the resource to load any short-term graphical content.
        /// </summary>
        public void LoadContent()
        {
            // reset the effect
            if (!resetDone)
                effect.OnResetDevice();
            resetDone = true;

            // if the declaration hasn't been created yet, do so now
            if (declaration == null)
                declaration = manager.Direct3D9.CreateVertexDeclaration(typeof(VectorModelVertex));

            // create the vertex buffer
            vertexBuffer = new VertexBuffer(Device, VectorModelVertex.SizeInBytes * vertices.Length, Usage.WriteOnly, VertexFormat.None, Pool.Default);
            vertexBuffer.Lock(0, 0, LockFlags.None).WriteRange(vertices);
            vertexBuffer.Unlock();

            // create the index buffer
            indexBuffer = new IndexBuffer(Device, sizeof(ushort) * indices.Length, Usage.WriteOnly, Pool.Default, true);
            indexBuffer.Lock(0, 0, LockFlags.None).WriteRange(indices);
            indexBuffer.Unlock();
        }

        /// <summary>
        /// Allows the resource to unload any short-term graphical content.
        /// </summary>
        public void UnloadContent()
        {
            // release the vertex buffer
            if (vertexBuffer != null)
                vertexBuffer.Dispose();
            vertexBuffer = null;

            // release the index buffer
            if (indexBuffer != null)
                indexBuffer.Dispose();
            indexBuffer = null;

            // release the effect
            if (resetDone)
            {
                // notify the effect that the Device is lost
                effect.OnLostDevice();
                resetDone = false;
            }
        }

        /// <summary>
        /// Releases the resource.
        /// </summary>
        public void Release()
        {
            // release the declaration
            if (declaration != null)
                declaration.Dispose();
            declaration = null;

            // release the effect
            if (effect != null)
                effect.Dispose();
            effect = null;
        }

        /// <summary>
        /// Draws the model.
        /// </summary>
        /// <param name="position">The position of the model.</param>
        /// <param name="rotation">The rotation of the model.</param>
        /// <param name="alpha">The alpha of the model.</param>
        public void Draw(Vector2 position, float rotation, float alpha)
        {
            // we should only render once we hit the maximum number of instances we can draw
            instanceData[instanceCount++] = new Vector4(position, rotation, alpha);
            if (instanceCount == MaxInstances)
                Flush();
        }

        /// <summary>
        /// Flushes the cached data waiting to be rendered.
        /// </summary>
        void Flush()
        {
            // make sure we have something to draw
            if (instanceCount == 0)
                return;

            // set up the Device for rendering
            Device.VertexDeclaration = declaration;
            Device.SetStreamSource(0, vertexBuffer, 0, VectorModelVertex.SizeInBytes);
            Device.Indices = indexBuffer;

            // set the effect parameters
            effect.SetValue("InstanceData", instanceData);
            effect.SetValue("ViewMatrix", ViewMatrix);
            effect.SetValue("ProjectionMatrix", ProjectionMatrix);

            // start the effect
            effect.Technique = "VectorModelTechnique";
            effect.Begin();
            effect.BeginPass(0);

            // draw the model
            Device.DrawIndexedPrimitives(PrimitiveType.TriangleList, 0, 0, vertexCount * instanceCount, 0, indexCount * instanceCount / 3);

            // end the effect
            effect.EndPass();
            effect.End();

            // no more data to draw
            instanceCount = 0;
        }

        /// <summary>
        /// Flushes all active models.
        /// </summary>
        public static void FlushAll()
        {
            // flush every model
            foreach (VectorModel model in allModels.Values)
                model.Flush();
        }

        /// <summary>
        /// Loads model vertices from an XML document.
        /// </summary>
        /// <param name="document">The document.</param>
        /// <param name="model">The model.</param>
        static void LoadXml(XmlDocument document, VectorModel model)
        {
            // ensure that we have the proper root node
            XmlNode rootNode = document["VectorModel"];
            if (rootNode == null)
                throw new InvalidDataException("Not a valid vector model file.");

            // store the extents of the model to construct a bounding box
            float minX = float.MaxValue;
            float minY = float.MaxValue;
            float maxX = float.MinValue;
            float maxY = float.MinValue;

            // process each polygon node
            var polygons = MakeList(new { Color = new Color4(Color.White), LineWidth = 1.0f, Vertices = new List<Vector2>() });
            foreach (XmlNode polygonNode in rootNode)
            {
                // ensure that we have a polygon node
                if (polygonNode.Name != "Polygon")
                    continue;

                // load the fill color, if any
                Color4 color = Color.White;
                XmlAttribute colorAttribute = polygonNode.Attributes["Color"];
                if (colorAttribute != null)
                    color = Parse<Color4>(colorAttribute.Value);

                // load the line width color, if any
                float lineWidth = 1.0f;
                XmlAttribute lineAttribute = polygonNode.Attributes["LineWidth"];
                if (lineAttribute != null)
                    lineWidth = Parse<float>(lineAttribute.Value);

                // load each vertex
                List<Vector2> verts = new List<Vector2>();
                foreach (XmlNode vertexNode in polygonNode)
                {
                    // make sure we have a vertex node
                    if (vertexNode.Name != "Vertex")
                        continue;

                    // load the position
                    Vector2 position = Parse<Vector2>(vertexNode.InnerText);
                    verts.Add(position);

                    // update the extents of the model
                    minX = Math.Min(minX, position.X);
                    minY = Math.Min(minY, position.Y);
                    maxX = Math.Max(maxX, position.X);
                    maxY = Math.Max(maxY, position.Y);
                }

                // add the polygon to the list
                polygons.Add(new { Color = color, LineWidth = lineWidth, Vertices = verts });
            }

            // remap the vertices
            VertexRemapper remapper = new VertexRemapper();
            List<ushort> tempIndices = new List<ushort>();

            // process each polygon
            foreach (var polygon in polygons)
            {
                // process each vertex
                for (int i = 0; i < polygon.Vertices.Count; i++)
                {
                    // grab this vertex and the next vertex as well
                    Vector2 v0 = polygon.Vertices[i];
                    Vector2 v1 = polygon.Vertices[(i + 1) % polygon.Vertices.Count];

                    // calculate the normal of the vertex
                    float halfWidth = polygon.LineWidth * 0.5f;
                    Vector2 tangent = v1 - v0;
                    Vector2 normal = Vector2.Normalize(new Vector2(-tangent.Y, tangent.X)) * halfWidth;

                    // create the four vertices necessary to make up the edge polygon
                    VectorModelVertex[] vs = new VectorModelVertex[4] {
                        new VectorModelVertex(v0 - normal, (int)polygon.Color),
                        new VectorModelVertex(v0 + normal, (int)polygon.Color),
                        new VectorModelVertex(v1 + normal, (int)polygon.Color),
                        new VectorModelVertex(v1 - normal, (int)polygon.Color) };

                    // add the correct indices to the list
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

            // process each instance
            int currentVertex = 0;
            int currentIndex = 0;
            for (int i = 0; i < MaxInstances; i++)
            {
                // calculate the current offset into the vertex array
                int baseVertex = model.vertexCount * i;

                // write the vertices
                foreach (VectorModelVertex vertex in remapper.Vertices)
                {
                    // write the current vertex
                    model.vertices[currentVertex] = vertex;
                    model.vertices[currentVertex].Padding = (float)i;
                    currentVertex++;
                }

                // write the indices
                foreach (ushort index in tempIndices)
                    model.indices[currentIndex++] = (ushort)(index + baseVertex);
            }

            // store the extents of the model
            float radius = Math.Max(Math.Max(Math.Abs(maxX), Math.Abs(maxY)), Math.Max(Math.Abs(minX), Math.Abs(minY)));
            model.bounds = new BoundingBox(new Vector3(minX, minY, 0.0f), new Vector3(maxX, maxY, 0.0f));
            model.Radius = radius;
        }

        /// <summary>
        /// Makes a generic list based upong the specified type.
        /// </summary>
        /// <typeparam name="T">The type of the data contained in the list.</typeparam>
        /// <param name="type">The data type.</param>
        /// <returns>The newly created list.</returns>
        static List<T> MakeList<T>(T type)
        {
            // create the list
            return new List<T>();
        }

        /// <summary>
        /// Parses an object using its registered type converter.
        /// </summary>
        /// <typeparam name="T">The type of the object.</typeparam>
        /// <param name="value">The object value.</param>
        /// <returns>The new object.</returns>
        static T Parse<T>(string value)
        {
            // look up the type converter to convert the value
            TypeConverter converter = TypeDescriptor.GetConverter(typeof(T));
            return (T)converter.ConvertFromString(value);
        }
    }
}
