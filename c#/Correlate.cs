using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearRegression;

namespace CorrLib
{
    public class Correlate
    {
        private static Error GetFiles(out List<string> files)
        {
            Console.WriteLine("Getting files...");
            files = new List<string>();
            for (int i = 0; i < Arguments.Get().Args.Input.Count; i++)
            {
                string input = Arguments.Get().Args.Input[i];
                if (File.Exists(input))
                    files.Add(input);
                else if (Directory.Exists(input))
                    files.AddRange(Directory.GetFiles(input, "*.csv").ToList());
                else
                    return Error.FileNotFound;
            }

            Console.WriteLine("Found");
            files.ForEach(x => Console.WriteLine(x));

            if (files.Count == 0)
                return Error.EmptyFileList;

            return Error.Ok;
        }

        private static Error ReadFiles(List<string> files, out List<Dataset> functions)
        {
            Console.WriteLine("Reading files...");
            functions = new List<Dataset>();
            for (int i = 0; i < files.Count; i++)
            {
                string file = files[i];
                Console.WriteLine("\tOpening " + file);
                List<List<string>> lines = File.ReadLines(file).Select(x => x.Split(new string[] { ",", ";" }, StringSplitOptions.None).ToList()).ToList();

                //first line could contain name of columns
                int firstGoodLine = lines[0].TrueForAll(x => !double.TryParse(x, out double tmp)) ? 1 : 0;

                if (!lines.GetRange(firstGoodLine, lines.Count - firstGoodLine).TrueForAll(x => x.TrueForAll(y => double.TryParse(y, out double tmp))))
                    return Error.ParsingData;

                List<string> domainNames = new List<string>();
                if (firstGoodLine == 1)
                    domainNames = lines[0].GetRange(0, Arguments.Get().Args.DomainSize);
                else
                    domainNames = Enumerable.Range(0, (int)Arguments.Get().Args.DomainSize).Select(x => "d" + x).ToList();

                List<List<double>> domain = lines.GetRange(firstGoodLine, lines.Count - firstGoodLine).Select(x => x.GetRange(0, (int)Arguments.Get().Args.DomainSize).Select(y => double.Parse(y)).ToList()).ToList();
                int functionInTheSameFile = lines[0].Count - Arguments.Get().Args.DomainSize;
                for (int j = 0; j < functionInTheSameFile; j++)
                {
                    string codomainName = string.Empty;
                    if (firstGoodLine == 1)
                        codomainName = lines[0][Arguments.Get().Args.DomainSize + j];
                    else
                        codomainName = "c" + j;

                    List<double> codomain = lines.GetRange(firstGoodLine, lines.Count - firstGoodLine).Select(x => double.Parse(x[(int)Arguments.Get().Args.DomainSize + j])).ToList();
                    functions.Add(new Dataset()
                    {
                        SourceFileName = file,
                        CodomainFileName = file + "#" + codomainName + Path.GetExtension(file),
                        Function = new Function<double>(domain, codomain, domainNames, codomainName)
                    });

                    Console.WriteLine("\t\tLoaded " + functions.Last().CodomainFileName);
                }
            }

            return Error.Ok;
        }

        private static Error Work(List<Dataset> functions)
        {
            Error err = Analysis.PolyFit(functions);
            if (err != Error.Ok)
                return err;

            return Error.Ok;
        }

        public static Error Work()
        {
            List<string> files = new List<string>();
            Error err = GetFiles(out files);
            if (err != Error.Ok)
                return err;

            List<Dataset> functions = new List<Dataset>();
            err = ReadFiles(files, out functions);
            if (err != Error.Ok)
                return err;

            Result.Get().Functions = functions;

            err = Work(functions);
            if (err != Error.Ok)
                return err;

            Result.Get().Save();
            return Error.Ok;
        }
    }
}