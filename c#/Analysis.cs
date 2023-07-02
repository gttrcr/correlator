using MathNet.Numerics;
using MathNet.Numerics.Statistics;

namespace CorrLib
{
    public class Analysis
    {
        public static Error PolyFit(List<Dataset> functions)
        {
            Console.WriteLine("PolyFit...");

            for (int order = 0; order < Arguments.Get().Args.PolyfitMaxDegree; order++)
            {
                for (int i = 0; i < functions.Count; i++)
                {
                    Function<double> f = functions[i].Function;
                    double[] coefs = Fit.Polynomial(f.Domain.SelectMany(x => x).ToArray(), f.Codomain.ToArray(), order); //remove SelectMany to allow multidimensional case
                    double pearson = Correlation.Pearson(Funct.FromPolyFit(coefs, f.Domain.SelectMany(x => x).ToList()).Domain.SelectMany(x => x), f.Codomain);  //remove SelectMany to allow multidimensional case
                    Result.Get().PolyFits.Add(new PolyFit()
                    {
                        File1 = functions[i].CodomainFileName,
                        Order = order,
                        Pearson = pearson,
                        Coefficients = coefs
                    });
                }
            }

            for (int order = 0; order < Arguments.Get().Args.PolyfitMaxDegree; order++)
            {
                for (int i = 0; i < functions.Count; i++)
                {
                    for (int j = i + 1; j < functions.Count; j++)
                    {
                        Function<double> f = functions[i].Function.Minus(functions.ElementAt(j).Function);
                        double[] coefs = Fit.Polynomial(f.Domain.SelectMany(x => x).ToArray(), f.Codomain.ToArray(), order); //remove SelectMany to allow multidimensional case
                        double pearson = Correlation.Pearson(Funct.FromPolyFit(coefs, f.Domain.SelectMany(x => x).ToList()).Domain.SelectMany(x => x), f.Codomain);  //remove SelectMany to allow multidimensional case
                        Result.Get().PolyFits.Add(new PolyFit()
                        {
                            File1 = functions[i].CodomainFileName,
                            File2 = functions.ElementAt(j).CodomainFileName,
                            Order = order,
                            Pearson = pearson,
                            Coefficients = coefs
                        });
                    }
                }
            }

            Console.WriteLine("Done");

            return Error.Ok;
        }
    }
}