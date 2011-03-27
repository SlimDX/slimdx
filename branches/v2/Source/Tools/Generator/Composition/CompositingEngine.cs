using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Json;

namespace SlimDX.Generator
{
	static class CompositingEngine
	{
		public static void Compose(JsonObject baseLayer, JsonObject nextLayer)
		{
			// Top-level scalar properties are always replaced.
			foreach (var key in nextLayer.Keys)
			{
				JsonObject value = nextLayer[key];
				if (value.JsonType != JsonType.Array)
					baseLayer[key] = value;
			}

			ComposeArrays(baseLayer, nextLayer, "dependencies");
			ComposeArrays(baseLayer, nextLayer, "translations");

			ComposeEnumerations(baseLayer, nextLayer);
            ComposeStructures(baseLayer, nextLayer);
            ComposeInterfaces(baseLayer, nextLayer);
            ComposeFunctions(baseLayer, nextLayer);
		}

		static void ComposeEnumerations(JsonObject baseLayer, JsonObject newLayer)
		{
			if (!GetItemArrays(ref baseLayer, ref newLayer, "enumerations"))
				return;

			foreach (var item in newLayer)
			{
				var flags = GetFlags(item);
				var oldItem = FindObjectByKey(baseLayer, (string)item["key"]);
				if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
					baseLayer.Remove(oldItem);

				if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
					baseLayer.Add(item);
			}
		}

        static void ComposeStructures(JsonObject baseLayer, JsonObject newLayer)
        {
            if (!GetItemArrays(ref baseLayer, ref newLayer, "structures"))
                return;

            foreach (var item in newLayer)
            {
                var flags = GetFlags(item);
                var oldItem = FindObjectByKey(baseLayer, (string)item["key"]);
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    baseLayer.Remove(oldItem);

                if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseLayer.Add(item);
            }
        }

        static void ComposeInterfaces(JsonObject baseLayer, JsonObject newLayer)
        {
            if (!GetItemArrays(ref baseLayer, ref newLayer, "interfaces"))
                return;

            foreach (var item in newLayer)
            {
                var flags = GetFlags(item);
                var oldItem = FindObjectByKey(baseLayer, (string)item["key"]);
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    baseLayer.Remove(oldItem);

                if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseLayer.Add(item);
            }
        }

        static void ComposeFunctions(JsonObject baseLayer, JsonObject newLayer)
        {
            if (!GetItemArrays(ref baseLayer, ref newLayer, "functions"))
                return;

            foreach (var item in newLayer)
            {
                var flags = GetFlags(item);
                var oldItem = FindObjectByKey(baseLayer, (string)item["key"]);
                if ((flags == CompositionFlags.Replace || flags == CompositionFlags.Remove || flags == CompositionFlags.None) && oldItem != null)
                    baseLayer.Remove(oldItem);

                if (flags == CompositionFlags.Add || flags == CompositionFlags.None || flags == CompositionFlags.Replace)
                    baseLayer.Add(item);
            }
        }

		static void ComposeArrays(JsonObject baseLayer, JsonObject newLayer, string name)
		{
			if (!GetItemArrays(ref baseLayer, ref newLayer, name))
				return;

			foreach (var item in newLayer)
			{
				if (!baseLayer.Contains(item))
					baseLayer.Add(item);
			}
		}

		#region Helpers

		static bool GetItemArrays(ref JsonObject baseLayer, ref JsonObject newLayer, string name)
		{
			JsonObject newLayerItems;
			if (!newLayer.TryGetValue(name, out newLayerItems))
				return false;

			JsonObject baseLayerItems;
			if (!baseLayer.TryGetValue(name, out baseLayerItems))
			{
				baseLayerItems = new JsonObject(JsonType.Array);
				baseLayer.Add(name, baseLayerItems);
			}

			baseLayer = baseLayerItems;
			newLayer = newLayerItems;
			return true;
		}

		static CompositionFlags GetFlags(JsonObject item)
		{
			if (item.ContainsKey("compositing"))
			{
				switch ((string)item["compositing"])
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

		static JsonObject FindObjectByKey(JsonObject array, string key)
		{
			foreach (var item in array)
			{
				if (item.ContainsKey("key") && (string)item["key"] == key)
					return item;
			}

			return null;
		}

		#endregion
	}
}
