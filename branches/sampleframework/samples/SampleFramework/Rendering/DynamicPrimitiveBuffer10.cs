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
using System.Runtime.InteropServices;

using D3D = SlimDX.Direct3D10;

namespace SlimDX.SampleFramework {
	/// <summary>
	/// An automatically-resizing buffer of primitive data, implemented using Direct3D10.
	/// </summary>
	public class DynamicPrimitiveBuffer10<T> : IDisposable where T : struct {
		#region Public Interface

		/// <summary>
		/// Initializes a new instance of the <see cref="DynamicPrimitiveBuffer10"/> class.
		/// </summary>
		/// <param name="device">The device.</param>
		/// <param name="topology">The primitive topology.</param>
		public DynamicPrimitiveBuffer10( D3D.Device device, PrimitiveTopology topology ) {
			if( device == null )
				throw new ArgumentNullException( "device" );

			switch( topology ) {
				case PrimitiveTopology.PointList:
					primitiveTopology = D3D.PrimitiveTopology.PointList;
					verticesPerPrimitive = 1;
					break;
				case PrimitiveTopology.LineList:
					primitiveTopology = D3D.PrimitiveTopology.LineList;
					verticesPerPrimitive = 2;
					break;
				case PrimitiveTopology.TriangleList:
					primitiveTopology = D3D.PrimitiveTopology.TriangleList;
					verticesPerPrimitive = 3;
					break;
				default:
					throw new ArgumentException( string.Format( "'{0}' is not a valid primitive topology for a primitive buffer.", topology ), "topology" );
			}

			buffer = CreateBuffer( device, bufferSize );
		}

		/// <summary>
		/// Performs object finalization.
		/// </summary>
		~DynamicPrimitiveBuffer10() {
			Dispose( false );
		}

		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		public void Dispose() {
			Dispose( true );
			GC.SuppressFinalize( this );
		}

		internal D3D.Buffer UnderlyingBuffer {
			get {
				return buffer;
			}
		}

		/// <summary>
		/// Adds a vertex to the buffer.
		/// </summary>
		/// <param name="vertex">The vertex.</param>
		public void Add( T vertex ) {
			vertices.Add( vertex );
			if( vertices.Count > bufferSize ) {
				bufferSize *= 2;
				buffer = CreateBuffer( buffer.Device, bufferSize );
			}

			needsCommit = true;
		}

		/// <summary>
		/// Clears the buffer of all primitive data.
		/// </summary>
		public void Clear() {
			// Note that we do not require a recommit here, since trying to render an
			// empty buffer will just no-op. It doesn't matter what's in the real buffer
			// on the card at this point, so there's no sense in locking it.
			vertices.Clear();
		}

		/// <summary>
		/// Renders the buffer.
		/// </summary>
		public void Render() {
			if( needsCommit ) {
				DataStream data = buffer.Map( D3D.MapMode.WriteDiscard, D3D.MapFlags.None );

				for( int vertexIndex = 0; vertexIndex < vertices.Count; ++vertexIndex ) {
					data.Write( vertices[vertexIndex] );
				}

				buffer.Unmap();
				needsCommit = false;
			}

			if( vertices.Count > 0 ) {
				D3D.Device device = buffer.Device;
				//device.InputAssembler.SetInputLayout( inputLayout );
				device.InputAssembler.SetPrimitiveTopology( primitiveTopology );
				device.InputAssembler.SetVertexBuffers( 0, new D3D.VertexBufferBinding( buffer, vertexSize, 0 ) );
				device.Draw( vertices.Count, 0 );
			}
		}

		#endregion
		#region Implementation Detail

		const int initialSize = 32;

		D3D.PrimitiveTopology primitiveTopology;
		int verticesPerPrimitive;

		D3D.Buffer buffer;
		int bufferSize = initialSize;

		List<T> vertices = new List<T>();

		bool needsCommit = false;

		static int vertexSize = Marshal.SizeOf( typeof( T ) );

		/// <summary>
		/// Disposes of object resources.
		/// </summary>
		/// <param name="disposeManagedResources">If true, managed resources should be
		/// disposed of in addition to unmanaged resources.</param>
		void Dispose( bool disposeManagedResources ) {
			if( disposeManagedResources ) {
				buffer.Dispose();
			}
		}

		/// <summary>
		/// Creates the buffer.
		/// </summary>
		/// <param name="device">The device.</param>
		/// <param name="size">The size (in vertices).</param>
		/// <returns>The created buffer.</returns>
		static D3D.Buffer CreateBuffer( D3D.Device device, int size ) {
			return new D3D.Buffer( device, new D3D.BufferDescription {
				BindFlags = D3D.BindFlags.VertexBuffer,
				CpuAccessFlags = D3D.CpuAccessFlags.Write,
				OptionFlags = D3D.ResourceOptionFlags.None,
				SizeInBytes = size * vertexSize,
				Usage = D3D.ResourceUsage.Dynamic
			} );
		}

		#endregion
	}
}
