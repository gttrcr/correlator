namespace Gui
{
    internal static class Program
    {
        [STAThread]
        static void Main()
        {
            //Common.Processing process = new("C:\\home\\gttrcr\\correlator\\Gui\\Gui\\win64\\correlator.exe");
            //process.AddArgument("-i .\\1_to_1\\");
            //process.Invoke();


            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.Run(new MainForm());
        }
    }
}