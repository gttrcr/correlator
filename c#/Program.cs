namespace CorrLib
{
    public class Program
    {
        // public static int Main(string[] args)
        // {
        //     //Dictionary's Tuple's Item1: common name of the argument (the name that you will use in the code)
        //     //Dictionary's Tuple's Item2: mandatory property (true if it is mandatory, false if it's not)
        //     //Dictionary's Tuple's Item3: default value
        //     Dictionary<string, Tuple<string, bool, object>> dict = new Dictionary<string, Tuple<string, bool, object>>();
        //     dict["-p"] = new Tuple<string, bool, object>("Port", false, 39785);
        //     dict["-i"] = new Tuple<string, bool, object>("Input", false, new List<string>() { "test_csv/1_to_5" });
        //     dict["-o"] = new Tuple<string, bool, object>("Output", false, "out_CorrLib");
        //     dict["-s"] = new Tuple<string, bool, object>("SocketOutput", false, "socket_out_CorrLib");
        //     dict["-f"] = new Tuple<string, bool, object>("NumberOfFFTPeaksToCompute", false, 5);
        //     dict["-d"] = new Tuple<string, bool, object>("DomainSize", false, 1);
        //     dict["-g"] = new Tuple<string, bool, object>("PolyfitMaxDegree", false, 5);
        //     dict["-t"] = new Tuple<string, bool, object>("Terminal", false, false);
        //     Arguments.Get().Set(args, dict);

        //     if (Arguments.Get().Args.Terminal)
        //         return (int)CorrLib.Correlate.Work();

        //     return (int)Error.Ok;
        // }
    }
}