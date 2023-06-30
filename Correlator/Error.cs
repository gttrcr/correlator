namespace Correlator
{
    public enum Error
    {
        Ok = 0,
        FileNotFound,
        DifferentLengthOfDomainAndCodomain,
        ParsingData,
        MultidimensionalDatasetInCodomain,
        EmptyFileList,
    }

    public class CorrelatorException : Exception
    {
        public Error Error { get; private set; }

        public CorrelatorException(Error error)
        {
            Error = error;
        }

        public override string Message => Enum.GetName(Error) ?? string.Empty;
    }
}