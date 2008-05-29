using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Interface
{
    /// <summary>
    /// Represents a radio button control.
    /// </summary>
    public class RadioButton : CheckBox
    {
        #region Properties

        /// <summary>
        /// Gets or sets the radio group.
        /// </summary>
        /// <value>The radio group.</value>
        public int Group
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="CheckBox"/> is checked.
        /// </summary>
        /// <value><c>true</c> if checked; otherwise, <c>false</c>.</value>
        public override bool Checked
        {
            get { return base.Checked; }
            set
            {
                // avoid unecessary changes
                if (value == base.Checked)
                    return;

                // update the value
                base.Checked = value;

                // clear any other radio buttons with the same group
                UpdateRadioButtons();
            }
        }

        #endregion

        #region Constructor

        /// <summary>
        /// Initializes a new instance of the <see cref="RadioButton"/> class.
        /// </summary>
        public RadioButton()
        {
            // update the base elements
            DrawingElements[0].TextureRectangle = new Rectangle(54, 54, 27, 27);
            DrawingElements[1].TextureRectangle = new Rectangle(81, 54, 27, 27);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="RadioButton"/> class.
        /// </summary>
        /// <param name="elements">The elements.</param>
        public RadioButton(DrawingElement[] elements)
            : base(elements)
        {
        }

        #endregion

        #region Event Handlers

        /// <summary>
        /// Raises the <see cref="E:Click"/> event.
        /// </summary>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        protected internal override void OnClick(EventArgs e)
        {
            // don't let clicks make the checked state false
            Checked = false;

            // call the base method
            base.OnClick(e);
        }

        #endregion

        #region Helpers

        /// <summary>
        /// Updates the radio buttons.
        /// </summary>
        void UpdateRadioButtons()
        {
            // if we are checked, uncheck all other radio buttons with the same group
            if (Checked && Parent != null)
            {
                // grab the other radio buttons
                IEnumerable<RadioButton> buttons = Parent.Controls.OfType<RadioButton>().Where(r => r.Group == Group && r != this);
                foreach (RadioButton button in buttons)
                    button.Checked = false;
            }
        }

        #endregion
    }
}
