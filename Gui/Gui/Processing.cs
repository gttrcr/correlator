using System.Diagnostics;

namespace Common
{
    class Processing
    {
        public delegate void ProcessingDelegate(object? obj, EventArgs e);
        public ProcessingDelegate? ProcessingCallback;

        public string ProcessName { get; private set; }
        public List<string?> Arguments { get; private set; }
        public Result Res { get; private set; }

        public Processing(string processName)
        {
            Arguments = new();
            ProcessName = processName;
        }

        public void AddArgument(string? arg = null)
        {
            Arguments.Add(arg);
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
                Output = output?.Split(new string[] { Environment.NewLine }, StringSplitOptions.None).ToList();
                Error = error?.Split(new string[] { Environment.NewLine }, StringSplitOptions.None).ToList();
            }
        }

        public void Invoke(string? args = null)
        {
            Process p = new();
            p.StartInfo.FileName = ProcessName;
            p.StartInfo.Arguments = args;
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.RedirectStandardError = true;
            p.StartInfo.CreateNoWindow = false;
            p.Start();

            if (ProcessingCallback != null)
            {
                p.Exited += (object? obj, EventArgs e) =>
                {
                    Process? p = (Process?)obj;
                    Res = new Result(p?.StandardOutput.ReadToEnd(), p?.StandardError.ReadToEnd());
                    ProcessingCallback.Invoke(obj, e);
                };
                p.WaitForExitAsync();
            }
            else
            {
                p.WaitForExit();
                Res = new Result(p.StandardOutput.ReadToEnd(), p.StandardError.ReadToEnd());
            }
        }

        public void Invoke()
        {
            Invoke(string.Join(" ", Arguments));
        }
    }
}
