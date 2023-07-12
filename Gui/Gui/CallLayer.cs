using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Gui
{
    static partial class CallLayer
    {
        [LibraryImport("cppcalltest.dll")]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(CallConvStdcall) })]
        public static partial int ComputePolyFit(int a);

        [LibraryImport("cppcalltest.dll")]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(CallConvStdcall) })]
        public static partial int InputString(IntPtr stringArray);
    }
}
