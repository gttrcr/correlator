using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Gui
{
    partial class CppCallTestCaller
    {
        private const string libraries = "cppcalltest.dll";
        
        [LibraryImport(libraries)]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(CallConvStdcall) })]
        public static partial int computePolyFit(int a);

        [LibraryImport(libraries)]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(CallConvStdcall) })]
        public static partial int inputString(IntPtr stringArray);

        [LibraryImport(libraries)]
        [UnmanagedCallConv(CallConvs = new Type[] { typeof(CallConvStdcall) })]
        public static partial int ping();
    }
}