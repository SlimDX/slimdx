using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SlimDX.Direct3D11;

namespace SlimDX.Toolkit
{
    /// <summary>
    /// Lightweight convenience class for creating commonly used state objects.
    /// </summary>
    public class CommonStates : IDisposable
    {
        static SharedResourcePool<Device, CommonStatesImpl> sharedResources = new SharedResourcePool<Device, CommonStatesImpl>();

        class CommonStatesImpl : IDisposable
        {
            Device device;

            public Lazy<BlendState> Opaque;
            public Lazy<BlendState> AlphaBlend;
            public Lazy<BlendState> Additive;
            public Lazy<BlendState> NonPremultiplied;

            public Lazy<DepthStencilState> DepthNone;
            public Lazy<DepthStencilState> DepthDefault;
            public Lazy<DepthStencilState> DepthRead;

            public Lazy<RasterizerState> CullNone;
            public Lazy<RasterizerState> CullClockwise;
            public Lazy<RasterizerState> CullCounterClockwise;
            public Lazy<RasterizerState> Wireframe;

            public Lazy<SamplerState> PointWrap;
            public Lazy<SamplerState> PointClamp;
            public Lazy<SamplerState> LinearWrap;
            public Lazy<SamplerState> LinearClamp;
            public Lazy<SamplerState> AnisotropicWrap;
            public Lazy<SamplerState> AnisotropicClamp;

            public CommonStatesImpl(Device device)
            {
                this.device = device;

                Opaque = new Lazy<BlendState>(() => CreateBlendState(BlendOption.One, BlendOption.Zero));
                AlphaBlend = new Lazy<BlendState>(() => CreateBlendState(BlendOption.One, BlendOption.InverseSourceAlpha));
                Additive = new Lazy<BlendState>(() => CreateBlendState(BlendOption.SourceAlpha, BlendOption.One));
                NonPremultiplied = new Lazy<BlendState>(() => CreateBlendState(BlendOption.SourceAlpha, BlendOption.InverseSourceAlpha));

                DepthNone = new Lazy<DepthStencilState>(() => CreateDepthStencilState(false, false));
                DepthDefault = new Lazy<DepthStencilState>(() => CreateDepthStencilState(true, true));
                DepthRead = new Lazy<DepthStencilState>(() => CreateDepthStencilState(true, false));

                CullNone = new Lazy<RasterizerState>(() => CreateRasterizerState(CullMode.None, FillMode.Solid));
                CullClockwise = new Lazy<RasterizerState>(() => CreateRasterizerState(CullMode.Front, FillMode.Solid));
                CullCounterClockwise = new Lazy<RasterizerState>(() => CreateRasterizerState(CullMode.Back, FillMode.Solid));
                Wireframe = new Lazy<RasterizerState>(() => CreateRasterizerState(CullMode.Back, FillMode.Wireframe));

                PointWrap = new Lazy<SamplerState>(() => CreateSamplerState(Filter.MinMagMipPoint, TextureAddressMode.Wrap));
                PointClamp = new Lazy<SamplerState>(() => CreateSamplerState(Filter.MinMagMipPoint, TextureAddressMode.Clamp));
                LinearWrap = new Lazy<SamplerState>(() => CreateSamplerState(Filter.MinMagMipLinear, TextureAddressMode.Wrap));
                LinearClamp = new Lazy<SamplerState>(() => CreateSamplerState(Filter.MinMagMipLinear, TextureAddressMode.Clamp));
                AnisotropicWrap = new Lazy<SamplerState>(() => CreateSamplerState(Filter.Anisotropic, TextureAddressMode.Wrap));
                AnisotropicClamp = new Lazy<SamplerState>(() => CreateSamplerState(Filter.Anisotropic, TextureAddressMode.Clamp));
            }

            public void Dispose()
            {
                Dispose(ref Opaque);
                Dispose(ref AlphaBlend);
                Dispose(ref Additive);
                Dispose(ref NonPremultiplied);

                Dispose(ref DepthNone);
                Dispose(ref DepthDefault);
                Dispose(ref DepthRead);

                Dispose(ref CullNone);
                Dispose(ref CullClockwise);
                Dispose(ref CullCounterClockwise);
                Dispose(ref Wireframe);

                Dispose(ref PointWrap);
                Dispose(ref PointClamp);
                Dispose(ref LinearWrap);
                Dispose(ref LinearClamp);
                Dispose(ref AnisotropicWrap);
                Dispose(ref AnisotropicClamp);
            }

            void Dispose<T>(ref Lazy<T> state) where T : IDisposable
            {
                if (state != null && state.IsValueCreated)
                {
                    state.Value.Dispose();
                    state = null;
                }
            }

            BlendState CreateBlendState(BlendOption sourceBlend, BlendOption destinationBlend)
            {
                var desc = new BlendStateDescription();
                desc.RenderTargets[0].BlendEnable = (sourceBlend != BlendOption.One) || (destinationBlend != BlendOption.Zero);
                desc.RenderTargets[0].SourceBlend = desc.RenderTargets[0].SourceBlendAlpha = sourceBlend;
                desc.RenderTargets[0].DestinationBlend = desc.RenderTargets[0].DestinationBlendAlpha = destinationBlend;
                desc.RenderTargets[0].BlendOperation = desc.RenderTargets[0].BlendOperationAlpha = BlendOperation.Add;
                desc.RenderTargets[0].RenderTargetWriteMask = ColorWriteMaskFlags.All;

                return BlendState.FromDescription(device, desc);
            }

            DepthStencilState CreateDepthStencilState(bool enable, bool writeEnable)
            {
                return DepthStencilState.FromDescription(device, new DepthStencilStateDescription
                {
                    IsDepthEnabled = enable,
                    DepthWriteMask = writeEnable ? DepthWriteMask.All : DepthWriteMask.Zero,
                    DepthComparison = Comparison.LessEqual
                });
            }

            RasterizerState CreateRasterizerState(CullMode cullMode, FillMode fillMode)
            {
                return RasterizerState.FromDescription(device, new RasterizerStateDescription
                {
                    CullMode = cullMode,
                    FillMode = fillMode,
                    IsDepthClipEnabled = true,
                    IsMultisampleEnabled = true
                });
            }

            SamplerState CreateSamplerState(Filter filter, TextureAddressMode addressMode)
            {
                return SamplerState.FromDescription(device, new SamplerDescription
                {
                    Filter = filter,
                    AddressU = addressMode,
                    AddressV = addressMode,
                    AddressW = addressMode,
                    MaximumLod = float.MaxValue,
                    MaximumAnisotropy = 16,
                    ComparisonFunction = Comparison.Never
                });
            }
        }

        ISharedResource<CommonStatesImpl> resource;
        CommonStatesImpl impl;

        /// <summary>
        /// An opaque blending mode.
        /// </summary>
        public BlendState Opaque { get { return impl.Opaque.Value; } }

        /// <summary>
        /// Alpha blending mode.
        /// </summary>
        public BlendState AlphaBlend { get { return impl.AlphaBlend.Value; } }

        /// <summary>
        /// Additive blending mode.
        /// </summary>
        public BlendState Additive { get { return impl.Additive.Value; } }

        /// <summary>
        /// Specific-alpha blending mode.
        /// </summary>
        public BlendState NonPremultiplied { get { return impl.NonPremultiplied.Value; } }

        /// <summary>
        /// No depth-testing.
        /// </summary>
        public DepthStencilState DepthNone { get { return impl.DepthNone.Value; } }

        /// <summary>
        /// Depth reading and writing.
        /// </summary>
        public DepthStencilState DepthDefault { get { return impl.DepthDefault.Value; } }

        /// <summary>
        /// Depth read but not write.
        /// </summary>
        public DepthStencilState DepthRead { get { return impl.DepthRead.Value; } }

        /// <summary>
        /// No culling.
        /// </summary>
        public RasterizerState CullNone { get { return impl.CullNone.Value; } }

        /// <summary>
        /// Clockwise culling.
        /// </summary>
        public RasterizerState CullClockwise { get { return impl.CullClockwise.Value; } }

        /// <summary>
        /// Counter-clockwise culling.
        /// </summary>
        public RasterizerState CullCounterClockwise { get { return impl.CullCounterClockwise.Value; } }

        /// <summary>
        /// Wireframe rendering.
        /// </summary>
        public RasterizerState Wireframe { get { return impl.Wireframe.Value; } }

        /// <summary>
        /// Point filtering and wrap addressing.
        /// </summary>
        public SamplerState PointWrap { get { return impl.PointWrap.Value; } }

        /// <summary>
        /// Point filtering and clamp addressing.
        /// </summary>
        public SamplerState PointClamp { get { return impl.PointClamp.Value; } }

        /// <summary>
        /// Linear filtering and wrap addressing.
        /// </summary>
        public SamplerState LinearWrap { get { return impl.LinearWrap.Value; } }

        /// <summary>
        /// Linear filtering and clamp addressing.
        /// </summary>
        public SamplerState LinearClamp { get { return impl.LinearClamp.Value; } }

        /// <summary>
        /// Anisotropic filtering and wrap addressing.
        /// </summary>
        public SamplerState AnisotropicWrap { get { return impl.AnisotropicWrap.Value; } }

        /// <summary>
        /// Anisotropic filtering and clamp addressing.
        /// </summary>
        public SamplerState AnisotropicClamp { get { return impl.AnisotropicClamp.Value; } }

        /// <summary>
        /// Initializes a new instance of the <see cref="CommonStates"/> class.
        /// </summary>
        /// <param name="device">The device used to create the state objects.</param>
        public CommonStates(Device device)
        {
            resource = sharedResources.DemandCreate(device, () => new CommonStatesImpl(device));
            impl = resource.Resource;
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            if (resource != null)
            {
                resource.Release();
                resource = null;
            }
        }
    }
}
