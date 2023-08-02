using System.Diagnostics;

namespace Common
{
    public class Processing
    {
        public Dictionary<PlatformID, string> ProcessNamePlatform { get; private set; }
        public List<string?> Arguments { get; private set; }
        public Result Res { get; private set; }

        public Processing()
        {
            Arguments = new();
            ProcessNamePlatform = new();
        }

        public Processing(string processName)
        {
            Arguments = new();
            ProcessNamePlatform = new() { { Environment.OSVersion.Platform, processName } };
        }

        public void AddArgument(string? arg = null)
        {
            Arguments.Add(arg);
        }

        public void AddProcessByPlatform(PlatformID platformID, string processName)
        {
            ProcessNamePlatform.Add(platformID, processName);
        }

        public void AddArgument(string arg, object? value)
        {
            string? val;
            if (value is List<string> listValue)
                val = string.Join(' ', listValue);
            else
                val = value?.ToString();
            AddArgument(arg + " " + val);
        }

        public struct Result
        {
            public List<string>? Output { get; private set; }
            public List<string>? Error { get; private set; }

            public Result(string? output, string? error)
            {
                Output = output?.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();
                Error = error?.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries).ToList();
            }
        }

        public bool Invoke(string? args = null)
        {
            Process p = new();
            p.StartInfo.FileName = ProcessNamePlatform[Environment.OSVersion.Platform];
            p.StartInfo.Arguments = args;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.StartInfo.CreateNoWindow = false;
            p.Start();

            p.WaitForExit();
            Res = new Result(p.StandardOutput.ReadToEnd(), p.StandardError.ReadToEnd());

            return Res.Error?.Count == 0;
        }

        public bool Invoke()
        {
            return Invoke(string.Join(" ", Arguments));
        }
    }
}
