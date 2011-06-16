using System.Linq;
using Newtonsoft.Json.Linq;

namespace SlimDX.Generator
{
	static class CompositingEngine
	{
        public static void Compose(JObject baseLayer, JObject nextLayer)
		{
			// Top-level scalar properties are always replaced.
			foreach (var pair in nextLayer)
			{
                if (pair.Value.Type != JTokenType.Array)
					baseLayer[pair.Key] = pair.Value;
			}

			ComposeArrays(baseLayer, nextLayer, "dependencies");
			ComposeArrays(baseLayer, nextLayer, "translations");

			ComposeEnumerations(baseLayer, nextLayer);
            ComposeStructures(baseLayer, nextLayer);
            ComposeInterfaces(baseLayer, nextLayer);
            ComposeFunctions(baseLayer, nextLayer);
		}

		static void ComposeEnumerations(JObject baseLayer, JObject newLayer)
		{
            JArray baseArray;
            JArray newArray;
			if (!GetItemArrays("enumerations", baseLayer, newLayer, out baseArray, out newArray))
				return;

            foreach (var item in newArray)
			{
				var flags = GetFlags(item as JObject);
                var oldItem = FindObjectByKey(baseArray, item.Value<string>("key"));
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    oldItem.Remove();

				if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseArray.Add(item);
			}
		}

        static void ComposeStructures(JObject baseLayer, JObject newLayer)
        {
            JArray baseArray;
            JArray newArray;
            if (!GetItemArrays("structures", baseLayer, newLayer, out baseArray, out newArray))
                return;

            foreach (var item in newArray)
            {
                var flags = GetFlags(item as JObject);
                var oldItem = FindObjectByKey(baseArray, item.Value<string>("key"));
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    oldItem.Remove();

                if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseArray.Add(item);
            }
        }

        static void ComposeInterfaces(JObject baseLayer, JObject newLayer)
        {
            JArray baseArray;
            JArray newArray;
            if (!GetItemArrays("interfaces", baseLayer, newLayer, out baseArray, out newArray))
                return;

            foreach (var item in newArray)
            {
                var flags = GetFlags(item as JObject);
                var oldItem = FindObjectByKey(baseArray, item.Value<string>("key"));
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    oldItem.Remove();

                if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseArray.Add(item);
            }
        }

        static void ComposeFunctions(JObject baseLayer, JObject newLayer)
        {
            JArray baseArray;
            JArray newArray;
            if (!GetItemArrays("functions", baseLayer, newLayer, out baseArray, out newArray))
                return;

            foreach (var item in newArray)
            {
                var flags = GetFlags(item as JObject);
                var oldItem = FindObjectByKey(baseArray, item.Value<string>("key"));
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    oldItem.Remove();

                if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseArray.Add(item);
            }
        }

		static void ComposeArrays(JObject baseLayer, JObject newLayer, string name)
		{
            JArray baseArray;
            JArray newArray;
			if (!GetItemArrays(name, baseLayer, newLayer, out baseArray, out newArray))
				return;

            foreach (var item in newArray)
			{
                if (!baseArray.Contains(item))
                    baseArray.Add(item);
			}
		}

		#region Helpers

        static bool GetItemArrays(string name, JObject baseLayer, JObject newLayer, out JArray baseArray, out JArray newArray)
		{
            baseArray = null;
            newArray = null;

			JToken newLayerItems;
			if (!newLayer.TryGetValue(name, out newLayerItems))
				return false;

            JToken baseLayerItems;
			if (!baseLayer.TryGetValue(name, out baseLayerItems))
			{
				baseLayerItems = new JArray();
				baseLayer.Add(name, baseLayerItems);
			}

            baseArray = baseLayerItems as JArray;
            newArray = newLayerItems as JArray;
			return true;
		}

		static CompositionFlags GetFlags(JObject item)
		{
            JToken compositing;
            if (item.TryGetValue("compositing", out compositing))
            {
                switch (compositing.Value<string>())
                {
                    case "add":
                        return CompositionFlags.Add;
                    case "remove":
                        return CompositionFlags.Remove;
                    case "replace":
                        return CompositionFlags.Replace;
                }
            }

			return CompositionFlags.None;
		}

		static JObject FindObjectByKey(JArray array, string key)
		{
			foreach (var item in array)
			{
                JToken token;
                if ((item as JObject).TryGetValue("key", out token) && token.Value<string>() == key)
                    return item as JObject;
			}

			return null;
		}

		#endregion
	}
}
