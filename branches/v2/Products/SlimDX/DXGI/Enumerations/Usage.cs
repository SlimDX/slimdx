namespace SlimDX.DXGI {
    /// <summary>
    /// 
    /// </summary>
    public enum Usage : int {
        /// <summary>
        /// 
        /// </summary>
        ShaderInput = ( 1 << ( 0 + 4 ) ),
        
        /// <summary>
        /// 
        /// </summary>
        RenderTargetOutput = ( 1 << ( 1 + 4 ) ),
        
        /// <summary>
        /// 
        /// </summary>
        BackBuffer = ( 1 << ( 2 + 4 ) ),
        
        /// <summary>
        /// 
        /// </summary>
        Shared = ( 1 << ( 3 + 4 ) ),
        
        /// <summary>
        /// 
        /// </summary>
        ReadOnly = ( 1 << ( 4 + 4 ) ),
        
        /// <summary>
        /// 
        /// </summary>
        DiscardOnPresent = ( 1 << ( 5 + 4 ) ),
        
        /// <summary>
        /// 
        /// </summary>
        UnorderedAccess = ( 1 << ( 6 + 4 ) ),
    }
}
