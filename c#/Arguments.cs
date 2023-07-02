using System.Dynamic;

namespace CorrLib
{
    public class Arguments
    {
        private static Arguments? _instance;

        private Arguments()
        {
            Args = new ExpandoObject();
        }

        public dynamic Args { get; private set; }

        public static Arguments Get()
        {
            if (_instance == null)
                _instance = new Arguments();

            return _instance;
        }

        public void Set(string[] args, Dictionary<string, Tuple<string, bool, object>> argsParameters)
        {
            args = args.Select(x => x.Split(' ')).SelectMany(x => x).Select(x => x.Trim()).ToArray();
            Dictionary<string, List<string>> cmds = new Dictionary<string, List<string>>();
            string parameter = string.Empty;
            for (int i = 0; i < args.Length; i++)
            {
                string line = args[i];
                if (argsParameters.ContainsKey(line))
                {
                    parameter = argsParameters[line].Item1;
                    cmds[parameter] = new List<string>();
                    continue;
                }
                else if (!string.IsNullOrEmpty(parameter))
                    cmds[parameter].Add(line);
            }

            for (int i = 0; i < cmds.Count; i++)
            {
                IDictionary<string, object> underlying = Args;
                underlying.Add(cmds.ElementAt(i).Key, cmds.ElementAt(i).Value);
            }

            IDictionary<string, object> propertyValues = (IDictionary<string, object>)Args;
            for (int i = 0; i < argsParameters.Count; i++)
            {
                if (!propertyValues.ContainsKey(argsParameters.ElementAt(i).Value.Item1))
                {
                    if (argsParameters.ElementAt(i).Value.Item2)
                        throw new ArgumentException("Argument " + argsParameters.ElementAt(i).Key + " is mandatory");
                    else
                        ((IDictionary<string, object>)Args).Add(argsParameters.ElementAt(i).Value.Item1, argsParameters.ElementAt(i).Value.Item3);
                }
            }
        }
    }
}