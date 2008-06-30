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
using System.Collections.ObjectModel;
using SlimDX;

namespace SampleFramework
{
    /// <summary>
    /// Maintains a collection of user interface dialogs.
    /// </summary>
    public class DialogCollection : Collection<Dialog>
    {
        // variables
        InterfaceManager parent;

        /// <summary>
        /// Gets the <see cref="Dialog"/> with the specified name.
        /// </summary>
        /// <value>The dialog with the specified name.</value>
        public Dialog this[string name]
        {
            get
            {
                // find the dialog with the matching name
                foreach (Dialog dialog in Items)
                    if (dialog.Name == name)
                        return dialog;

                // otherwise, no match found
                return null;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DialogCollection"/> class.
        /// </summary>
        /// <param name="parent">The parent manager.</param>
        internal DialogCollection(InterfaceManager parent)
        {
            // store variables
            this.parent = parent;
        }

        /// <summary>
        /// Adds a default dialog to the collection.
        /// </summary>
        /// <returns>The created dialog.</returns>
        public Dialog Add()
        {
            // create the dialog
            Dialog dialog = new Dialog(parent);
            Add(dialog);
            return dialog;
        }

        /// <summary>
        /// Adds a new dialog to the collection.
        /// </summary>
        /// <param name="name">The name of the dialog.</param>
        /// <returns>The created dialog.</returns>
        public Dialog Add(string name)
        {
            // create the dialog
            Dialog dialog = new Dialog(parent) { Name = name };
            Add(dialog);
            return dialog;
        }

        /// <summary>
        /// Adds a new dialog to the collection.
        /// </summary>
        /// <param name="name">The name of the dialog.</param>
        /// <param name="topLeftColor">Color of the top left corner.</param>
        /// <param name="topRightColor">Color of the top right corner.</param>
        /// <param name="bottomLeftColor">Color of the bottom left corner.</param>
        /// <param name="bottomRightColor">Color of the bottom right corner.</param>
        /// <returns>The created dialog.</returns>
        public Dialog Add(string name, Color4 topLeftColor, Color4 topRightColor, Color4 bottomLeftColor, Color4 bottomRightColor)
        {
            // create the dialog
            Dialog dialog = new Dialog(parent) { Name = name, TopLeftColor = topLeftColor, TopRightColor = topRightColor, BottomLeftColor = bottomLeftColor, BottomRightColor = bottomRightColor };
            Add(dialog);
            return dialog;
        }

        /// <summary>
        /// Inserts an element into the <see cref="T:System.Collections.ObjectModel.Collection`1"/> at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item"/> should be inserted.</param>
        /// <param name="item">The object to insert. The value can be null for reference types.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void InsertItem(int index, Dialog item)
        {
            // call the base method
            base.InsertItem(index, item);

            // make sure the parent is set properly
            item.Parent = parent;
        }

        /// <summary>
        /// Replaces the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to replace.</param>
        /// <param name="item">The new value for the element at the specified index. The value can be null for reference types.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void SetItem(int index, Dialog item)
        {
            // call the base method
            base.SetItem(index, item);

            // make sure the parent is set properly
            item.Parent = parent;
        }
    }
}
