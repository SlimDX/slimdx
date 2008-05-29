using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using SlimDX;

namespace Interface
{
    /// <summary>
    /// Maintains a collection of user interface dialogs.
    /// </summary>
    public class DialogCollection : Collection<Dialog>
    {
        #region Variables

        // variables
        InterfaceManager parent;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the <see cref="Interface.Dialog"/> with the specified name.
        /// </summary>
        /// <value>The dialog with the specified name.</value>
        public Dialog this[string name]
        {
            get { return Items.FirstOrDefault(d => d.Name == name); }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="DialogCollection"/> class.
        /// </summary>
        /// <param name="parent">The parent manager.</param>
        internal DialogCollection(InterfaceManager parent)
        {
            // store variables
            this.parent = parent;
        }

        #endregion

        #region Methods

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

        #endregion

        #region Event Handlers

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

        #endregion
    }
}
