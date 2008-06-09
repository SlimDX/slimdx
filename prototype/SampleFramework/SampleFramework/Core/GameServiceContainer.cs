using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SampleFramework
{
    /// <summary>
    /// Provides a container for game services.
    /// </summary>
    public class GameServiceContainer : IServiceProvider
    {
        // variables
        Dictionary<Type, object> services = new Dictionary<Type, object>();

        /// <summary>
        /// Gets the services.
        /// </summary>
        /// <value>The services.</value>
        internal Dictionary<Type, object> Services
        {
            get { return services; }
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="GameServiceContainer"/> class.
        /// </summary>
        public GameServiceContainer()
        {
        }

        /// <summary>
        /// Adds a service to the container.
        /// </summary>
        /// <param name="serviceType">Type of the service.</param>
        /// <param name="provider">The service provider.</param>
        /// <exception cref="ArgumentNullException">
        /// Thrown when <paramref name="serviceType"/> or <paramref name="provider"/> is a null reference.
        /// </exception>
        /// <exception cref="ArgumentException">
        /// Thrown when a service with the same type already
        /// exists in the container, or when the specified provider isn't assignable to the provided type.
        /// </exception>
        public void AddService(Type serviceType, object provider)
        {
            // error checking
            if (serviceType == null)
                throw new ArgumentNullException("serviceType");
            if (provider == null)
                throw new ArgumentNullException("provider");
            if (services.ContainsKey(serviceType))
                throw new ArgumentException("The specified service is already present in the container.", "serviceType");
            if (!serviceType.IsAssignableFrom(provider.GetType()))
                throw new ArgumentException("The provider must be assignable to the provided serviceType.");

            // add the service
            services.Add(serviceType, provider);
        }

        /// <summary>
        /// Gets the service object of the specified type.
        /// </summary>
        /// <param name="serviceType">An object that specifies the type of service object to get.</param>
        /// <returns>
        /// A service object of type <paramref name="serviceType"/>.-or- <c>null</c> if there is no service object of type <paramref name="serviceType"/>.
        /// </returns>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="serviceType"/> is a null reference.</exception>
        public object GetService(Type serviceType)
        {
            // error checking
            if (serviceType == null)
                throw new ArgumentNullException("serviceType");

            // return the service if we have it
            if (services.ContainsKey(serviceType))
                return services[serviceType];

            // otherwise, just return null
            return null;
        }

        /// <summary>
        /// Removes a service from the container.
        /// </summary>
        /// <param name="serviceType">Type of the service.</param>
        /// <exception cref="ArgumentNullException">Thrown when <paramref name="serviceType"/> is a null reference.</exception>
        public void RemoveService(Type serviceType)
        {
            // error checking
            if (serviceType == null)
                throw new ArgumentNullException("serviceType");

            // get the item
            object service = GetService(serviceType);
            if (service == null)
                return;

            // remove the item
            services.Remove(serviceType);
        }
    }
}
