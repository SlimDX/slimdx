using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace Interface
{
    /// <summary>
    /// Contains various extension methods for .NET types.
    /// </summary>
    public static class ExtensionMethods
    {
        #region Collection<T> Methods

        /// <summary>
        /// Adds a range of items to the specified collection.
        /// </summary>
        /// <typeparam name="T">The type of the items held by the collection.</typeparam>
        /// <param name="collection">The collection.</param>
        /// <param name="items">The items.</param>
        public static void AddRange<T>(this Collection<T> collection, IEnumerable<T> items)
        {
            // add the items
            foreach (T item in items)
                collection.Add(item);
        }

        #endregion

        #region String Methods

        /// <summary>
        /// Converts a string to an arbitrary object by looking up its type converter.
        /// </summary>
        /// <typeparam name="T">The type of the object to convert to.</typeparam>
        /// <param name="value">The value.</param>
        /// <returns>The converted object.</returns>
        public static T ToObject<T>(this string value)
        {
            // look up the type converter to convert the value
            TypeConverter converter = TypeDescriptor.GetConverter(typeof(T));
            return (T)converter.ConvertFromString(value);
        }

        #endregion
    }
}
