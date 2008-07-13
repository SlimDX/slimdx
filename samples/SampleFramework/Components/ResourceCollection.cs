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
using System.Collections.ObjectModel;

namespace SampleFramework
{
    /// <summary>
    /// Defines a collection of resources.
    /// </summary>
    public class ResourceCollection : Collection<IResource>, IResource
    {
        /// <summary>
        /// Specifies possible resource methods.
        /// </summary>
        enum ResourceMethod
        {
            /// <summary>
            /// The Initialize method.
            /// </summary>
            Initialize,

            /// <summary>
            /// The LoadContent method.
            /// </summary>
            LoadContent,

            /// <summary>
            /// The UnloadContent method.
            /// </summary>
            UnloadContent,

            /// <summary>
            /// The Release method.
            /// </summary>
            Release
        }

        // variables
        GraphicsDeviceManager manager;
        ResourceMethod lastMethod = ResourceMethod.Release;

        /// <summary>
        /// Initializes a new instance of the <see cref="ResourceCollection"/> class.
        /// </summary>
        public ResourceCollection()
        {
        }

        /// <summary>
        /// Initializes the resource collection.
        /// </summary>
        /// <param name="graphicsDeviceManager">The graphics device manager.</param>
        public void Initialize(GraphicsDeviceManager graphicsDeviceManager)
        {
            // store the reference
            manager = graphicsDeviceManager;

            // update the resources
            foreach (IResource resource in Items)
                resource.Initialize(graphicsDeviceManager);

            // set the last method
            lastMethod = ResourceMethod.Initialize;
        }

        /// <summary>
        /// Allows the resources to load any short-term graphical content.
        /// </summary>
        public void LoadContent()
        {
            // update the resources
            foreach (IResource resource in Items)
                resource.LoadContent();

            // set the last method
            lastMethod = ResourceMethod.LoadContent;
        }

        /// <summary>
        /// Allows the resources to unload any short-term graphical content.
        /// </summary>
        public void UnloadContent()
        {
            // update the resources
            foreach (IResource resource in Items)
                resource.UnloadContent();

            // set the last method
            lastMethod = ResourceMethod.UnloadContent;
        }

        /// <summary>
        /// Releases the resources.
        /// </summary>
        public void Release()
        {
            // update the resources
            foreach (IResource resource in Items)
                resource.Release();

            // set the last method
            lastMethod = ResourceMethod.Release;
        }

        /// <summary>
        /// Removes all elements from the <see cref="T:System.Collections.ObjectModel.Collection`1"/>.
        /// </summary>
        protected override void ClearItems()
        {
            // if the items are currently loaded, be sure to unload them
            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                Release();
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                // unload and release
                UnloadContent();
                Release();
            }

            // call the base method
            base.ClearItems();
        }

        /// <summary>
        /// Inserts an element into the <see cref="T:System.Collections.ObjectModel.Collection`1"/> at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item"/> should be inserted.</param>
        /// <param name="item">The object to insert. The value can be null for reference types.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void InsertItem(int index, IResource item)
        {
            // make sure we don't have this resource already
            if (Contains(item))
                throw new InvalidOperationException("Cannot add duplicates to the resource collection.");

            // update the resource as appropriate
            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                item.Initialize(manager);
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                // initialize and load
                item.Initialize(manager);
                item.LoadContent();
            }

            // call the base method
            base.InsertItem(index, item);
        }

        /// <summary>
        /// Removes the element at the specified index of the <see cref="T:System.Collections.ObjectModel.Collection`1"/>.
        /// </summary>
        /// <param name="index">The zero-based index of the element to remove.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is equal to or greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void RemoveItem(int index)
        {
            // grab the item
            IResource item = Items[index];

            // update the resource as appropriate
            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                item.Release();
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                // unload and release
                item.UnloadContent();
                item.Release();
            }

            // call the base method
            base.RemoveItem(index);
        }

        /// <summary>
        /// Replaces the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to replace.</param>
        /// <param name="item">The new value for the element at the specified index. The value can be null for reference types.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void SetItem(int index, IResource item)
        {
            // make sure we don't have this resource already
            if (Contains(item))
                throw new InvalidOperationException("Cannot add duplicates to the resource collection.");

            // update the resource as appropriate
            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                item.Initialize(manager);
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                // initialize and load
                item.Initialize(manager);
                item.LoadContent();
            }

            // call the base method
            base.SetItem(index, item);
        }
    }
}
