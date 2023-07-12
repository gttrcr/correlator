using System.Drawing;

namespace Gui
{
    public class MainFormStatic
    {
        public static List<List<string>> ReadCSV(string file)
        {
            List<List<string>> ret = new();
            string[] lines = File.ReadAllLines(file);
            for (int i = 0; i < lines.Length; i++)
            {
                List<string> values = lines[i].Split(new string[] { ",", ";" }, StringSplitOptions.None).ToList();
                ret.Add(values);
            }

            return ret;
        }

        private static readonly Dictionary<Color, bool> colors = new List<Color>() {
            Color.Blue, Color.Orange, Color.Red, Color.Purple, Color.Green,
            Color.Salmon, Color.DeepSkyBlue, Color.Lime, Color.Brown, Color.Black,
            Color.Tomato, Color.LightGreen, Color.LemonChiffon, Color.GreenYellow, Color.LightGray
        }.ToDictionary(x => x, x => false);
        public static Color GiveAGoodColor()
        {
            List<Color> cls = colors.Where(x => !x.Value).Select(x => x.Key).ToList();
            Color c = cls[new Random().Next(cls.Count)];
            colors[c] = true;
            return c;
        }

        public static void ReleaseAGoodColor(Color? color = null)
        {
            if (color == null)
                colors.Where(x => x.Value).ToList().ForEach(x => ReleaseAGoodColor(x.Key));
            else
                colors[color.Value] = false;
        }
    }
}
