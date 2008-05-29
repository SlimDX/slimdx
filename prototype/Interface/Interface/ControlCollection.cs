using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace Interface
{
    /// <summary>
    /// Maintains a collection of user interface controls.
    /// </summary>
    public class ControlCollection : Collection<Control>
    {
        #region Variables

        // variables
        Dialog parent;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the <see cref="Interface.Control"/> with the specified name.
        /// </summary>
        /// <value>The control with the specified name.</value>
        public Control this[string name]
        {
            get { return Items.FirstOrDefault(c => c.Name == name); }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="ControlCollection"/> class.
        /// </summary>
        /// <param name="parent">The parent dialog.</param>
        internal ControlCollection(Dialog parent)
        {
            // store variables
            this.parent = parent;
        }

        #endregion

        #region Event Handlers

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

        #endregion
    }
}
