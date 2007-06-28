using System;
using System.Collections;
using SlimDX;
using SlimDX.Direct3D;
using SlimDX.Direct3D9;

namespace Engine
{
	public class EntityManager
	{
		#region Members
		private ArrayList entityList;
		#endregion
		#region Methods
		public EntityManager()
		{
			entityList = new ArrayList();
		}
		public void Add(Entity entity)
		{
			entityList.Add(entity);
		}
		public void Update(Matrix matView, Matrix matProj)
		{
			foreach(Entity entity in entityList)
			{
				entity.Update(matView, matProj);
			}
		}
		public void Render(Device device)
		{
			foreach(Entity entity in entityList)
			{
				entity.Render(device);
			}
		}
		#endregion
	}
}
