using System;
using System.Collections.Generic;
using System.Text;
using SlimDX;

namespace SampleFramework
{
    public class Quad
    {
        public Quad()
        {
            vertices = new Vector3[]
            {
                new Vector3(-1.0f,-1.0f, 0.0f),
                new Vector3(-1.0f, 1.0f, 0.0f),
                new Vector3( 1.0f,-1.0f, 0.0f),
                new Vector3( 1.0f, 1.0f, 0.0f),
            };

            this.indices = new int[]
            {
                0,
                1,
                2,
                2,
                1,
                3
            };
        }

        Vector3[] vertices;

        public Vector3[] Vertices
        {
            get
            {
                return vertices;
            }
        }

        int[] indices;

        public int[] Indices
        {
            get
            {
                return indices;
            }
        }

        public static int VertexCount
        {
            get
            {
                return 4;
            }
        }

        public static int IndexCount
        {
            get
            {
                return 6;
            }
        }
    }
}
