/* Copyright (c) 2007-2010 SlimDX Group
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
using System.Runtime.Serialization;
using System.Security.Permissions;

namespace SlimDX {
    /// <summary>
    /// Describes a failure that originated in the SlimDX API.
    /// </summary>
    public class SlimDXException : Exception {
        /// <summary>
        /// Initializes a new instance of the <see cref="SlimDXException"/> class.
        /// </summary>
        SlimDXException()
            : base( "A SlimDX exception occured." ) {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SlimDXException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        SlimDXException( string message )
            : base( message ) {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="SlimDXException"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="innerException">The inner exception.</param>
        SlimDXException( string message, Exception innerException )
            : base( message, innerException ) {
        }

        /// <summary>
        /// When overridden in a derived class, sets the <see cref="T:System.Runtime.Serialization.SerializationInfo"/> with information about the exception.
        /// </summary>
        /// <param name="info">The <see cref="T:System.Runtime.Serialization.SerializationInfo"/> that holds the serialized object data about the exception being thrown.</param>
        /// <param name="context">The <see cref="T:System.Runtime.Serialization.StreamingContext"/> that contains contextual information about the source or destination.</param>
        /// <exception cref="T:System.ArgumentNullException">
        /// The <paramref name="info"/> parameter is a null reference (Nothing in Visual Basic).
        /// </exception>
        /// <PermissionSet>
        /// 	<IPermission class="System.Security.Permissions.FileIOPermission, mscorlib, Version=2.0.3600.0, Culture=neutral, PublicKeyToken=b77a5c561934e089" version="1" Read="*AllFiles*" PathDiscovery="*AllFiles*"/>
        /// 	<IPermission class="System.Security.Permissions.SecurityPermission, mscorlib, Version=2.0.3600.0, Culture=neutral, PublicKeyToken=b77a5c561934e089" version="1" Flags="SerializationFormatter"/>
        /// </PermissionSet>
        [SecurityPermission( SecurityAction.LinkDemand, Flags = SecurityPermissionFlag.SerializationFormatter )]
        public override void GetObjectData( SerializationInfo info, StreamingContext context ) {
            if( info == null ) {
                throw new ArgumentNullException( "info" );
            }
            //info->AddValue("Result", m_Result);

            base.GetObjectData( info, context );
        }
    }
}