using MathNet.Numerics;

namespace Correlator
{
    public class Function<T> where T : notnull
    {
        public List<string>? DomainNames { get; private set; }
        public string? CodomainName { get; private set; }
        public List<List<T>> Domain { get; private set; }
        public List<T> Codomain { get; private set; }

        public Function(List<List<T>> domain, List<T> codomain, List<string>? domainNames = null, string? codomainName = null)
        {
            DomainNames = domainNames;
            CodomainName = codomainName;
            if (domain.Count() != codomain.Count())
                throw new Exception("Cannot create a function where domain and codomain has different Count");

            if (domain[0].Count() > 1)
                throw new NotImplementedException();

            Domain = domain;
            Codomain = codomain;
        }

        public int Count()
        {
            return Domain.Count();
        }
    }

    public static class Funct
    {
        public static Function<double> FromPolyFit(double[] coefs, List<double> domain)
        {
            List<List<double>> funcDomain = domain.Select(x => new List<double>() { x }).ToList();
            return new Function<double>(funcDomain, domain.Select(x => Polynomial.Evaluate(x, coefs)).ToList());
        }

        public static Function<double> Minus(this Function<double> a, Function<double> b)
        {
            if (!a.Domain.SelectMany(x => x).SequenceEqual(b.Domain.SelectMany(x => x)))
                throw new Exception("Cannot operate with functions with different domains");

            List<double> codomain = new List<double>();
            for (int i = 0; i < a.Count(); i++)
                codomain.Add(a.Codomain[i] - b.Codomain[i]);

            return new Function<double>(a.Domain, codomain);
        }
    }
}