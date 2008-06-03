using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Collections.ObjectModel;
using SlimDX.Direct3D9;

namespace Interface
{
    #region ListBoxItem

    /// <summary>
    /// Represents a single item in a list box.
    /// </summary>
    public class ListBoxItem
    {
        #region Properties

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        /// <value>The text.</value>
        public string Text
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets application-specific data.
        /// </summary>
        /// <value>The application-specific data.</value>
        public object Tag
        {
            get;
            set;
        }

        /// <summary>
        /// Gets a value indicating whether this <see cref="ListBoxItem"/> is selected.
        /// </summary>
        /// <value><c>true</c> if selected; otherwise, <c>false</c>.</value>
        public bool Selected
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets the active rectangle.
        /// </summary>
        /// <value>The active rectangle.</value>
        public Rectangle ActiveRectangle
        {
            get;
            set;
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="ListBoxItem"/> class.
        /// </summary>
        public ListBoxItem()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ListBoxItem"/> class.
        /// </summary>
        /// <param name="text">The text.</param>
        public ListBoxItem(string text)
        {
            // store values
            Text = text;
        }

        #endregion
    }

    #endregion

    /// <summary>
    /// Represents a generic list box control.
    /// </summary>
    public class ListBox : Control
    {
        #region ObjectCollection

        /// <summary>
        /// Maintains a collection of list box items.
        /// </summary>
        public class ObjectCollection : Collection<ListBoxItem>
        {
            #region Variables

            // variables
            ListBox parent;

            #endregion

            #region Constructor

            /// <summary>
            /// Initializes a new instance of the <see cref="ObjectCollection"/> class.
            /// </summary>
            internal ObjectCollection(ListBox parent)
            {
                // store the parent
                this.parent = parent;
            }

            #endregion

            #region Event Handlers

            /// <summary>
            /// Removes the element at the specified index of the <see cref="T:System.Collections.ObjectModel.Collection`1"/>.
            /// </summary>
            /// <param name="index">The zero-based index of the element to remove.</param>
            /// <exception cref="T:System.ArgumentOutOfRangeException">
            /// 	<paramref name="index"/> is less than zero.-or-<paramref name="index"/> is equal to or greater than <see cref="P:System.Collections.ObjectModel.Collection`1.Count"/>.</exception>
            protected override void RemoveItem(int index)
            {
                // call the base method
                base.RemoveItem(index);

                // update the parent
                parent.OnItemRemoved();
            }

            #endregion
        }

        #endregion

        #region Variables

        // variables
        bool allowMultiselect;
        int selectedIndex = -1;
        int scrollBarWidth = 16;
        Rectangle selectionRectangle;
        Rectangle textRectangle;
        ScrollBar scrollBar;
        Rectangle storedBounds;
        int textHeight;
        bool firstTime = true;

        #endregion

        #region Properties

        /// <summary>
        /// Gets the scroll bar.
        /// </summary>
        /// <value>The scroll bar.</value>
        private ScrollBar ScrollBar
        {
            get
            {
                // ensure that the scroll bar is created
                if (scrollBar == null && Parent != null)
                {
                    // create the scroll bar
                    scrollBar = (ScrollBar)Parent.Parent.CreateControl("ScrollBar", true);
                    scrollBar.Parent = Parent;
                }

                // return the result
                return scrollBar; 
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether the control should allow multiple selections.
        /// </summary>
        /// <value><c>true</c> if the control should allow multiple selections; otherwise, <c>false</c>.</value>
        public bool AllowMultiselect
        {
            get { return allowMultiselect; }
            set
            {
                // avoid unecessary changes
                if (allowMultiselect == value)
                    return;

                // when this is changed, update the state
                allowMultiselect = value;
                if (!allowMultiselect)
                    foreach (ListBoxItem item in Items)
                        item.Selected = false;
            }
        }

        /// <summary>
        /// Gets the items contained by the list box.
        /// </summary>
        /// <value>The contained items.</value>
        public ObjectCollection Items
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets or sets the width of the scroll bar.
        /// </summary>
        /// <value>The width of the scroll bar.</value>
        public int ScrollBarWidth
        {
            get { return scrollBarWidth; }
            set
            {
                // update the value
                scrollBarWidth = value;
                UpdateRects();
            }
        }

        /// <summary>
        /// Gets or sets the border.
        /// </summary>
        /// <value>The border.</value>
        public int Border
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the margin.
        /// </summary>
        /// <value>The margin.</value>
        public int Margin
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the index of the selected item.
        /// </summary>
        /// <value>The index of the selected item.</value>
        public int SelectedIndex
        {
            get { if (AllowMultiselect) return -1; return selectedIndex; }
            set
            {
                // if no items exist, or if we allow multiselect, do nothing
                if (Items.Count == 0 || AllowMultiselect)
                    return;

                // update the value
                int old = selectedIndex;
                selectedIndex = value;

                // perform capping
                if (selectedIndex < 0)
                    selectedIndex = 0;
                if (selectedIndex >= Items.Count)
                    selectedIndex = Items.Count - 1;

                // check if the selection has changed
                if (old != selectedIndex)
                {
                    // update the state
                    Items[old].Selected = false;
                    Items[selectedIndex].Selected = true;
                }
            }
        }

        /// <summary>
        /// Gets or sets the selected item.
        /// </summary>
        /// <value>The selected item.</value>
        public ListBoxItem SelectedItem
        {
            get { return Items[SelectedIndex]; }
            set { SelectedIndex = Items.IndexOf(value); }
        }

        /// <summary>
        /// Gets the selected indices.
        /// </summary>
        /// <value>The selected indices.</value>
        public IEnumerable<int> SelectedIndices
        {
            get
            {
                // only do this for multiselect list boxes
                if (!AllowMultiselect)
                    return null;

                // return the selected items
                return from i in Items
                       where i.Selected
                       select Items.IndexOf(i);
            }
        }

        /// <summary>
        /// Gets the selected items.
        /// </summary>
        /// <value>The selected items.</value>
        public IEnumerable<ListBoxItem> SelectedItems
        {
            get
            {
                // only do this for multiselect list boxes
                if (!AllowMultiselect)
                    return null;

                // return the selected items
                return from i in Items
                       where i.Selected
                       select i;
            }
        }

        /// <summary>
        /// Gets a value indicating whether this instance can have focus.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance can have focus; otherwise, <c>false</c>.
        /// </value>
        public override bool CanHaveFocus
        {
            get { return IsVisible && IsEnabled; }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="ListBox"/> class.
        /// </summary>
        public ListBox()
        {
            // create the collection
            Items = new ObjectCollection(this);

            // set initial values
            SelectedIndex = -1;
            Border = 6;
            Margin = 5;

            // create the main drawing element
            DrawingElement main = new DrawingElement();
            main.TextureRectangle = new Rectangle(13, 123, 228, 37);
            main.FontColor = new BlendColor(Color.FromArgb(255, 0, 0, 0));
            main.TextFormat = DrawTextFormat.Left | DrawTextFormat.Top;

            // create the selection element
            DrawingElement selection = new DrawingElement();
            selection.TextureRectangle = new Rectangle(16, 166, 224, 17);
            selection.TextFormat = DrawTextFormat.Left | DrawTextFormat.Top;

            // add the elements
            DrawingElements.Add(main);
            DrawingElements.Add(selection);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ListBox"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public ListBox(DrawingElement[] elements)
        {
            // create the collection
            Items = new ObjectCollection(this);

            // set initial values
            SelectedIndex = -1;
            Border = 6;
            Margin = 5;

            // add the elements
            DrawingElements.AddRange(elements);
        }

        #endregion

        #region Methods

        /// <summary>
        /// Selects the specified items.
        /// </summary>
        public void SelectItems()
        {
            // TODO
        }

        /// <summary>
        /// Deselects the specified items.
        /// </summary>
        public void DeselectItems()
        {
            // TODO
        }

        /// <summary>
        /// Updates the control.
        /// </summary>
        /// <param name="elapsedTime">The elapsed time.</param>
        protected internal override void Update(float elapsedTime)
        {
            // call the base method
            base.Update(elapsedTime);

            // update the rectangles
            UpdateRects();

            // set the track range for the scroll bar
            ScrollBar.Start = 0;
            ScrollBar.End = Items.Count == 0 ? 1 : Items.Count;

            // blend the colors
            DrawingElements[0].TextureColor.Blend(ControlState.Normal, elapsedTime);
            DrawingElements[0].FontColor.Blend(ControlState.Normal, elapsedTime);
            DrawingElements[1].TextureColor.Blend(ControlState.Normal, elapsedTime);
            DrawingElements[1].FontColor.Blend(ControlState.Normal, elapsedTime);

            // make sure we have items
            if (Items.Count > 0)
            {
                // find out the height of a single line
                CachedFont font = DrawingElements[0].CachedFont ?? Parent.Parent.DefaultFont;
                textHeight = font.Height;

                // update the page size of the scroll bar
                if (firstTime)
                {
                    // only do this for the first update
                    firstTime = false;
                    if (textHeight != 0)
                        ScrollBar.PageSize = textRectangle.Height / textHeight;
                    else
                        ScrollBar.PageSize = textRectangle.Height;
                }
            }

            // update the scroll bar
            ScrollBar.Update(elapsedTime);
        }

        /// <summary>
        /// Renders the control.
        /// </summary>
        protected internal override void Render()
        {
            // call the base method
            base.Render();

            // draw the one sprite
            Parent.DrawSprite(DrawingElements[0], Bounds);

            // render the scroll bar
            ScrollBar.Render();
        }

        #endregion

        #region Helpers

        /// <summary>
        /// Called when an item is removed.
        /// </summary>
        private void OnItemRemoved()
        {
            // check if the selection has been invalidated
            if (SelectedIndex >= Items.Count)
                SelectedIndex = Items.Count - 1;
        }

        /// <summary>
        /// Updates the rectangles.
        /// </summary>
        void UpdateRects()
        {
            // check if we need to update
            if (Bounds == storedBounds)
                return;
            storedBounds = Bounds;

            // create the selection rectangle
            selectionRectangle = Bounds;
            selectionRectangle.Width -= scrollBarWidth;
            selectionRectangle.Inflate(-Border, -Border);

            // create the text rectangle
            textRectangle = selectionRectangle;
            textRectangle.Inflate(-Margin, 0);

            // update the scroll bar rectangles
            ScrollBar.Location = new Point(Bounds.Right - scrollBarWidth, Bounds.Top);
            ScrollBar.Size = new Size(scrollBarWidth, Height);

            // check if we should adjust based upon the font height
            CachedFont font = DrawingElements[0].CachedFont ?? Parent.Parent.DefaultFont;
            if (font != null && font.Height != 0)
            {
                // update the scroll bar
                ScrollBar.PageSize = textRectangle.Height / font.Height;
                if (!AllowMultiselect)
                    ScrollBar.ShowItem(SelectedIndex);
                else
                    ScrollBar.ShowItem(SelectedIndices.First());
            }
        }

        #endregion
    }
}
