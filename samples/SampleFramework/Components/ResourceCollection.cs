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
using System.Collections.ObjectModel;

namespace SampleFramework
{
    /// <summary>
    /// Defines a collection of resources.
    /// </summary>
    public sealed class ResourceCollection : Collection<IResource>, IResource
    {
        enum ResourceMethod
        {
            Initialize,
            LoadContent,
            UnloadContent,
            Release
        }

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
            manager = graphicsDeviceManager;

            foreach (IResource resource in Items)
                resource.Initialize(graphicsDeviceManager);

            lastMethod = ResourceMethod.Initialize;
        }

        /// <summary>
        /// Allows the resources to load any short-term graphical content.
        /// </summary>
        public void LoadContent()
        {
            foreach (IResource resource in Items)
                resource.LoadContent();

            lastMethod = ResourceMethod.LoadContent;
        }

        /// <summary>
        /// Allows the resources to unload any short-term graphical content.
        /// </summary>
        public void UnloadContent()
        {
            foreach (IResource resource in Items)
                resource.UnloadContent();

            lastMethod = ResourceMethod.UnloadContent;
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            foreach (IResource resource in Items)
                resource.Dispose();

            lastMethod = ResourceMethod.Release;
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Removes all elements from the <see cref="T:System.Collections.ObjectModel.Collection`1"/>.
        /// </summary>
        protected override void ClearItems()
        {
            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                Dispose();
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                UnloadContent();
                Dispose();
            }

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
            if (Contains(item))
                throw new InvalidOperationException("Cannot add duplicates to the resource collection.");

            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                item.Initialize(manager);
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                item.Initialize(manager);
                item.LoadContent();
            }

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
            IResource item = Items[index];

            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                item.Dispose();
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                item.UnloadContent();
                item.Dispose();
            }

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
            if (Contains(item))
                throw new InvalidOperationException("Cannot add duplicates to the resource collection.");

            if (lastMethod == ResourceMethod.Initialize || lastMethod == ResourceMethod.UnloadContent)
                item.Initialize(manager);
            else if (lastMethod == ResourceMethod.LoadContent)
            {
                item.Initialize(manager);
                item.LoadContent();
            }

            base.SetItem(index, item);
        }
    }
}
