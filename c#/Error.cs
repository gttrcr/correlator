namespace CorrLib
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

    public class CorrLibException : Exception
    {
        public Error Error { get; private set; }

        public CorrLibException(Error error)
        {
            Error = error;
        }

        public override string Message => Enum.GetName(Error) ?? string.Empty;
    }
}