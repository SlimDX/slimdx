using System;

namespace SlimDX {
    public class InterfaceIDAttribute : Attribute {
        #region Public Interface

        /// <summary>
        /// Initializes a new instance of the <see cref="InterfaceIDAttribute"/> class.
        /// </summary>
        /// <param name="iid">The interface ID.</param>
        public InterfaceIDAttribute( string iid ) {
            // We don't want to allow exceptions to propagate out of 
            // attribute constructors.
            try {
                interfaceID = new Guid( iid );
            } catch {
                interfaceID = Guid.Empty;
            }
        }

        /// <summary>
        /// Gets the value of the interface ID attribute.
        /// </summary>
        public Guid Value {
            get {
                return interfaceID;
            }
        }

        #endregion
        #region Implementation

        Guid interfaceID;

        #endregion
    }
}