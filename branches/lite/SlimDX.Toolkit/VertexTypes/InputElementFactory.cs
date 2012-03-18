using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using SlimDX.Direct3D11;
using SlimDX.DXGI;
using SlimMath;

namespace SlimDX.Toolkit.VertexTypes
{
    /// <summary>
    /// Defines a factory for creating input layout descriptions for various vertex types.
    /// </summary>
    public static class InputElementFactory
    {
        static Dictionary<Type, InputElement[]> cache = new Dictionary<Type, InputElement[]>();

        /// <summary>
        /// Retrieves an input layout for the given vertex type from the cache, or creates a new one if it cannot be found.
        /// </summary>
        /// <param name="vertexType">Vertex type for which to get a layout.</param>
        /// <returns>An set of elements describing the input layout for the given vertex type.</returns>
        /// <exception cref="ArgumentNullException">Thrown if <paramref name="vertexType"/> is <c>null</c>.</exception>
        /// <exception cref="ArgumentException">Thrown if <paramref name="vertexType"/> does not refer to a value type.</exception>
        /// <exception cref="InvalidOperationException">Thrown if the vertex type does not have any marked fields or if one of the fields uses an unknown data type.</exception>
        public static InputElement[] DemandCreate(Type vertexType)
        {
            InputElement[] elements;
            if (cache.TryGetValue(vertexType, out elements))
                return elements;

            if (vertexType == null)
                throw new ArgumentNullException("vertexType");
            if (!vertexType.IsValueType)
                throw new ArgumentException("Vertex types must be value types.", "vertexType");

            // get all the fields on the type that have the VertexElement attribute applied
            var fields = from f in vertexType.GetFields(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)
                         let a = f.GetCustomAttributes(typeof(VertexElementAttribute), false)
                         where a.Length != 0
                         select new { Field = f, Data = (VertexElementAttribute)a[0] };

            // create the set of input elements for the given fields
            elements = fields.Select(f => CreateElement(vertexType, f.Field, f.Data)).ToArray();
            if (elements.Length == 0)
                throw new InvalidOperationException("Provided vertex type does not have any fields marked with the VertexElement attribute.");

            cache.Add(vertexType, elements);
            return elements;
        }

        static InputElement CreateElement(Type vertexType, FieldInfo field, VertexElementAttribute attribute)
        {
            int offset = Marshal.OffsetOf(vertexType, field.Name).ToInt32();
            var format = attribute.Format;
            if (format == Format.Unknown)
            {
                if (field.FieldType == typeof(Vector2))
                    format = Format.R32G32_Float;
                else if (field.FieldType == typeof(Vector3))
                    format = Format.R32G32B32_Float;
                else if (field.FieldType == typeof(Vector4))
                    format = Format.R32G32B32A32_Float;
                else if (field.FieldType == typeof(Color3))
                    format = Format.R32G32B32_Float;
                else if (field.FieldType == typeof(Color4))
                    format = Format.R32G32B32A32_Float;
                else if (field.FieldType == typeof(float))
                    format = Format.R32_Float;
                else if (field.FieldType == typeof(int))
                    format = Format.R8G8B8A8_UNorm;
                else if (field.FieldType == typeof(uint))
                    format = Format.R32_UInt;
                else if (field.FieldType == typeof(short))
                    format = Format.R16_SInt;
                else if (field.FieldType == typeof(ushort))
                    format = Format.R16_UInt;
                else if (field.FieldType == typeof(byte))
                    format = Format.R8_UInt;
                else if (field.FieldType == typeof(Half2))
                    format = Format.R16G16_Float;
                else if (field.FieldType == typeof(Half4))
                    format = Format.R16G16B16A16_Float;
                else if (field.FieldType == typeof(Half))
                    format = Format.R16_Float;
                else
                    throw new InvalidOperationException(string.Format("Unrecognized type for field '{0}'. Please specify the format explicitly.", field.Name));
            }

            return new InputElement(attribute.Semantic, attribute.SemanticIndex, format, offset, attribute.Slot, attribute.Classification, attribute.InstanceDataStepRate);
        }
    }
}
