using System.Data.Common;
using System.Globalization;

namespace Common
{
    public class CSVReader<T>
    {
        public string Path { get; private set; }
        public List<List<string>> Data { get; private set; }
        public List<string> Title { get; private set; }
        public List<List<T>> TData { get; private set; }
        public List<T> TTitle { get; private set; }
        public bool Parsable { get; private set; }
        public int Columns { get => Title.Count; }


        public List<T> this[int row]
        {
            get => TData[row];
            set => TData[row] = value;
        }

        public List<T> Column(string column)
        {
            return TData.Select(x => x[Title.IndexOf(column)]).ToList();
        }

        public List<T> Column(int index)
        {
            return TData.Select(x => x[index]).ToList();
        }

        public CSVReader(string path, bool hasTitle = false)
        {
            if (!File.Exists(path))
                throw new FileNotFoundException(path);

            Path = path;
            List<string> lines = File.ReadAllLines(path).ToList();
            Data = lines.Select(x => x.Split(new string[] { ",", ";" }, StringSplitOptions.None).ToList()).ToList();
            Parsable = true;

            if (hasTitle)
            {
                Title = Data[0];
                Data = Data.GetRange(1, Data.Count - 1);
            }
            else
                Title = new();

            TData = new();
            string nds = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
            try
            {
                if (typeof(T) == typeof(double))
                    Data = Data.Select(x => x.Select(y => y.Replace(".", nds)).ToList()).ToList();
                TData = Data.Select(x => x.Select(y => (T)Convert.ChangeType(y, typeof(T))).ToList()).ToList();
            }
            catch
            {
                Parsable = false;
            }

            TTitle = new();
            try
            {
                if (typeof(T) == typeof(double))
                    Title = Title.Select(x => x.Replace(".", nds)).ToList();
                TTitle = Title.Select(x => (T)Convert.ChangeType(x, typeof(T))).ToList();
            }
            catch
            {

            }

            if (Data.TrueForAll(x => string.IsNullOrEmpty(x.Last())) && string.IsNullOrEmpty(Title.Last()))
            {
                Data = Data.Select(x => x.GetRange(0, x.Count - 1)).ToList();
                TData = TData.Select(x => x.GetRange(0, x.Count - 1)).ToList();
                Title = Title.GetRange(0, Title.Count - 1);
                TTitle = TTitle.GetRange(0, TTitle.Count - 1);
            }
        }
    }
}
