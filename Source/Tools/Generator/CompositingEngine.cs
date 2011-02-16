using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Json;

namespace SlimDX.Generator
{
	enum CompositingFlags
	{
		None,
		Add,
		Remove,
		Replace
	}

	static class CompositingEngine
	{
		public static void Compose(JsonObject baseLayer, JsonObject newLayer)
		{
			// dependencies and references just do a simple add
			ComposeArrays(baseLayer, newLayer, "dependencies");
			ComposeArrays(baseLayer, newLayer, "references");

			ComposeEnumerations(baseLayer, newLayer);
		}

		static void ComposeEnumerations(JsonObject baseLayer, JsonObject newLayer)
		{
			if (!GetItemArrays(ref baseLayer, ref newLayer, "enumerations"))
				return;

			foreach (var item in newLayer)
			{
				var flags = GetFlags(item);
				var oldItem = FindObjectByKey(baseLayer, (string)item["key"]);
				if ((flags == CompositingFlags.Replace || flags == CompositingFlags.Remove) && oldItem != null)
					baseLayer.Remove(oldItem);

				if (flags == CompositingFlags.Add || flags == CompositingFlags.None || flags == CompositingFlags.Replace)
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

		static CompositingFlags GetFlags(JsonObject item)
		{
			if (item.ContainsKey("compositing"))
			{
				switch((string)item["compositing"])
				{
					case "add":
						return CompositingFlags.Add;
					case "remove":
						return CompositingFlags.Remove;
					case "replace":
						return CompositingFlags.Replace;
				}
			}

			return CompositingFlags.None;
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
