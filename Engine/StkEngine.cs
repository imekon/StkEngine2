using System.Runtime.InteropServices;

namespace Engine
{
    public static class StkEngine
    {
        [DllImport("StkEngine2.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static void Initialise();
        [DllImport("StkEngine2.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static void Shutdown();
        [DllImport("StkEngine2.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static void Start();
        [DllImport("StkEngine2.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static void Stop();
    }
}