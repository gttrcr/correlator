using System.ComponentModel.DataAnnotations;
using System.Globalization;

namespace Common
{
    public class CSVReader<T>
    {
        public string Path { get; private set; }
        public List<List<T>> Data { get; private set; }
        public List<string> Title { get; private set; }
        public List<T> TTitle { get; private set; }
        public List<T> this[int row]
        {
            get => Data[row];
            set => Data[row] = value;
        }
        public List<T> this[string column]
        {
            get => Data.Select(x => x[Title.IndexOf(column)]).ToList();
        }

        public CSVReader(string path, bool hasTitle = false)
        {
            if (!File.Exists(path))
                throw new FileNotFoundException(path);

            Path = path;
            List<string> lines = File.ReadAllLines(path).ToList();
            string nds = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
            //if (nds.Equals(","))
            //    nds = ";";
            List<List<string>> content = lines.Select(x => x.Split(nds).ToList()).ToList();

            if (hasTitle)
            {
                Title = content[0];
                TTitle = Title.Select(x => (T)Convert.ChangeType(x, typeof(T))).ToList();
                Data = content.GetRange(1, content.Count - 1).Select(x => x.Select(y => (T)Convert.ChangeType(y, typeof(T))).ToList()).ToList();
            }
            else
            {
                Title = new();
                TTitle = new();
                Data = content.Select(x => x.Select(y => (T)Convert.ChangeType(y, typeof(T))).ToList()).ToList();
            }
        }
    }
}
