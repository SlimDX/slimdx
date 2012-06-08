using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace SlimDX
{
    /// <summary>
    /// 
    /// </summary>
    public static class ReferenceTracker
    {
        public struct TrackingInformation
        {
            public IntPtr NativePointer { get; set; }
            public Type Type { get; set; }
            public int ReferenceCount { get; set; }

            public override string ToString()
            {
                return string.Format("Reference: [Native Pointer: {0}, Type: {1}, Reference Count: {2}]", NativePointer, Type, ReferenceCount);
            }
        }

        private class TrackerKey
        {
            public IntPtr NativePointer;
            public Type Type;

            public override bool Equals(object obj)
            {
                if (ReferenceEquals(null, obj))
                {
                    return false;
                }
                if (ReferenceEquals(this, obj))
                {
                    return true;
                }
                if (obj.GetType() != typeof(TrackerKey))
                {
                    return false;
                }
                return Equals((TrackerKey)obj);
            }

            public bool Equals(TrackerKey other)
            {
                if (ReferenceEquals(null, other))
                {
                    return false;
                }
                if (ReferenceEquals(this, other))
                {
                    return true;
                }
                return other.NativePointer.Equals(NativePointer) && Equals(other.Type, Type);
            }

            public override int GetHashCode()
            {
                unchecked
                {
                    return (NativePointer.GetHashCode() * 397) ^ (Type != null ? Type.GetHashCode() : 0);
                }
            }
        }

        /// <summary>
        /// When set will register references with the tracker, allowing for extended debugging of unreleased references.
        /// </summary>
        public static bool TrackReferences { get; set; }

        private static readonly Dictionary<TrackerKey, int> References = new Dictionary<TrackerKey, int>();

        internal static void Constructed(IntPtr nativePointer, Type comObjectType)
        {
            lock (References)
            {
                var trackerKey = new TrackerKey { NativePointer = nativePointer, Type = comObjectType };

                if (!References.ContainsKey(trackerKey))
                {
                    References.Add(trackerKey, 0);
                }

                ReferenceIncremented(nativePointer, comObjectType);
            }
        }

        internal static void ReferenceIncremented(IntPtr nativePointer, Type comObjectType)
        {
            lock (References)
            {
                var trackerKey = new TrackerKey { NativePointer = nativePointer, Type = comObjectType };

                if (!References.ContainsKey(trackerKey))
                    throw new InvalidOperationException(string.Format("Attempted reference increment on dead object: {{NativePointer: {0}, Type: {1}}", nativePointer, comObjectType));

                ++References[trackerKey];
            }
        }

        internal static void ReferenceDecremented(IntPtr nativePointer, Type comObjectType)
        {
            lock (References)
            {
                var trackerKey = new TrackerKey { NativePointer = nativePointer, Type = comObjectType };

                if (!References.ContainsKey(trackerKey))
                    throw new InvalidOperationException(string.Format("Attempted reference decrement on dead or non-existant object: {{NativePointer: {0}, Type: {1}}", nativePointer, comObjectType));

                var result = --References[trackerKey];
                if (result == 0)
                    References.Remove(trackerKey);
            }
        }

        /// <summary>
        /// When reference tracking is enabled a list of current references and their reference count is returned.
        /// </summary>
        /// <returns>An enumerable of all current registered references if reference tracking is enabled, otherwise an empty enumerable.</returns>
        public static IEnumerable<TrackingInformation> GetCurrentReferences()
        {
            var trackingInfo = new List<TrackingInformation>(from ti in References select new TrackingInformation {NativePointer = ti.Key.NativePointer, Type = ti.Key.Type, ReferenceCount = ti.Value});
            return trackingInfo;
        }
    }
}
