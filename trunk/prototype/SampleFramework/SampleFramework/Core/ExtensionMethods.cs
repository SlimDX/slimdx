using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Contains various extension methods for use with the sample framework.
    /// </summary>
    public static class ExtensionMethods
    {
        /// <summary>
        /// Finds the best match in the collection.
        /// </summary>
        /// <typeparam name="TSource">The type of the source.</typeparam>
        /// <typeparam name="TRank">The type of the rank.</typeparam>
        /// <param name="source">The source collection.</param>
        /// <param name="func">The ranking function.</param>
        /// <returns>The highest ranked match.</returns>
        public static TSource BestMatch<TSource, TRank>(this IEnumerable<TSource> source, Func<TSource, TRank> func)
        {
            // call the overload
            return BestMatch(source, func, Comparer<TRank>.Default);
        }

        /// <summary>
        /// Finds the best match in the collection.
        /// </summary>
        /// <typeparam name="TSource">The type of the source.</typeparam>
        /// <typeparam name="TRank">The type of the rank.</typeparam>
        /// <param name="source">The source collection.</param>
        /// <param name="func">The ranking function.</param>
        /// <param name="comparer">The comparer.</param>
        /// <returns>The highest ranked match.</returns>
        public static TSource BestMatch<TSource, TRank>(this IEnumerable<TSource> source, Func<TSource, TRank> func, IComparer<TRank> comparer)
        {
            // find the best match
            TRank currentRank = default(TRank);
            TSource result = default(TSource);

            // apply the function to each element
            foreach (TSource item in source)
            {
                // apply the function
                TRank rank = func.Invoke(item);
                if (comparer.Compare(rank, currentRank) > 0)
                {
                    // we found a new best match
                    currentRank = rank;
                    result = item;
                }
            }

            // return the best match
            return result;
        }
    }
}
