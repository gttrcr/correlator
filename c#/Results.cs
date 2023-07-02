using Newtonsoft.Json;

namespace CorrLib
{
    public class Result
    {
        private static Result? _instance;

        private Result()
        {
            Functions = new List<Dataset>();
            PolyFits = new List<PolyFit>();
            FFTs = new List<FFT>();
            FFTPeakss = new List<FFTPeaks>();
        }

        public static Result Get()
        {
            if (_instance == null)
                _instance = new Result();

            return _instance;

        }

        public IDictionary<string, object>? Arguments { get => CorrLib.Arguments.Get().Args; }
        public List<Dataset> Functions { get; set; }
        public List<PolyFit> PolyFits { get; set; }
        public List<FFT> FFTs { get; set; }
        public List<FFTPeaks> FFTPeakss { get; set; }

        public void Save()
        {
            string resString = JsonConvert.SerializeObject(this);
            Directory.CreateDirectory(CorrLib.Arguments.Get().Args.Output);
            File.WriteAllText(CorrLib.Arguments.Get().Args.Output + "/results.json", resString);
        }
    }

    public struct Dataset
    {
        public string SourceFileName { get; set; }
        public string CodomainFileName { get; set; }
        public Function<double> Function { get; set; }
    }

    public struct PolyFit
    {
        public string File1 { get; set; }
        public string? File2 { get; set; }
        public int Order { get; set; }
        public double Pearson { get; set; }
        public double[] Coefficients { get; set; }
    }

    public struct FFT
    {
        public string File { get; set; }
        public double[] Complex { get; set; }
        public double[] Immaginary { get; set; }
    }

    public struct FFTPeaks
    {
        public string File { get; set; }
        public Tuple<double, double> Peaks;
    }
}