namespace SlimDX.Direct3D10 {
    /// <summary>
    /// Indicates how a resource should be bound to the graphics pipeline.
    /// </summary>
    public enum BindFlags : int {
        /// <summary>
        /// 
        /// </summary>
        VertexBuffer = 0x1,
        
        /// <summary>
        /// 
        /// </summary>
        IndexBuffer = 0x2,
        
        /// <summary>
        /// 
        /// </summary>
        ConstantBuffer = 0x4,
        
        /// <summary>
        /// 
        /// </summary>
        ShaderResource = 0x8,
        
        /// <summary>
        /// 
        /// </summary>
        StreamOutput = 0x10,
        
        /// <summary>
        /// 
        /// </summary>
        RenderTarget = 0x20,
        
        /// <summary>
        /// 
        /// </summary>
        DepthStencil = 0x40,
    }
}
