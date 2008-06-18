using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Interface
{
    /// <summary>
    /// Represents a scroll bar control.
    /// </summary>
    public class ScrollBar : Control
    {
        #region Enums

        /// <summary>
        /// Defines possible arrow states.
        /// </summary>
        enum ArrowState
        {
            /// <summary>
            /// No arrow is down.
            /// </summary>
            Clear,

            /// <summary>
            /// The up arrow was clicked once.
            /// </summary>
            ClickedUp,

            /// <summary>
            /// The down arrow was clicked once.
            /// </summary>
            ClickedDown,

            /// <summary>
            /// The up arrow was held for a sustained period of time.
            /// </summary>
            HeldUp,

            /// <summary>
            /// The down arrow was held for a sustained period of time.
            /// </summary>
            HeldDown
        }

        #endregion

        #region Variables

        // constants
        const int MinimumThumbSize = 8;
        const float ArrowClickDelay = 0.33f;
        const float ArrowClickRepeat = 0.05f;

        // public variables
        int position;
        int pageSize = 1;
        int start;
        int end = 1;

        // generic variables
        bool showThumb = true;
        ArrowState arrowState;
        float arrowElapsed;
        int thumbOffsetY;
        bool drag;
        Point lastMousePosition;

        // bounds
        Rectangle upButtonRect;
        Rectangle downButtonRect;
        Rectangle trackRect;
        Rectangle thumbRect;

        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets the start of the scroll bar range.
        /// </summary>
        /// <value>The start of the scroll bar range.</value>
        public int Start
        {
            get { return start; }
            set
            {
                // update the range
                start = value;
                Cap();
                UpdateThumbRect();
            }
        }

        /// <summary>
        /// Gets or sets the end of the scroll bar range.
        /// </summary>
        /// <value>The end of the scroll bar range.</value>
        public int End
        {
            get { return end; }
            set
            {
                // update the range
                end = value;
                Cap();
                UpdateThumbRect();
            }
        }

        /// <summary>
        /// Gets or sets the position.
        /// </summary>
        /// <value>The position.</value>
        public int Position
        {
            get { return position; }
            set
            {
                // update the position
                position = value;
                Cap();
                UpdateThumbRect();
            }
        }

        /// <summary>
        /// Gets or sets the size of the page.
        /// </summary>
        /// <value>The size of the page.</value>
        public int PageSize
        {
            get { return pageSize; }
            set
            {
                // update the page size
                pageSize = value;
                Cap();
                UpdateThumbRect();
            }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="ScrollBar"/> class.
        /// </summary>
        public ScrollBar()
        {
            // set default values
            Width = 22;
            Height = 100;

            // create the track element
            DrawingElement track = new DrawingElement();
            track.TextureRectangle = new Rectangle(196, 212, 22, 11);
            track.TextureColor.States[(int)ControlState.Disabled] = Color.FromArgb(255, 200, 200, 200);

            // create the up arrow element
            DrawingElement up = new DrawingElement();
            up.TextureRectangle = new Rectangle(196, 192, 22, 20);
            up.TextureColor.States[(int)ControlState.Disabled] = Color.FromArgb(255, 200, 200, 200);

            // create the down arrow element
            DrawingElement down = new DrawingElement();
            down.TextureRectangle = new Rectangle(196, 223, 22, 21);
            down.TextureColor.States[(int)ControlState.Disabled] = Color.FromArgb(255, 200, 200, 200);

            // create the button element
            DrawingElement button = new DrawingElement();
            button.TextureRectangle = new Rectangle(200, 192, 18, 42);

            // add the elements
            DrawingElements.Add(track);
            DrawingElements.Add(up);
            DrawingElements.Add(down);
            DrawingElements.Add(button);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ScrollBar"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public ScrollBar(DrawingElement[] elements)
        {
            // set default values
            Width = 22;
            Height = 100;

            // add the elements
            DrawingElements.AddRange(elements);
        }

        #endregion

        #region Methods

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

            // check if the button has been held down for a while
            // if so, update thumb position to simulate repeated scroll
            if (arrowState != ArrowState.Clear)
            {
                // update the elapsed time
                arrowElapsed += elapsedTime;
                if (upButtonRect.Contains(lastMousePosition))
                {
                    // check the arrow state
                    if (arrowState == ArrowState.ClickedUp && ArrowClickDelay < arrowElapsed)
                    {
                        // update the state
                        Position -= 1;
                        arrowState = ArrowState.HeldUp;
                        elapsedTime = 0.0f;
                    }
                    else if (arrowState == ArrowState.HeldUp && ArrowClickRepeat < arrowElapsed)
                    {
                        // update the state
                        Position -= 1;
                        elapsedTime = 0.0f;
                    }
                }
                else if (downButtonRect.Contains(lastMousePosition))
                {
                    // check the arrow state
                    if (arrowState == ArrowState.ClickedDown && ArrowClickDelay < arrowElapsed)
                    {
                        // update the state
                        Position += 1;
                        arrowState = ArrowState.HeldDown;
                        elapsedTime = 0.0f;
                    }
                    else if (arrowState == ArrowState.HeldDown && ArrowClickRepeat < arrowElapsed)
                    {
                        // update the state
                        Position += 1;
                        elapsedTime = 0.0f;
                    }
                }
            }

            // determine the destination state
            ControlState state = ControlState.Normal;
            if (!IsVisible)
                state = ControlState.Hidden;
            else if (!IsEnabled || !showThumb)
                state = ControlState.Disabled;
            else if (IsMouseOver)
                state = ControlState.MouseOver;
            else if (HasFocus)
                state = ControlState.Focus;

            // figure out the rate
            float rate = 0.8f;

            // blend the texture colors
            DrawingElements[0].TextureColor.Blend(state, elapsedTime, rate);
            DrawingElements[1].TextureColor.Blend(state, elapsedTime, rate);
            DrawingElements[2].TextureColor.Blend(state, elapsedTime, rate);
            DrawingElements[3].TextureColor.Blend(state, elapsedTime, rate);
        }

        /// <summary>
        /// Renders the control.
        /// </summary>
        protected internal override void Render()
        {
            // call the base method
            base.Render();

            // render each piece of the control
            Parent.DrawSprite(DrawingElements[0], trackRect);
            Parent.DrawSprite(DrawingElements[1], upButtonRect);
            Parent.DrawSprite(DrawingElements[2], downButtonRect);
            Parent.DrawSprite(DrawingElements[3], thumbRect);
        }

        /// <summary>
        /// Ensures that the specified item is visible in the scroll bar range.
        /// </summary>
        /// <param name="index">The index of the item.</param>
        public void ShowItem(int index)
        {
            // cap the index
            if (index < 0)
                index = 0;
            else if (index >= end)
                index = end - 1;

            // adjust the position
            if (position > index)
                position = index;
            else if (position + pageSize <= index)
                position = index - pageSize + 1;

            // update the bounds
            UpdateThumbRect();
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Raises the <see cref="E:MouseDown"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal override void OnMouseDown(System.Windows.Forms.MouseEventArgs e)
        {
            // call the base method
            base.OnMouseDown(e);

            // only handle the left mouse button
            if (e.Button != System.Windows.Forms.MouseButtons.Left)
                return;

            // check for clicks
            if (upButtonRect.Contains(e.Location))
            {
                // update the position
                if (position > start)
                    position--;

                // update the state
                UpdateThumbRect();
                arrowState = ArrowState.ClickedUp;
                arrowElapsed = 0.0f;
            }
            else if (downButtonRect.Contains(e.Location))
            {
                // update the position
                if (position + pageSize < end)
                    position++;

                // update the state
                UpdateThumbRect();
                arrowState = ArrowState.ClickedDown;
                arrowElapsed = 0.0f;
            }
            else if (thumbRect.Contains(e.Location))
            {
                // we are now dragging
                drag = true;
                thumbOffsetY = e.Y - thumbRect.Top;
            }
            else if (thumbRect.X <= e.X && thumbRect.Right > e.X)
            {
                // check if we should scroll forwards or backwards
                if (thumbRect.Y > e.Y && trackRect.Y <= e.Y)
                    Position -= (pageSize - 1);
                else if (thumbRect.Bottom <= e.Y && trackRect.Bottom > e.Y)
                    Position += (pageSize - 1);
            }
        }

        /// <summary>
        /// Raises the <see cref="E:MouseUp"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal override void OnMouseUp(System.Windows.Forms.MouseEventArgs e)
        {
            // call the base method
            base.OnMouseUp(e);

            // only worry about the left button
            if (e.Button != System.Windows.Forms.MouseButtons.Left)
                return;

            // update the state
            drag = false;
            UpdateThumbRect();
            arrowState = ArrowState.Clear;
        }

        /// <summary>
        /// Raises the <see cref="E:MouseMove"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.Windows.Forms.MouseEventArgs"/> instance containing the event data.</param>
        protected internal override void OnMouseMove(System.Windows.Forms.MouseEventArgs e)
        {
            // call the base method
            base.OnMouseMove(e);

            // store the position
            lastMousePosition = e.Location;

            // only care if we are dragging
            if (!drag)
                return;

            // update the thumb position
            thumbRect.Height += e.Y - thumbOffsetY - thumbRect.Y;
            thumbRect.Y = e.Y - thumbOffsetY;
            if (thumbRect.Y < trackRect.Y)
                thumbRect.Offset(0, trackRect.Y - thumbRect.Y);
            else if (thumbRect.Bottom > trackRect.Bottom)
                thumbRect.Offset(0, trackRect.Bottom - thumbRect.Bottom);

            // compute the first item index
            int maxFirstItem = End - Start - PageSize;
            int maxThumb = trackRect.Height - thumbRect.Height;

            // set the position
            position = Start + (thumbRect.Y - trackRect.Y + maxThumb / (maxFirstItem * 2)) * maxFirstItem / maxThumb;
        }

        #endregion

        #region Helpers

        /// <summary>
        /// Updates the rectangles.
        /// </summary>
        void UpdateRects()
        {
            // make the buttons square
            upButtonRect = new Rectangle(X, Y, Width, Width);
            downButtonRect = new Rectangle(X, Bounds.Bottom - Width, Width, Width);
            trackRect = Rectangle.FromLTRB(upButtonRect.Left, upButtonRect.Bottom, downButtonRect.Right, downButtonRect.Bottom);

            // update the thumb a bit
            thumbRect.X = upButtonRect.X;
            thumbRect.Width = upButtonRect.Width;

            // do a full thumb update
            UpdateThumbRect();
        }

        /// <summary>
        /// Updates the thumb rectangle.
        /// </summary>
        void UpdateThumbRect()
        {
            // check if we have content to scroll
            if (End - Start > PageSize)
            {
                // calculate the thumb's dimensions
                int thumbHeight = Math.Max(trackRect.Height * PageSize / (End - Start), MinimumThumbSize);
                int maxPosition = End - Start - PageSize;

                // adjust the rectangle
                thumbRect.Y = trackRect.Y + (Position - Start) * (trackRect.Height - thumbHeight) / maxPosition;
                thumbRect.Height = thumbHeight;
                showThumb = true;
            }
            else
            {
                // nothing to do
                thumbRect.Height = 0;
                showThumb = false;
            }
        }

        /// <summary>
        /// Caps the position values to the range.
        /// </summary>
        void Cap()
        {
            // cap the value
            if (position < start || end - start <= pageSize)
                position = start;
            else if (position + pageSize > end)
                position = end - pageSize;
        }

        #endregion
    }
}
