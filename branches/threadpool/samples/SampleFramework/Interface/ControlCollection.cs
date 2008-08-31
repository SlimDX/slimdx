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

namespace SampleFramework
{
    /// <summary>
    /// Maintains a collection of user interface controls.
    /// </summary>
    public class ControlCollection : Collection<Control>
    {
        // variables
        Dialog parent;

        /// <summary>
        /// Gets the <see cref="Control"/> with the specified name.
        /// </summary>
        /// <value>The control with the specified name.</value>
        public Control this[string name]
        {
            get
            {
                // find the control with the matching name
                foreach (Control control in Items)
                    if (control.Name == name)
                        return control;

                // otherwise, no match found
                return null;
            }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ControlCollection"/> class.
        /// </summary>
        /// <param name="parent">The parent dialog.</param>
        internal ControlCollection(Dialog parent)
        {
            // store variables
            this.parent = parent;
        }

        /// <summary>
        /// Inserts an element into the <see cref="T:System.Collections.ObjectModel.Collection`1"/> at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index at which <paramref name="item"/> should be inserted.</param>
        /// <param name="item">The object to insert. The value can be null for reference types.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void InsertItem(int index, Control item)
        {
            // call the base method
            base.InsertItem(index, item);

            // make sure the parent is set properly
            item.Parent = parent;

            // make sure the focus property is respected
            if (item.HasFocus && parent.FocusControl != item)
            {
                // clear and update the focus
                parent.ClearFocus();
                parent.FocusControl = item;
            }
        }

        /// <summary>
        /// Replaces the element at the specified index.
        /// </summary>
        /// <param name="index">The zero-based index of the element to replace.</param>
        /// <param name="item">The new value for the element at the specified index. The value can be null for reference types.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void SetItem(int index, Control item)
        {
            // call the base method
            base.SetItem(index, item);

            // make sure the parent is set properly
            item.Parent = parent;

            // make sure the focus property is respected
            if (item.HasFocus && parent.FocusControl != item)
            {
                // clear and update the focus
                parent.ClearFocus();
                parent.FocusControl = item;
            }
        }

        /// <summary>
        /// Removes the element at the specified index of the <see cref="T:System.Collections.ObjectModel.Collection`1"/>.
        /// </summary>
        /// <param name="index">The zero-based index of the element to remove.</param>
        /// <exception cref="T:System.ArgumentOutOfRangeException">
        /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is equal to or greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
        protected override void RemoveItem(int index)
        {
            // the control can no longer have focus
            if (Items[index] == parent.FocusControl)
                parent.ClearFocus();

            // call the base method
            base.RemoveItem(index);
        }

        /// <summary>
        /// Removes all elements from the <see cref="T:System.Collections.ObjectModel.Collection`1"/>.
        /// </summary>
        protected override void ClearItems()
        {
            // clear the focus
            parent.ClearFocus();

            // call the base method
            base.ClearItems();
        }
    }
}
