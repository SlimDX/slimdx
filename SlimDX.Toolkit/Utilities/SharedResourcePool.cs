using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Provides an interface for reference counted shared resources.
    /// Call Dispose to release the individual reference on each resource. When no other references exist,
    /// the resource will be freed.
    /// </summary>
    /// <typeparam name="T">The type of the resource being shared.</typeparam>
    public interface ISharedResource<T> : IDisposable where T : IDisposable
    {
        /// <summary>
        /// The shared resource.
        /// </summary>
        T Resource { get; }
    }

    /// <summary>
    /// Manages a pool of shared resources such that only a single instance of a given resource is created
    /// for each unique key. This avoids duplicate resource creation so that discrete instances can
    /// share resources such as shaders or vertex buffers.
    /// </summary>
    /// <typeparam name="TKey">The type of the key used to map the resources.</typeparam>
    /// <typeparam name="TData">The type of the resource being shared.</typeparam>
    public class SharedResourcePool<TKey, TData> where TData : IDisposable
    {
        class SharedResource : ISharedResource<TData>
        {
            public TData Resource
            {
                get;
                set;
            }

            public TKey Key;
            public int RefCount;
            public SharedResourcePool<TKey, TData> Pool;

            public SharedResource(TKey key, TData data, SharedResourcePool<TKey, TData> pool)
            {
                Key = key;
                Resource = data;
                Pool = pool;
                RefCount = 1;
            }

            public int AddRef()
            {
                return Interlocked.Increment(ref RefCount);
            }

            public void Dispose()
            {
                lock (Pool.syncBlock)
                {
                    RefCount--;
                    if (RefCount < 1)
                    {
                        Pool.map.Remove(Key);
                        Resource.Dispose();
                    }
                }
            }
        }

        Dictionary<TKey, SharedResource> map = new Dictionary<TKey, SharedResource>();
        object syncBlock = new object();

        /// <summary>
        /// Initializes a new instance of the <see cref="SharedResourcePool&lt;TKey, TData&gt;"/> class.
        /// </summary>
        public SharedResourcePool()
        {
        }

        /// <summary>
        /// Creates or retrieves the shared resource data for the given key.
        /// </summary>
        /// <param name="key">The resource key.</param>
        /// <param name="factory">A factory function used to create the resource if none exists in the pool for the given key.</param>
        /// <returns>The created or retrieved resource reference. The user must call Dispose on this reference when done with the resource.</returns>
        public ISharedResource<TData> DemandCreate(TKey key, Func<TData> factory)
        {
            lock (syncBlock)
            {
                SharedResource resource;
                if (map.TryGetValue(key, out resource))
                {
                    if (resource.AddRef() > 1)
                        return resource;

                    map.Remove(key);
                }

                resource = new SharedResource(key, factory(), this);
                map.Add(key, resource);

                return resource;
            }
        }
    }
}
